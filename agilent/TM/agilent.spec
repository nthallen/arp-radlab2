TGTDIR = $(TGTNODE)/home/agilent

tmcbase = base.tmc
# tmcbase = RefT.tmc
colbase = agilentcol.tmc

cmdbase = /usr/local/share/huarp/phrtg.cmd

genuibase = agilent.genui

Module TMbase

SCRIPT = interact
IDISTRIB = Experiment.config VERSION
IGNORE = Makefile
DISTRIB = ../Agilent/agilentDriver

agilentdisp : agilent.tbl rtg.tmc /usr/local/share/oui/cic.oui
agilentalgo : agilent.tma
doit : agilent.doit
%%
CPPFLAGS += -I ../Agilent
../Agilent/agilentDriver :
	cd ../Agilent && make
