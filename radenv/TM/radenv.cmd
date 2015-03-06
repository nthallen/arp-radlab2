%{
  #ifdef SERVER
    #include "herc_ad.h"
  #endif
%}
&command
  : Command %d &on_off * { herc_cmd($2, $3); }
  : Flipper &on_off * { herc_cmd( 0, $2); }
  ;
&on_off <int>
  : on { $0 = 1; }
  : off { $0 = 0; }
  ;
