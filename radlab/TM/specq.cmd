%INTERFACE <specq>

%{
  #ifdef SERVER

  /* specq.cmd commands for communication with the Bomem */
  #include "specq.h"
  #include "collect.h"
  #define IOMODE_INIT (IO_SPACE|IO_BACKSPACE|IO_WORD)
  
  static unsigned short N_Coadds = 0;
  static int HartChan = 5;

  void set_ncoadds( int newcoadds ) {
    static send_id coaddid;

    N_Coadds = newcoadds;
    if (coaddid == 0) {
      int rv = set_response( 2 );
      coaddid = Col_send_init("Coadds", &N_Coadds, sizeof(N_Coadds), 0);
      set_response(rv);
    }
    if (coaddid != 0) Col_send(coaddid);
  }

  void specq_setscan( unsigned short value ) {
    if_specq.Turf("SR%d\n", value);
  }

  void specq_command( const char *cmd ) {
    if_specq.Turf( "%s\n", cmd );
  }

  void specq_scan( void ) {
    if (N_Coadds == 0) set_ncoadds(4);
    if_specq.Turf( "SCfile=B%%02d;coadds=%d", N_Coadds );
  }
  #endif
%}

&command
	: Bomem &specq_cmd
	;

&specq_cmd
	: Exit * { specq_command( SPECQ_EXIT ); }
#	: Reset * { specq_command( SPECQ_RESET ); }
#	: Check * { specq_command( SPECQ_CHECK ); }
	: Clear Status * { specq_command( SPECQ_RESET_STATUS ); }
	: SetCoadds %d (Enter Number of Coadds) * { set_ncoadds( $2 ); }
	: SetScan %d (Enter Next Scan Number) * { specq_setscan( $2-1 ); }
	: Scan * { specq_scan(); }
	;
