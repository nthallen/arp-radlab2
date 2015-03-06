# Makefile Generated Wed May 18 02:21:08 UTC 2011
MNC=bmxs
HOMEDIR=/home/ndemusz/BMXSdiag
SPECFILE=bmxs.spec
SRC=base.tmc bmxsdiag.tbl bmxsrtg.tmc bmxs.doit bmxs.cmd
TOOL=bmxs.spec Makefile
SCRIPT=interact
OBJ=bmxsdiagtbl.tmc bmxsdiagdisp.cc bmxsdiagdispoui.c
OBJ+=bmxsdiagdispoui.o bmxsdiagdisp.o bmxsdiagtblnc.tmc
OBJ+=bmxsdiagdispnc.cc bmxsdiagdispncoui.c bmxsdiagdispncoui.o
OBJ+=bmxsdiagdispnc.o bmxscol.cc bmxs.pcm tm.dac bmxscoloui.c
OBJ+=bmxscoloui.o bmxscol.o doit.dep bmxscmd.cc bmxscmd.dat bmxsclt.o
OBJ+=bmxscltoui.c bmxscltoui.o bmxscltnc.o bmxscltncoui.c
OBJ+=bmxscltncoui.o bmxssrvr.o bmxssrvroui.c bmxssrvroui.o
TGT=bmxsdiagdisp bmxsdiagdispnc bmxscol doit bmxsclt bmxscltnc
TGT+=bmxssrvr
DISTRIB=bmxs.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit
SRCDIST=bmxsdiag.tbl base.tmc
NONRCS=
TMCBASE=base.tmc
CMDBASE=/usr/local/share/huarp/root.cmd bmxs.cmd
CMDBASE+=/usr/local/share/huarp/phrtg.cmd
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/BMXSdiag
include /usr/local/share/huarp/appgen.mk

all : Makefile $(TGT)
Makefile : bmxs.spec
	appgen bmxs.spec
VERSION=`cat VERSION`
extdistribution : $(DSTRB) $(SRCDIST)
	@[ -d $(TGTDIR)/bin ] || mkdir $(TGTDIR)/bin
	@[ -d $(TGTDIR)/bin/$(VERSION) ] || mkdir $(TGTDIR)/bin/$(VERSION)
	@[ -d  $(TGTDIR)/bin/$(VERSION)/Base ] || mkdir $(TGTDIR)/bin/$(VERSION)/Base
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION) $(DSTRB)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION)/Base $(SRCDIST)
distribution : extdistribution
	@distribute $(FORCE) $(TGTDIR) $(IDISTRIB)
bmxsdiagdisp : bmxsdiagdisp.o bmxsdiagdispoui.o
	$(LINK.normCXX) bmxsdiagdisp.o bmxsdiagdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) bmxsdiagdispoui.c
bmxsdiagdispnc : bmxsdiagdispnc.o bmxsdiagdispncoui.o
	$(LINK.normCXX) bmxsdiagdispnc.o bmxsdiagdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) bmxsdiagdispncoui.c
bmxscol : bmxscol.o bmxscoloui.o
	$(LINK.privCXX) bmxscol.o bmxscoloui.o -ltmpp -ltm -lnort
	$(OUIUSE) bmxscoloui.c
	$(PROMOTE) bmxscol
doit : bmxs.doit
	mkdoit3 -o doit  bmxs.doit
bmxsclt : bmxsclt.o bmxscltoui.o
	$(LINK.normCXX) bmxsclt.o bmxscltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) bmxscltoui.c
bmxscltnc : bmxscltnc.o bmxscltncoui.o
	$(LINK.normCXX) bmxscltnc.o bmxscltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) bmxscltncoui.c
bmxssrvr : bmxssrvr.o bmxssrvroui.o
	$(LINK.privCXX) bmxssrvr.o bmxssrvroui.o -ltmpp -ltm -lnort
	$(OUIUSE) bmxssrvroui.c
	$(PROMOTE) bmxssrvr
bmxsdiagtbl.tmc : bmxsdiag.tbl
	$(TABLE) bmxsdiag.tbl
bmxsdiagdisp.cc : base.tmc /usr/local/share/huarp/flttime.tmc bmxsdiagtbl.tmc bmxsrtg.tmc
	$(TMC) base.tmc /usr/local/share/huarp/flttime.tmc bmxsdiagtbl.tmc bmxsrtg.tmc
bmxsdiagdispoui.c : /usr/local/share/oui/cic.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) /usr/local/share/oui/cic.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
bmxsdiagdispoui.o : bmxsdiagdispoui.c
bmxsdiagdisp.o : bmxsdiagdisp.cc
bmxsdiagtblnc.tmc : bmxsdiag.tbl
	$(NCTABLE) bmxsdiag.tbl
bmxsdiagdispnc.cc : base.tmc /usr/local/share/huarp/flttime.tmc bmxsdiagtblnc.tmc bmxsrtg.tmc
	$(TMC) base.tmc /usr/local/share/huarp/flttime.tmc bmxsdiagtblnc.tmc bmxsrtg.tmc
bmxsdiagdispncoui.c : /usr/local/share/oui/cic.oui $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) /usr/local/share/oui/cic.oui $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
bmxsdiagdispncoui.o : bmxsdiagdispncoui.c
bmxsdiagdispnc.o : bmxsdiagdispnc.cc
bmxscol.cc : base.tmc
	$(TMC.col) base.tmc
bmxscoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
bmxscoloui.o : bmxscoloui.c
bmxscol.o : bmxscol.cc
doit.dep : bmxs.doit
	mkdoit3 -M -o doit  bmxs.doit
-include doit.dep
bmxscmd.cc : /usr/local/share/huarp/root.cmd bmxs.cmd /usr/local/share/huarp/phrtg.cmd
	$(CMDGEN) -d bmxscmd.dat /usr/local/share/huarp/root.cmd bmxs.cmd /usr/local/share/huarp/phrtg.cmd
bmxsclt.o : bmxscmd.cc
	$(COMPILE.clt) bmxscmd.cc
bmxscltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
bmxscltoui.o : bmxscltoui.c
bmxscltnc.o : bmxscmd.cc
	$(COMPILE.cltnc) bmxscmd.cc
bmxscltncoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
bmxscltncoui.o : bmxscltncoui.c
bmxssrvr.o : bmxscmd.cc
	$(COMPILE.srvr) bmxscmd.cc
bmxssrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
bmxssrvroui.o : bmxssrvroui.c

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
.cvsignore :
	@for i in Makefile '.B4*' $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
