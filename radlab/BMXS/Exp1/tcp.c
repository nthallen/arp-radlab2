//#define BOM_SERVER_PORT 20000


#include "bmxs_all.h"
#include <unistd.h>

static int tcp_socket;

int tcp_create( char *hostname, int tcp_port ) {

  int rc;
  struct sockaddr_in localAddr, servAddr;
  struct hostent *h;

  h = gethostbyname(hostname);
  if(h==NULL) {
    nl_error( 3, "Unknown host '%s'\n",hostname);
    exit(1);
  }

  servAddr.sin_family = h->h_addrtype;
  memcpy((char *) &servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
  servAddr.sin_port = htons(tcp_port);

  /* create socket */
  tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (tcp_socket<0) {
    nl_error( 3, "cannot open socket ");
}

  /* bind any port number */
  localAddr.sin_family = AF_INET;
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  localAddr.sin_port = htons(0);
  
  rc = bind(tcp_socket, (struct sockaddr *) &localAddr, sizeof(localAddr));
  if (rc<0) {
    nl_error( 3, "Cannot bind port TCP %u\n", tcp_port);
	}
	
  /* connect to server */
  rc = connect(tcp_socket, (struct sockaddr *) &servAddr, sizeof(servAddr));
  if (rc<0) {
    nl_error( 3, "cannot connect ");
  }
  return tcp_socket;
}

int tcp_send( struct OUT_FTIR_PACKET *cmd, int cmdleng ) {

  int rv;

  rv = send( tcp_socket, (void *) cmd, cmdleng, 0);
  if ( rv != cmdleng ) {
    nl_error( 2, "Send failed: %d: errno = %d\n", rv, errno );
	return -1;
  }
  
 return 0;
 
}

int tcp_receive( void *received_packet, int packet_size ){
	
	int rv;
	
	rv = recv( tcp_socket, received_packet, packet_size, 0 );

	if( rv < 0 ) nl_error( 2, "Receive Error" );
	
	return rv ;
}

int tcp_close(void) {
  close(tcp_socket);
  return 0;
}
