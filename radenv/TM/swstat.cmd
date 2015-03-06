%{
  #include "swstat.h"
  #ifdef SERVER
    swstat_t SWData;
  #endif
%}

%INTERFACE <SWData:DG/data>

&command
  : &SWTM * { if_SWData.Turf(); }
  ;
&SWTM
  : FlipState &fon_off {
	SWData.FlipState = $2;
      }
  : SW Status &swstat {
        SWData.SWStat = $3;
      }
  ;
&swstat <int>
  : Set %d { $0 = $2; }
  : Idle { $0 = SWS_IDLE; }
  : Acquire { $0 = SWS_ACQUIRE; }
  : Time Warp { $0 = SWS_TIME_WARP; }
# : ReadFile { $0 = SWS_READFILE; }
# : Shutdown { $0 = SWS_SHUTDOWN; }
  ;
&fon_off <int>
  : on { $0 = 1; }
  : off { $0 = 0; }
  ;
