tmcbase = base.tmc herc_ad.tmc
cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = /usr/local/share/huarp/phrtg.cmd
cmdbase = radenv.cmd
cmdbase = bmxs.cmd

TGTDIR = $(TGTNODE)/home/radenv
IDISTRIB = Experiment.config VERSION
# DISTRIB = ../Agilent/agilentDriver
SCRIPT = interact

radenvcol : iopriv.oui herc_ad.c herc_ad.oui
radenvsrvr : herc_dio.cc herc_dio.oui iopriv.oui
radenvdisp : /usr/local/share/huarp/flttime.tmc radenv.tbl /usr/local/share/oui/cic.oui
radenvalgo : radenv.tma
radenvext : radenv.edf
doit : radenv.doit
