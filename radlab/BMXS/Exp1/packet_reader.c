#include "bmxs_all.h"
#include "mlf.h"

//! Reads the header of a packet returns the number of bytes of what should be read off of tcp
int read_header( struct IN_TCP_FTIRPACKET *packet ){
	unsigned long signature = ntohl( packet->header.signature );
	unsigned short size = ntohs( packet->header.size );
	nl_error( -2, "Packet size: %hd", size );
	nl_error( -2, "Packet signature: %lX ", signature );
	nl_error( -2, "Packet command: %X ", packet->header.command );
	nl_assert( signature == FTIR_SIGNATURE );
	return size;
}	
//! After a full packet has been read into the buffer this will decide what to do with it
int read_tcp( struct IN_TCP_FTIRPACKET *packet, BMXS_t *BMXS, bmxsStruct *savedData ){
	FILE *fd;
	unsigned char day, month, year, hour, second, minute, millisecond;
	int size =  ntohs(packet->header.size);
	int i, tnumElements;
	long rowcol[2];
	
	switch( packet->header.command ){
		//! Packets that store data will be coadded within a separate buffer
		//! Once the appropriate number of coadds are reached it will write them to disk using MLF
		case D2PC_DATA:
			size -= 10;// The -10 comes from ctype (unsigned char and reserved[9] which == 10 bytes)
			//! Keeps track of the total number of bytes if following data reads don't match there will be an error with coads
			if( (savedData->numcoads) == (BMXS->numcoads) )
				savedData->t_num_bytes += size;
			//! copy into raw buffer at byte level			
			memcpy( (&savedData->buffer.rawbuffer[savedData->startingpoint]), packet->data.data, size );
			savedData->startingpoint += size;
			nl_error( -2, "TNB:%d SP:%d Coad:%d", savedData->t_num_bytes, savedData->startingpoint, savedData->numcoads );
			
			if( (packet->data.ctype == DPT_END) || (packet->data.ctype == DPT_COMPLETE) ){
				nl_error( -2, "Packet is a 'complete' packet" );
				
				if( (savedData->t_num_bytes) != (savedData->startingpoint) ){
					nl_error( 2, "Data length does not match" );
					return -1;
				}
				if( ((savedData->t_num_bytes) % sizeof(SINT16)) ){
					nl_error( 2, "Data does not match type SINT16, likely to crash phrtg" );
					return -1;
				}
				tnumElements = (savedData->t_num_bytes) / sizeof(SINT16);
				for( i = 0; i < tnumElements; i++ )
					savedData->coadbuf[i] += savedData->buffer.intbuffer[i];
				(savedData->numcoads)--;
					
				if( (savedData->numcoads) == 0 ){
					fd = mlf_next_file( savedData->mlf );
					if( fd == NULL ){
						nl_error( 2, "file could not be opened");
						return -1;
					}
					rowcol[0] = tnumElements;
					rowcol[1] = 1;
					fwrite( rowcol, sizeof(long), 2, fd );
					fwrite( savedData->coadbuf, sizeof(float), tnumElements, fd ); // ptr size count(#elements) fd
					BMXS->index = savedData->mlf->index;
					fclose(fd);
					return 1;
				}				else{
				savedData->startingpoint = 0;
				}
			}
			return 0;
		// Status packet that has time and date stamp
		case D2PC_STATUS:
			packet->status.header.date.stamp = ntohl( packet->status.header.date.stamp );
			packet->status.header.time.stamp = ntohl( packet->status.header.time.stamp );
			month = packet->status.header.date.date.month;
			day = packet->status.header.date.date.day;
			year = packet->status.header.date.date.year;
			hour = packet->status.header.time.time.hour;
			minute = packet->status.header.time.time.minutes;
			second = packet->status.header.time.time.seconds;
			millisecond = ntohs( packet->status.header.milliseconds );
			nl_error( -2, "Date: %hu.%hu.%hu", month, day, year );
			nl_error( -2, "Time: %huh %hum %hus %hums", hour, minute, second, millisecond );
			return 0;
		
		case D2PC_CONFIG:
			packet->config.udp_port = ntohs( packet->config.udp_port );
			packet->config.tcp_port = ntohs( packet->config.tcp_port );
			// packet->config.uart_speed;
			// packet->config.channel_type
			// packet->config.max_psize = ntohl( packet->config.max_psize );
			packet->config.DHCP_lease = ntohl( packet->config.DHCP_lease );
			return 0;
		
		case D2PC_RUPL_CONFIG:
			if( packet->uresult.result ) nl_error(3, "Upload board config" );
			return 0;
		
		case D2PC_FIRM_VERSION:
			nl_error( -2, "Flash Version: %d", packet->firm_ver.flash.version );
			nl_error( -2, "FPGA Version: %d", packet->firm_ver.fpga.version );
			return 0;
		
		case D2PC_REQ_HOSTP:
			nl_error( -2, "Host presence requested." );
			struct OUT_FTIR_PACKET host_packet;
			// Send host present
			host_packet.header.signature = htonl( FTIR_SIGNATURE ) ;
			host_packet.header.command = PC2D_HOST_PRESENT ;
			host_packet.header.size = 0;
			tcp_send(&host_packet, 7 );
			nl_error( -2, "Host presence sent." );
			return 0;
		
		case D2PC_RUPL_CONFIGB:
				if( packet->uresult.result ) nl_error( 0, "Upload instrument config" );
			return 0;
		
		case D2PC_CONFIGB:
			packet->bconfig.ftir_config.type = ntohs( packet->bconfig.ftir_config.type );
			packet->bconfig.ftir_config.instrument = ntohs( packet->bconfig.ftir_config.instrument );
			if( packet->bconfig.ftir_config.computer_ctrl ) nl_error( 0, "Remotely controlled" );
			else nl_error( 0, "Not remotely controlled" );
			if( packet->bconfig.ftir_config.fgain_enable ) nl_error( 0, "First stage gain ON" );
			else nl_error( 0, "First stage gain OFF" );
			if( packet->bconfig.ftir_config.sgain_enable ) nl_error( 0, "Second stage gain ON" );
			else nl_error( 0, " Second stage gain OFF" );
			BMXS->channels = ntohs( packet->bconfig.ftir_config.max_channel ); 
			nl_error( 0, "Max # Channels: %d", BMXS->channels);
			return 0;

		case D2PC_MRSTATUS:
			// No packet description what so ever
			return 0;

		case D2PC_FTP_INFO:
			// Skipping for now used for FTP login
			return 0;

		case D2PC_RFTP_INFO:
			if( packet->uresult.result ) nl_error( 3, "FTP Login failed" );
			return 0;

		default:
			nl_error( 2, "Error reading command from device" );
			return -1;
	}	
}

