#include "bmxs_all.h"
#include <errno.h>
#include <string.h>
static int udp_socket;

//! Creates UDP socket
int udp_create(int *port) {
  struct sockaddr_in servAddr;
  int rc;
  socklen_t servAddr_len = sizeof(servAddr);
  int broadcast = 1;
  /* socket creation */
  udp_socket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (udp_socket<0) {
    nl_error( -3,"Cannot open UDP socket");
  }

  /* bind local server port */
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(0);
  rc = bind (udp_socket, (struct sockaddr *) &servAddr,sizeof(servAddr));
  if(rc<0) {
    nl_error(3, "cannot bind port number %d",  0);
  }
  rc = getsockname( udp_socket, (struct sockaddr *)&servAddr, &servAddr_len);
  *port = ntohs(servAddr.sin_port);
  nl_error( -2, "UDP port is %d\n", *port );

  if( setsockopt( udp_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof( broadcast ) ) )
	nl_error( 3, "cannot set Broadcast option" );
  
  return udp_socket;
}

//! Grabs data from previously created UDP socket
int udp_receive( struct IN_UDP_FTIRPACKET *scan, size_t length, char *hostaddr ) {
    struct sockaddr_in cliAddr;
  	int n;
  	socklen_t cliLen;

    cliLen = sizeof(cliAddr);
	n = recvfrom(udp_socket, scan, length, 0, (struct sockaddr *) &cliAddr, &cliLen);
	if( n <= 0 ) nl_error( 0, "No UDP Pack returned %d", n );

	inet_ntop(AF_INET, (struct sockaddr *) &cliAddr.sin_addr.s_addr, hostaddr, 16);
 
	return n;
}
/*
int udp_send( int port_num, unsigned char cmd  ){
	struct IN_UDP_FTIRPACKET packet;
	struct sockaddr_in destAddr;
	struct hostent *h;
	struct sockaddr *temp;
	
	h = gethostbyname( SERV_ADDRESS );
	destAddr.sin_family = h->h_addrtype;
	memcpy((char *) &destAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length) ;
	destAddr.sin_port = htons(udp_socket);
	
	packet.header.signature = FTIR_SIGNATURE;
	packet.header.command = cmd;
	packet.header.size = 0;

	temp = (struct sockaddr *) &destAddr;
	sendto( udp_socket, &packet,  7, 0, temp, sizeof(destAddr) );
	
	return 0;
}
*/

//! Broadcasts to all devices on a given network
int udp_broadcast( int port_num, unsigned char cmd ){
	struct IN_UDP_FTIRPACKET packet;
	struct sockaddr_in destAddr;
	
	memset( &destAddr, '\0', sizeof(struct sockaddr_in) );
	destAddr.sin_family = AF_INET;
	destAddr.sin_port = htons( port_num );
	if(!inet_aton("255.255.255.255", &destAddr.sin_addr)) nl_error( 3, "Invalid UDP Broadcast Address" );
	
	packet.header.signature = htonl( FTIR_SIGNATURE );
	packet.header.command = cmd;
	packet.header.size = 0;
	if( udp_socket < 0 ) nl_error( 0, "UDP Socket is not initialized" );
	if(sendto( udp_socket, &packet,  7, 0, (struct sockaddr *)&destAddr, sizeof(struct sockaddr_in) )< 0)
		nl_error( 3, "UDP Broadcast Failed: %s", strerror(errno) );
	
	return 0;
}
