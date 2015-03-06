%{
  #include "swstat.h"

  static unsigned short sw_status;
  void set_sw_status( unsigned short status ) {
    static send_id SWStatus;
    sw_status = status;
    if (SWStatus == 0) {
      int rv = set_response(2);
      SWStatus = Col_send_init("SWStatus", &sw_status, sizeof(sw_status), 0);
      set_response(rv);
    }
    if (SWStatus != 0) Col_send(SWStatus);
  }
%}

&command
        : SW Status &SWStat * { set_sw_status( $3 ); }
        ;

&SWStat <int>
        : Set %d { $0 = $2; }
        : Acquire Default { $0 = SWS_ACQUIRE; }
        : Acquire Laser { $0 = SWS_LASER_ACQUIRE; }
        : Acquire Cal1 { $0 = SWS_CAL1_ACQUIRE; }
        : Acquire Debug { $0 = SWS_DEBUG_ACQUIRE; }
        : Idle { $0 = SWS_IDLE; }
        : Shutdown { $0 = SWS_SHUTDOWN; }
        ;
