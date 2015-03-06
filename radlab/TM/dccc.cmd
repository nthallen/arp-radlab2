%INTERFACE <dccc:dccc>
&command
  : &dccc_cmd * { if_dccc.Turf("D%d\n", $1); }
  ;
&dccc_cmd <int>
  : Laser Power On { $0 = 12; }
  : Laser Power Off { $0 = 13; }
  ;
