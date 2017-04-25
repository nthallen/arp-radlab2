#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "agilent_int.h"
#include "oui.h"
#include "tm.h"
#include "nortlib.h"

/**
 * Establish connection to Quit stream
 */
Quitter::Quitter() : Selectee() {
  int resp = set_response(1);
  fd = tm_open_name(tm_dev_name("cmd/Quit"),NULL,O_RDONLY);
  flags = Selector::Sel_Read;
  set_response(resp);
}

/** If Quitter is ready for read, it's time to quit */
int Quitter::ProcessData(int flag) {
  return 1;
}

const int agilent_ctrl::BUFFER_SIZE = 10000;
const int agilent_ctrl::devicePort = 5025;
const char agilent_ctrl::hostname[] = "agilent.arp.harvard.edu";

agilent_ctrl::agilent_ctrl() : Selectee() {
  int rv;

  buffer = new char[BUFFER_SIZE];
  TM.init( this, "Agilent", &TMdata, sizeof(TMdata) );
  fd = tcp_create( hostname,  devicePort );
  if ( fd >= 0 ) {
    nl_error( 0, "Connected to Agilent" );
  } else {
    nl_error( 3, "Failed to connect to Agilent" );
  }
  tcp_send( "SYST:COMM:LAN:TELN:WMES?\n", -1 );
  rv = tcp_receive( buffer, BUFFER_SIZE );
  if ( rv == BUFFER_SIZE ) buffer[BUFFER_SIZE-1] = '\0';
  else if ( rv >= 0 ) buffer[rv] = '\0';
  else nl_error( 3, "Error receiving from Agilent: %s",
    strerror(errno) );
  nl_error( 0, "%s", buffer );
}

void agilent_ctrl::Request() {
  tcp_send( "READ?\n", -1 );
  flags = Selector::Sel_Read;
  nl_error( -2, "READ?" );
}

int agilent_ctrl::ProcessData(int flag) {
  char *pBegin, *pEnd;
  int OK = 0;
  int rv;
  bool done = false;
  int count = 0;
  static int saveCount = 0;
  
  rv = tcp_receive( buffer, BUFFER_SIZE );
  if ( rv == BUFFER_SIZE ) buffer[BUFFER_SIZE-1] = '\0';
  else if ( rv >= 0 ) buffer[rv] = '\0';
  else nl_error( 3, "Error receiving from Agilent: %s",
    strerror(errno) );

  // Skip any echos or garbage at the beginning
  pBegin = &buffer[0];
  while (*pBegin != '\0' && *pBegin != '+' && *pBegin != '-')
    ++pBegin;

  // Not sure how to implement a loop here
  // Feel that it should be able to be done..
  // straight memcpy might do it but might be dangerous
  while (!done) {
    
    TMdata.data[count] = strtod( pBegin, &pEnd );
    count++;
    if ( *pEnd == ',' ) {
      pBegin = pEnd + 1;
    } else {
      nl_error( -2, "No more data detected" );
      if ( saveCount == 0 ) { // Should only trigger on first pass.
        saveCount = count;
        nl_error( 0, "Number of data points is: %d", saveCount );
        for (int i = saveCount; i < 20; i++ )
                TMdata.data[i] = 0;
      }
      if( saveCount != count ) {
        nl_error( 2, "Error number of data points changed" );
      } else {
        OK = 1;
      }
            
      TMdata.count = count;
      done = true;
    }
  }

	
  TM.send();
  nl_error( -2, "TM.send()" );
  flags = 0;
  
  if ( !OK ) {
    nl_error( 1, "Invalid data read: '%s'", buffer );
  }
  
  return 0;
}

TMcollect::TMcollect() : Selectee() {
  par = NULL;
  TMid = NULL;
}

int TMcollect::ProcessData( int flag ) {
  flags = 0;
  par->Request();
  return 0;
}


int TMcollect::init(agilent_ctrl *par_in, const char *name,
	    void *data, int data_size) {
  par = par_in;
  TMid = Col_send_init(name, data, data_size, 0);
  fd = TMid->fd;
  flags = Selector::Sel_Write;
  nl_error( -2, "TM initialized: fd = %d", fd );
  return 0;
}

int TMcollect::send() {
  Col_send(TMid);
  flags = Selector::Sel_Write;
  return 0;
} 

int main( int argc, char **argv ) {
  oui_init_options(argc, argv);
  nl_error( 0, "Initiating connections" );
  { Selector Sr;
    Quitter Q;
    agilent_ctrl AC;
    // Allow for the case where we can't locate the
    // command stream
    if ( Q.fd >= 0)
      Sr.add_child(&Q);
    Sr.add_child(&AC);
    Sr.add_child(&AC.TM);
    nl_error( 0, "Installed" );
    Sr.event_loop();
    nl_error( 0, "Terminating" );
  }
  return 0;
}

