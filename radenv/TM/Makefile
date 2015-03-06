# Makefile Generated Wed Feb 01 10:47:18 EST 2012
MNC=radenv
HOMEDIR=/home/radenv/src/TM
SPECFILE=radenv.spec
SRC=base.tmc herc_ad.tmc iopriv.oui radenvcol.tmc swstat.tmc
SRC+=herc_ad.c herc_ad.oui radenv.cmd swstat.cmd bmxs.cmd herc_dio.cc
SRC+=herc_dio.oui dstat.tmc bmxsrtg.tmc radenv.tbl radenv.tma
SRC+=radenv.edf radenv.doit
TOOL=radenv.spec Makefile
SCRIPT=interact
OBJ=radenvcol.cc radenv.pcm tm.dac radenvcoloui.c radenvcoloui.o
OBJ+=herc_ad.o radenvcol.o radenvcmd.cc radenvcmd.dat radenvsrvr.o
OBJ+=radenvsrvroui.c radenvsrvroui.o herc_dio.o radenvtbl.tmc
OBJ+=radenvdisp.cc radenvdispoui.c radenvdispoui.o radenvdisp.o
OBJ+=radenvtblnc.tmc radenvdispnc.cc radenvdispncoui.c
OBJ+=radenvdispncoui.o radenvdispnc.o radenvalgoa.tmc radenvalgo.cc
OBJ+=radenvalgooui.c radenvalgooui.o radenvalgo.o radenvextedf.oui
OBJ+=radenvext.tmc radenvext.cc radenvextoui.c radenvextoui.o
OBJ+=radenvext.o doit.dep radenvclt.o radenvcltoui.c radenvcltoui.o
OBJ+=radenvcltnc.o radenvcltncoui.c radenvcltncoui.o
TGT=radenvcol radenvsrvr radenvdisp radenvdispnc radenvalgo
TGT+=radenvext doit radenvclt radenvcltnc
DISTRIB=../Agilent/agilentDriver radenv.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit
SRCDIST=radenv.tbl radenv.tma base.tmc herc_ad.tmc
NONRCS=
TMCBASE=base.tmc herc_ad.tmc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/phrtg.cmd radenv.cmd swstat.cmd
CMDBASE+=bmxs.cmd
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/radenv
include /usr/local/share/huarp/appgen.mk

all : Makefile $(TGT)
Makefile : radenv.spec
	appgen radenv.spec
VERSION=`cat VERSION`
extdistribution : $(DSTRB) $(SRCDIST)
	@[ -d $(TGTDIR)/bin ] || mkdir $(TGTDIR)/bin
	@[ -d $(TGTDIR)/bin/$(VERSION) ] || mkdir $(TGTDIR)/bin/$(VERSION)
	@[ -d  $(TGTDIR)/bin/$(VERSION)/Base ] || mkdir $(TGTDIR)/bin/$(VERSION)/Base
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION) $(DSTRB)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION)/Base $(SRCDIST)
distribution : extdistribution
	@distribute $(FORCE) $(TGTDIR) $(IDISTRIB)
radenvcol : radenvcol.o radenvcoloui.o herc_ad.o
	$(LINK.privCXX) radenvcol.o radenvcoloui.o herc_ad.o -ltmpp -ltm -lnort
	$(OUIUSE) radenvcoloui.c
	$(PROMOTE) radenvcol
radenvsrvr : radenvsrvr.o herc_dio.o radenvsrvroui.o
	$(LINK.privCXX) radenvsrvr.o herc_dio.o radenvsrvroui.o -ltmpp -ltm -lnort
	$(OUIUSE) radenvsrvroui.c
	$(PROMOTE) radenvsrvr
radenvdisp : radenvdisp.o radenvdispoui.o
	$(LINK.normCXX) radenvdisp.o radenvdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) radenvdispoui.c
radenvdispnc : radenvdispnc.o radenvdispncoui.o
	$(LINK.normCXX) radenvdispnc.o radenvdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) radenvdispncoui.c
radenvalgo : radenvalgo.o radenvalgooui.o
	$(LINK.normCXX) radenvalgo.o radenvalgooui.o -ltmpp -ltm -lnort
	$(OUIUSE) radenvalgooui.c
