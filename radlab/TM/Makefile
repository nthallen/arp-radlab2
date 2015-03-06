# Makefile Generated Fri Dec 19 10:25:45 EST 2014
MNC=radlab
SPECFILE=radlab.spec
PCMFILE=radlab.pcm
SRC=base.tmc idx.tmc hart.tmc specq.tmc swstat.tmc idxcol.tmc
SRC+=dstat.tmc idxflag.tmc radlab.tbl idxdrv.cmd cmdenbl.cmd
SRC+=specq.cmd dccc.cmd swstat.cmd daspt.cmd radlab.tma radlabext.tmc
SRC+=radlabext.oui testext.tmc testext.oui radlab.doit
TOOL=radlab.spec Makefile
SCRIPT=interact idx.idx64 dccc.dccc
OBJ=radlabcol.cc radlab.pcm tm.dac radlabcoloui.c radlabcoloui.o
OBJ+=radlabcol.o radlabtbl.tmc radlabdisp.cc radlabdispoui.c
OBJ+=radlabdispoui.o radlabdisp.o radlabtblnc.tmc radlabdispnc.cc
OBJ+=radlabdispncoui.c radlabdispncoui.o radlabdispnc.o radlabcmd.cc
OBJ+=radlabcmd.dat radlabsrvr.o radlabsrvroui.c radlabsrvroui.o
OBJ+=radlabalgoa.tmc radlabalgo.cc radlabalgooui.c radlabalgooui.o
OBJ+=radlabalgo.o radlabext.cc radlabextoui.c radlabextoui.o
OBJ+=radlabext.o testext.cc testextoui.c testextoui.o testext.o
OBJ+=doit.dep radlabclt.o radlabcltoui.c radlabcltoui.o radlabcltnc.o
OBJ+=radlabcltncoui.c radlabcltncoui.o
TGT=radlabcol radlabdisp radlabdispnc radlabsrvr radlabalgo
TGT+=radlabext testext doit radlabclt radlabcltnc
DISTRIB=radlab.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit
SRCDIST=radlab.tbl radlab.tma base.tmc idx.tmc hart.tmc
SRCDIST+=/usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc
TMCBASE=base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc
TMCBASE+=specq.tmc swstat.tmc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/idx64.cmd idxdrv.cmd cmdenbl.cmd
CMDBASE+=specq.cmd dccc.cmd swstat.cmd daspt.cmd
COLBASE=
SWSBASE=
QCLIBASE=
PHTGT=radlabtbl.tmc
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/radlab
include /usr/local/share/huarp/appgen.mk

.PHONY : all extdistribution distribution clean check_photon

all : Makefile check_photon $(TGT) .cvsignore
Makefile : radlab.spec
	appgen radlab.spec
VERSION=`cat VERSION`
extdistribution : $(DSTRB) $(SRCDIST) VERSION
	@[ -d $(TGTDIR)/bin ] || mkdir $(TGTDIR)/bin
	@[ -d $(TGTDIR)/bin/$(VERSION) ] || mkdir $(TGTDIR)/bin/$(VERSION)
	@[ -d $(TGTDIR)/bin/$(VERSION)/Base ] || mkdir $(TGTDIR)/bin/$(VERSION)/Base
	@[ ! -f $(TGTDIR)/bin/$(VERSION)/$(PCMFILE) ] || \
	  cmp -s $(TGTDIR)/bin/$(VERSION)/$(PCMFILE) $(PCMFILE) || \
	  ( echo "$(PCMFILE) changed without VERSION update"; false )
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION) $(DSTRB)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION)/Base $(SRCDIST)
distribution : extdistribution
	@distribute $(FORCE) $(TGTDIR) $(IDISTRIB)
check_photon :
ifeq ($(WPHOTON),YES)
	@for tgt in $(PHTGT); do \
	  cmp -s $$tgt /usr/local/share/huarp/nulltbl.tmc && echo Remaking $$tgt && rm -f $$tgt; \
	done; true
endif
radlabcol : radlabcol.o radlabcoloui.o
	$(LINK.privCXX) radlabcol.o radlabcoloui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) radlabcoloui.c
	$(PROMOTE) radlabcol
