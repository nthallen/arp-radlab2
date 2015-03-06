#include "bmxs_all.h"
#include "mlf.h"
#include "oui.h"

static char *mlf_config = NULL;

void bmxsdrv_init(int argc, char * const *argv ) {
  int c;

  optind = OPTIND_RESET; /* start from the beginning */
  opterr = 0; /* disable default error message */
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
		case 'H':
			//snprintf( board_hostname, 40, "%s", optarg );
			break;
		case 'N':
			mlf_config = optarg;
			break;
		case '?':
        nl_error(3, "Unrecognized Option -%c", optopt);
    }
  }
}
// Main function that initializes some things and everything else is spawned from
int main( int argc, char **argv ){
	
	send_id tm_data;
 	static BMXS_t BMXS;
	oui_init_options(argc, argv);
	//bmxsdrv_init( argc, argv );

	//Setup connection with Telemetry
	tm_data = Col_send_init( "BMXS", &BMXS, sizeof(BMXS), 0 ); 
	BMXS.stat = BMXS_INITIALIZE;
	Col_send(tm_data);
	nl_error( 0, "Startup" );
	if( operate( &BMXS, tm_data, mlf_config ) != 0 ) 
		nl_error(3, "error with operate");	
	
	// Use unlink to remove the file (inode) so that the
	// name will be available for the next run
	unlink(SOCKET_PATH);

	nl_error( 0, "Shutdown");
	BMXS.stat = BMXS_TERMINATE;
	Col_send(tm_data);
	
	return 0;
}
