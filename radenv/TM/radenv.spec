tmcbase = base.tmc herc_ad.tmc Herc_T30K.tmc
cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = /usr/local/share/huarp/phrtg.cmd
cmdbase = radenv.cmd
cmdbase = bmxs.cmd
genuibase = radenv.genui

Module TMbase

TGTDIR = $(TGTNODE)/home/radenv
IDISTRIB = Experiment.config VERSION
# DISTRIB = ../Agilent/agilentDriver
SCRIPT = interact
IGNORE = Makefile

radenvcol : iopriv.oui herc_ad.c herc_ad.oui
radenvsrvr : herc_dio.cc herc_dio.oui iopriv.oui
radenvdisp : radenv.tbl /usr/local/share/oui/cic.oui
radenvalgo : radenv.tma
doit : radenv.doit