int read_udp( struct IN_UDP_FTIRPACKET packet ){
	unsigned char test;
	// Reading Header of packet
	nl_error( -2, "Packet signature is: %lX ", packet.header.signature );
	nl_error( -2, "Packet command: %X ", packet.header.command );
	nl_error( -2, "Packet size: %hd", ntohs(packet.header.size) );

	switch( packet.header.command ){
		
		case D2PC_U_CONN_STATUS:
			if( (test = packet.c_status.status) == PC2D_UPL_CONFIGB ){
				return (short) ntohs( packet.c_status.tcp_port );
			}
			return -1;
		
		case D2PC_U_CONFIG:
			*packet.config.ip_addr = ntohl( *packet.config.ip_addr );
			packet.config.udp_port = ntohs( packet.config.udp_port );
			packet.config.tcp_port = ntohs( packet.config.tcp_port );
			packet.config.max_psize = ntohl( packet.config.max_psize );
			packet.config.DHCP_lease = ntohl( packet.config.DHCP_lease );
			*packet.config.subnet_mask = ntohl( *packet.config.subnet_mask );
			*packet.config.gateway = ntohl( *packet.config.gateway );
			nl_error( -2, "IP address is: %s ", packet.config.ip_addr );
			nl_error( -2, "Channel type: %X ", packet.config.channel_type );
			nl_error( -2, "Uart speed: %c", packet.config.uart_speed );
			nl_error( -2, "UDP port is: %u ", packet.config.udp_port );
			nl_error( -2, "TCP port is: %u ", packet.config.tcp_port );
			nl_error( -2, "Max packet size is: %ld", packet.config.max_psize );
			nl_error( -2, "DHCP lease time: %ld seconds", packet.config.DHCP_lease );
			return 0 ;
			
		case D2PC_U_CONFIGB:
		// password
		// ftir_desc
			packet.bconfig.ftir_config.type = ntohs( packet.bconfig.ftir_config.type );
			packet.bconfig.ftir_config.instrument = ntohs( packet.bconfig.ftir_config.instrument );
			if( packet.bconfig.ftir_config.computer_ctrl ) nl_error( -1, "Remotely controlled" );
			else nl_error( -1, "Not remotely controlled" );
			if( packet.bconfig.ftir_config.fgain_enable ) nl_error( -1, "First stage gain ON" );
			else nl_error( -1, "\nFirst stage gain OFF\n" );
			if( packet.bconfig.ftir_config.sgain_enable ) nl_error( -1, "Second stage gain ON" );
			else nl_error( -1, "Second stage gain OFF" );
			packet.bconfig.ftir_config.max_channel = ntohs( packet.bconfig.ftir_config.max_channel ); 
			return 0;
			
		/*case D2PC_U_CONFIG:
			return 0;		*/

		default:
			nl_error( 0, "Error reading command from device" );
			return -1;
	}
}