radenvext : radenvext.o radenvextoui.o
	$(LINK.normCXX) radenvext.o radenvextoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) radenvextoui.c
doit : radenv.doit
	mkdoit3 -o doit  radenv.doit
radenvclt : radenvclt.o radenvcltoui.o
	$(LINK.normCXX) radenvclt.o radenvcltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) radenvcltoui.c
radenvcltnc : radenvcltnc.o radenvcltncoui.o
	$(LINK.normCXX) radenvcltnc.o radenvcltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) radenvcltncoui.c
radenvcol.cc : base.tmc herc_ad.tmc radenvcol.tmc swstat.tmc
	$(TMC.col) base.tmc herc_ad.tmc radenvcol.tmc swstat.tmc
radenvcoloui.c : iopriv.oui herc_ad.oui $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) iopriv.oui herc_ad.oui $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
radenvcoloui.o : radenvcoloui.c
herc_ad.o : herc_ad.c
radenvcol.o : radenvcol.cc
radenvcmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/phrtg.cmd radenv.cmd swstat.cmd bmxs.cmd
	$(CMDGEN) -d radenvcmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/phrtg.cmd radenv.cmd swstat.cmd bmxs.cmd
radenvsrvr.o : radenvcmd.cc
	$(COMPILE.srvr) radenvcmd.cc
radenvsrvroui.c : herc_dio.oui iopriv.oui $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) herc_dio.oui iopriv.oui $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
radenvsrvroui.o : radenvsrvroui.c
herc_dio.o : herc_dio.cc
radenvtbl.tmc : radenv.tbl
	$(TABLE) radenv.tbl
radenvdisp.cc : base.tmc herc_ad.tmc dstat.tmc /usr/local/share/huarp/flttime.tmc bmxsrtg.tmc radenvtbl.tmc
	$(TMC) base.tmc herc_ad.tmc dstat.tmc /usr/local/share/huarp/flttime.tmc bmxsrtg.tmc radenvtbl.tmc
radenvdispoui.c : /usr/local/share/oui/cic.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) /usr/local/share/oui/cic.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
radenvdispoui.o : radenvdispoui.c
radenvdisp.o : radenvdisp.cc
radenvtblnc.tmc : radenv.tbl
	$(NCTABLE) radenv.tbl
radenvdispnc.cc : base.tmc herc_ad.tmc dstat.tmc /usr/local/share/huarp/flttime.tmc bmxsrtg.tmc radenvtblnc.tmc
	$(TMC) base.tmc herc_ad.tmc dstat.tmc /usr/local/share/huarp/flttime.tmc bmxsrtg.tmc radenvtblnc.tmc
radenvdispncoui.c : /usr/local/share/oui/cic.oui $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) /usr/local/share/oui/cic.oui $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
radenvdispncoui.o : radenvdispncoui.c
radenvdispnc.o : radenvdispnc.cc
radenvalgoa.tmc : radenv.tma radenvsrvr
	$(SERVER) ./radenvsrvr
	$(TMCALGO) -V "`./radenvsrvr -R`" radenv.tma
radenvalgo.cc : base.tmc herc_ad.tmc radenvalgoa.tmc
	$(TMC) base.tmc herc_ad.tmc radenvalgoa.tmc
radenvalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
radenvalgooui.o : radenvalgooui.c
radenvalgo.o : radenvalgo.cc
radenvextedf.oui : radenv.edf
	$(EDF2OUI) radenv.edf
radenvext.tmc : radenv.edf
	$(EDF2EXT) radenv.edf
radenvext.cc : base.tmc herc_ad.tmc radenvext.tmc
	$(TMC) base.tmc herc_ad.tmc radenvext.tmc
radenvextoui.c : radenvextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) radenvextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
radenvextoui.o : radenvextoui.c
radenvext.o : radenvext.cc
doit.dep : radenv.doit
	mkdoit3 -M -o doit  radenv.doit
-include doit.dep
radenvclt.o : radenvcmd.cc
	$(COMPILE.clt) radenvcmd.cc
radenvcltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
radenvcltoui.o : radenvcltoui.c
radenvcltnc.o : radenvcmd.cc
	$(COMPILE.cltnc) radenvcmd.cc
radenvcltncoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
radenvcltncoui.o : radenvcltncoui.c

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
.cvsignore :
	@for i in Makefile '.B4*' $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
