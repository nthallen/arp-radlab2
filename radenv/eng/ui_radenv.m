function ui_radenv
f = ne_dialg('radenv Instrument',1);
f = ne_dialg(f, 'add', 0, 1, 'gradenvc', 'Chamber' );
f = ne_dialg(f, 'add', 1, 0, 'pradenvcp', 'P' );
f = ne_dialg(f, 'add', 1, 0, 'pradenvct', 'T' );
f = ne_dialg(f, 'add', 0, 1, 'gradenvtm', 'T Mbase' );
f = ne_dialg(f, 'add', 1, 0, 'pradenvtmtd', 'T Drift' );
f = ne_dialg(f, 'add', 1, 0, 'pradenvtmcpu', 'CPU' );
f = ne_dialg(f, 'add', 1, 0, 'pradenvtmram', 'RAM' );
f = ne_dialg(f, 'add', 1, 0, 'pradenvtmd', 'Disk' );
f = ne_listdirs(f, 'RADENV_DATA_DIR', 15);
f = ne_dialg(f, 'newcol');
ne_dialg(f, 'resize');
