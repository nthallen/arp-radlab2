#include <sys/select.h>
#include <time.h>
#include <sys/time.h>
#include "bmxs_all.h"
#include "BmxsHelper.h"
#include "mlf.h"
#include "collect.h"
#include "tm.h"
#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
//! Once in operate will stay in operate until terminated or fatal errors occur
int operate( BMXS_t *p_BMXS, send_id tm_data, char *mlf_config ){
	int n, user, done = 0, pstcp = 7, readsize = -1, pread, initial = 7, userReset;
    int connFlag = UNABLE_CONN;
	fd_set rfd;
    struct tm *lt;
	struct timeval timeout;
	char s[8] = { 'R', 'E', ':', '1', '6', '\0' }; //! faux cmd set res of device to 16 bit Resolution cbcb User
	struct IN_TCP_FTIRPACKET *packet;
	struct IN_UDP_FTIRPACKET upacket;
	char buffer[sizeof( struct IN_TCP_FTIRPACKET )];
	bmxsStruct savedData;	// Helper Struct for passing variable to other functions
	
	// Taking off the stack and putting buffers in the heap
	savedData.buffer.rawbuffer = (unsigned char *) malloc( (RECV_BUF_ELEMENTS * sizeof(SINT16)) );
	savedData.coadbuf = (coad_t *) malloc( (RECV_BUF_ELEMENTS * sizeof(coad_t)) );
	
	savedData.numcoads = 5; // Hardcode of initial 5 for setup, cbcb user

	memset( savedData.coadbuf, 0, RECV_BUF_ELEMENTS * sizeof( coad_t ) );
	
	savedData.mlf = mlf_init( 3, 60, 1, "BMXS", "dat", mlf_config ); 

	// ***Moving in setup from bom_soc***
	char bomem_hostname[16] = SERV_ADDRESS;
	int packet_size, tcp = -1, udp, bomemInit = 1;
	int udp_port, devicePort;
	time_t now, absTimeOut;
	struct OUT_FTIR_PACKET bom_setup;
	// struct IN_UDP_FTIRPACKET udpSetupPack;
	// *** End **************************
	// Changing to an absolute time implementation
	// timeout.tv_sec = 15;
	timeout.tv_usec = 0;
	
	user = open( tm_dev_name("cmd/BMXS"), O_RDONLY );
	if( user < 0 ) nl_error( -2, "opening command channel" );

	// Setup UDP port
	udp = udp_create(&udp_port);
	
	p_BMXS->numcoads = savedData.numcoads;
	p_BMXS->stat = BMXS_INITIALIZE;
	Col_send(tm_data);
	
	do{
	if( bomemInit ){
		absTimeOut = time( NULL ) + TIMEOUT_VALUE;
		switch( bomemInit ){

			case 1:
				// UDP Broadcast
				udp_broadcast( BOM_SERVER_PORT, PC2D_U_CONN_STATUS );
				udp_broadcast( BOM_SERVER_PORT, PC2D_U_CONN_STATUS );
				udp_broadcast( BOM_SERVER_PORT, PC2D_U_CONN_STATUS );
				break;

			case 2:
				// Setup signature and Enable data transmission	
				bom_setup.header.signature = htonl( FTIR_SIGNATURE );
				bom_setup.header.size = 0;
				// Set command for connection info
				bom_setup.header.command = PC2D_CONN_INFO;
				bom_setup.cinfo.udp_port = htons(udp_port);
				bom_setup.header.size = htons( 12 );
				// Setting up the Date and Time
				now = time( NULL );
				lt = localtime( &now );
				// Set the Date
				bom_setup.cinfo.host_date.date.day = lt->tm_mday;
				bom_setup.cinfo.host_date.date.month = lt->tm_mon + 1;
				bom_setup.cinfo.host_date.date.year = lt->tm_year + 1900;
				// Set the time
				bom_setup.cinfo.host_time.time.seconds = lt->tm_sec;
				bom_setup.cinfo.host_time.time.minutes = lt->tm_min;
				bom_setup.cinfo.host_time.time.hour = lt->tm_hour;
				bom_setup.cinfo.host_msec = htons( 0 );
				bom_setup.cinfo.host_date.stamp = htonl( bom_setup.cinfo.host_date.stamp );
				bom_setup.cinfo.host_time.stamp = htonl( bom_setup.cinfo.host_time.stamp );
				packet_size = sizeof( struct IN_HEADER ) + sizeof( struct feth_conn_info );
				if( tcp_send(&bom_setup, packet_size) ==  0)
					bomemInit++;
				break;
			
			case 3:
				bom_setup.header.signature = htonl( FTIR_SIGNATURE );
				bom_setup.header.command = PC2D_ENABLE_TX;
				bom_setup.header.size = htons( 1 );
				bom_setup.txctrl.mode = FP_TM_STATUS;
				if( tcp_send( &bom_setup, 8 ));
					bomemInit++;
				break;
				
			case 4:
				user_command( s, p_BMXS );
				connFlag = LOST_CONN;
				bomemInit = 0;
				break;
		}
	}
	// select removes elements from rfd that are not ready for reading
	// this clears out and resets them all
	FD_ZERO( &rfd );
	FD_SET( user, &rfd );
	FD_SET( tcp, &rfd );
	FD_SET( udp, &rfd );
	
	now = time( NULL );
	if( now > absTimeOut ){
		timeout.tv_sec = 0;
	}else{
		timeout.tv_sec = absTimeOut - now;
	}
	switch( n = select( 1 + max(user, max(udp, tcp)) , &rfd, NULL, NULL, &timeout )){

		case -1:
			nl_error( 3, "select" );
			done = 1;
			break;
		
		case 0:
			if( connFlag == UNABLE_CONN ){
				nl_error( 0, "Unable to connect" );
				connFlag = SUPPRESS_CONN;
			}
			if( connFlag == LOST_CONN ){
				nl_error( 0, "Lost Connection" );
				connFlag = SUPPRESS_CONN;
			}
			bomemInit = 1;
			p_BMXS->stat = BMXS_ACQUIRE;
			Col_send( tm_data );
			break;			
		
		default:
			if( FD_ISSET( user, &rfd ) ){	// User
				if ((n = read(user, s, BUFSIZ)) == -1)
					nl_error( 2, "command error");
				if( n == 0 ) done = 1; // default exit command
				if( (userReset = user_command( s, p_BMXS )) == 7 ) done = 1;
				if( userReset == 1 ){
					memset( savedData.coadbuf, 0, RECV_BUF_ELEMENTS * sizeof( coad_t ));
					memset( savedData.buffer.rawbuffer, 0, RECV_BUF_ELEMENTS * sizeof( SINT16 ));
					savedData.startingpoint = 0;
					savedData.t_num_bytes = 0;
					savedData.numcoads = p_BMXS->numcoads;
				}
				Col_send( tm_data );
				break;
			}
			if( FD_ISSET( tcp, &rfd ) ){	// Tcp
				if( initial > 0 ){ 
					pread = tcp_receive(&buffer[7 - initial], initial);
					nl_error( -2, "read in %d bytes", pread );
					initial -= pread;
				}
				if( readsize > 0 ){
					pread = tcp_receive(&buffer[pstcp], readsize );
					readsize -= pread;
					pstcp += pread;
				}
				if( (readsize == 0) ){
					packet = (struct IN_TCP_FTIRPACKET *) buffer;
					//! if read_tcp returns anything other than zero it zeros out and discards any data
					if(read_tcp( packet, p_BMXS, &savedData )){
						savedData.startingpoint = 0;
						savedData.t_num_bytes = 0;
						savedData.numcoads = p_BMXS->numcoads;
					}
					initial = 7;
					pstcp = 7;
					readsize = -1;
					if( savedData.numcoads == 0 ) savedData.numcoads = p_BMXS->numcoads; 
					Col_send( tm_data );
				}
				if( (initial == 0)&&(readsize == -1) ){
					packet = (struct IN_TCP_FTIRPACKET *) buffer;
					readsize = read_header(packet); 
				}
				absTimeOut = time( NULL ) + TIMEOUT_VALUE;
				break;
			}
			if(FD_ISSET( udp, &rfd )){	// udp
				n = udp_receive(&upacket, 1600, bomem_hostname);
				if( bomemInit == 1 ){
					devicePort = ntohs( upacket.c_status.tcp_port );
					//! open TCP connection to Bomem
					if((tcp = tcp_create(bomem_hostname, devicePort )) > 0 ){
						bomemInit = 2;
						p_BMXS->stat = BMXS_READY;
						nl_error( 0, "Connected" );
						Col_send( tm_data );
					}
					else{
						nl_error( 2, "Could not bind tcp port" );
						if( read_udp( upacket ) < 0 ) 
							nl_error( 2, "corrupted udp packet" );
					}
				}
				absTimeOut = time( NULL ) + TIMEOUT_VALUE;
				break;
			}
		}
	}while( !done );
	tcp_close();
	close(user);
	return 0;
}
