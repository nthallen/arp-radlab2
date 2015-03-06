/* OUI output from the following packages:
   msghdr_default
   msghdr
   bmxsdrv
   msg
   nl_error_init
*/
char *opt_string = "h:N:H:vo:mV";
#include "oui.h"
#include "msg.h"
#include "bmxs_all.h"
#include "nortlib.h"
  int (*nl_error)(int level, const char *s, ...) = msg;

void oui_init_options(int argc, char **argv) {
  char *msg_hdr_default = "bmxsd";
  const char *msg_hdr;
  msg_hdr = msghdr_init( msg_hdr_default, argc, argv );
 bmxsdrv_init(argc, argv);
  msg_init_options(msg_hdr, argc, argv);
}

#ifdef __USAGE
%C	[options]
	-H <bmxs_hostname>	
	-h <msg header>
	-m write to memo [default]
	-N <logging config>
	-o <error filename> Write to specified file
	-v add a level of verbosity
	-V write to stderr

Logging config is a path string identifying the last file previously written and implicitly the next file to write.
#endif
