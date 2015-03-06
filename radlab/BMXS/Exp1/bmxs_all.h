#ifndef ssp_get_h_included
#define ssp_get_h_included

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* close() */
#include <string.h> /* memset() */
#include <errno.h>
#include <ctype.h>
#include "bomem_struct.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <signal.h>
#include "nortlib.h"
#include "mlf.h"
#include "nl_assert.h"
#include "BMXS.h"
#include "collect.h"
#include "BmxsHelper.h"

#define BOM_SERVER_PORT 20000
#define SERV_ADDRESS "10.0.0.44"
//#define SERV_ADDRESS "10.0.0.124"
//#define BOM_SERVER_PORT 4242
#define TIMEOUT_VALUE 15

#define UNABLE_CONN 0
#define LOST_CONN 1
#define SUPPRESS_CONN 2

#define SOCKET_PATH     "myserver"
//#define RECV_BUF_SIZE 100000

// typedef int coad_t;
//typedef float coad_t;
//typedef short SINT16;

extern int read_header( struct IN_TCP_FTIRPACKET *packet );
extern int read_tcp( struct IN_TCP_FTIRPACKET *packet, BMXS_t *BMXS, bmxsStruct *savedData );
extern int read_udp(struct IN_UDP_FTIRPACKET packet );

//extern int operate(int tcp, int udp, mlf_def_t *mlf, BMXS_t *BMXS, send_id tm_data);
extern int operate( BMXS_t *BMXS, send_id tm_data, char *mlf_config );

extern int user_command( char *command, BMXS_t *BMXS );

extern int udp_create(int *port);
extern int udp_send( int port, unsigned char cmd );
extern int udp_receive(struct IN_UDP_FTIRPACKET *scan, size_t length, char *hostaddr );
extern int tcp_create(char *hostname, int port);
extern int tcp_send( struct OUT_FTIR_PACKET *cmd, int cmdleng );
extern int tcp_close(void);
extern int tcp_receive( void *received_packet, int packet_size );
extern int udp_broadcast( int port, unsigned char cmd );

extern void bmxsdrv_init( int argc, char * const * argv );

#define LOGROOT "CPCI14"
#define PID_FILE LOGROOT "/bmxs_log.pid"
#define HDR_LOG LOGROOT "/bmxs.log"

#endif