radlabdisp : radlabdisp.o radlabdispoui.o
	$(LINK.normCXX) radlabdisp.o radlabdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) radlabdispoui.c
radlabdispnc : radlabdispnc.o radlabdispncoui.o
	$(LINK.normCXX) radlabdispnc.o radlabdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) radlabdispncoui.c
radlabsrvr : radlabsrvr.o radlabsrvroui.o
	$(LINK.privCXX) radlabsrvr.o radlabsrvroui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) radlabsrvroui.c
	$(PROMOTE) radlabsrvr
radlabalgo : radlabalgo.o radlabalgooui.o
	$(LINK.normCXX) radlabalgo.o radlabalgooui.o -ltmpp -ltm -lnort
	$(OUIUSE) radlabalgooui.c
radlabext : radlabext.o radlabextoui.o
	$(LINK.normCXX) radlabext.o radlabextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) radlabextoui.c
testext : testext.o testextoui.o
	$(LINK.normCXX) testext.o testextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) testextoui.c
doit : radlab.doit
	mkdoit3 -o doit  radlab.doit
radlabclt : radlabclt.o radlabcltoui.o
	$(LINK.normCXX) radlabclt.o radlabcltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) radlabcltoui.c
radlabcltnc : radlabcltnc.o radlabcltncoui.o
	$(LINK.normCXX) radlabcltnc.o radlabcltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) radlabcltncoui.c
radlabcol.cc : base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc idxcol.tmc
	$(TMC.col) base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc idxcol.tmc
radlabcoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
radlabcoloui.o : radlabcoloui.c
radlabcol.o : radlabcol.cc
radlabtbl.tmc : radlab.tbl
radlabdisp.cc : base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc dstat.tmc idxflag.tmc radlabtbl.tmc
	$(TMC) base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc dstat.tmc idxflag.tmc radlabtbl.tmc
radlabdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
radlabdispoui.o : radlabdispoui.c
radlabdisp.o : radlabdisp.cc
radlabtblnc.tmc : radlab.tbl
radlabdispnc.cc : base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc dstat.tmc idxflag.tmc radlabtblnc.tmc
	$(TMC) base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc dstat.tmc idxflag.tmc radlabtblnc.tmc
radlabdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
radlabdispncoui.o : radlabdispncoui.c
radlabdispnc.o : radlabdispnc.cc
radlabcmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/idx64.cmd idxdrv.cmd cmdenbl.cmd specq.cmd dccc.cmd swstat.cmd daspt.cmd
	$(CMDGEN) -d radlabcmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/idx64.cmd idxdrv.cmd cmdenbl.cmd specq.cmd dccc.cmd swstat.cmd daspt.cmd
radlabsrvr.o : radlabcmd.cc
	$(COMPILE.srvr) radlabcmd.cc
radlabsrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
radlabsrvroui.o : radlabsrvroui.c
radlabalgoa.tmc : radlab.tma radlabsrvr
	$(SERVER) ./radlabsrvr
	$(TMCALGO) -V "`./radlabsrvr -R`" radlab.tma
radlabalgo.cc : base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc radlabalgoa.tmc
	$(TMC) base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc radlabalgoa.tmc
radlabalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
radlabalgooui.o : radlabalgooui.c
radlabalgo.o : radlabalgo.cc
radlabext.cc : base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc dstat.tmc radlabext.tmc
	$(TMC) base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc dstat.tmc radlabext.tmc
radlabextoui.c : radlabext.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) radlabext.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
radlabextoui.o : radlabextoui.c
radlabext.o : radlabext.cc
testext.cc : base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc testext.tmc
	$(TMC) base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc specq.tmc swstat.tmc testext.tmc
testextoui.c : testext.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) testext.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
testextoui.o : testextoui.c
testext.o : testext.cc
doit.dep : radlab.doit
	mkdoit3 -M -o doit  radlab.doit
-include doit.dep
radlabclt.o : radlabcmd.cc
	$(COMPILE.clt) radlabcmd.cc
radlabcltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
radlabcltoui.o : radlabcltoui.c
radlabcltnc.o : radlabcmd.cc
	$(COMPILE.cltnc) radlabcmd.cc
radlabcltncoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
radlabcltncoui.o : radlabcltncoui.c

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
.cvsignore : Makefile
	@for i in $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
