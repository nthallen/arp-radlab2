
%INTERFACE <BMXS>

&command
	: BMXS Start * {  if_BMXS.Turf( "EN" ); }
	: BMXS Stop * { if_BMXS.Turf( "DA" ); }
	: BMXS Exit * { if_BMXS.Turf( "EX" ); }
	: BMXS Set NCoadd %d (Number of Scans to Coadd) * { if_BMXS.Turf( "NC:%d\n", $4); }
	: BMXS Set Resolution &res cm-1 * { if_BMXS.Turf( "RE:%d\n", $4); }
	;
&res <int>
	: 1 { $0 = 1; }
	: 2 { $0 = 2; }
	: 4 { $0 = 4; }
	: 8 { $0 = 8; }
	: 16 { $0 = 16; }
	: 32 { $0 = 32; }
	: 64 { $0 = 64; }
	: 128 { $0 = 128; }
	;
