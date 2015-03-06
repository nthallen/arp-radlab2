tmcbase = base.tmc
cmdbase = /usr/local/share/huarp/root.cmd bmxs.cmd
cmdbase = /usr/local/share/huarp/phrtg.cmd
TGTDIR = $(TGTNODE)/home/BMXSdiag
SCRIPT = interact
IDISTRIB = Experiment.config doit VERSION

bmxsdiagdisp : /usr/local/share/huarp/flttime.tmc bmxsdiag.tbl bmxsrtg.tmc /usr/local/share/oui/cic.oui 
bmxscol :

doit : bmxs.doit

