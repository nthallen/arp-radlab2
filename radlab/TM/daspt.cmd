&command
  : &daspt_lim_cmd %lf (Enter Voltage) *
    { int sp = (int) (409.6 * $2);
      if ( sp > 410 ) sp = 410;
      else if ( sp < 0 ) sp = 0;
      sbwr($1, sp);
    }
  ;
&daspt_lim_cmd <int>
  : QCL Current Setpoint { $0 = 0xC60; }
  ;
