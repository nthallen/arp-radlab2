function ui_radenv
f = ne_dialg('radenv Instrument',1);
f = ne_dialg(f, 'add', 0, 1, 'gradenvc', 'Chamber' );
f = ne_dialg(f, 'add', 1, 0, 'pradenvcp', 'P' );
f = ne_listdirs(f, 'RADENV_DATA_DIR', 15);
f = ne_dialg(f, 'newcol');
ne_dialg(f, 'resize');
