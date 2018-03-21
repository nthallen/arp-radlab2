function ui_Ag
f = ne_dialg('Agilent',1);
f = ne_dialg(f, 'add', 0, 1, 'gAga', 'Agilent' );
f = ne_dialg(f, 'add', 1, 0, 'pAgao', 'Ohms' );
f = ne_dialg(f, 'add', 1, 0, 'pAgacount', 'count' );
f = ne_dialg(f, 'add', 1, 0, 'pAgas', 'Stale' );
f = ne_dialg(f, 'add', 0, 1, 'gAgtm', 'T Mbase' );
f = ne_dialg(f, 'add', 1, 0, 'pAgtmtd', 'T Drift' );
f = ne_dialg(f, 'add', 1, 0, 'pAgtmcpu', 'CPU' );
f = ne_dialg(f, 'add', 1, 0, 'pAgtmram', 'RAM' );
f = ne_dialg(f, 'add', 1, 0, 'pAgtmd', 'Disk' );
f = ne_listdirs(f, 'Agilent_Data_Dir', 15);
f = ne_dialg(f, 'newcol');
ne_dialg(f, 'resize');
