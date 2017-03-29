# Makefile Generated Tue Mar 28 11:40:50 EDT 2017
MNC=radenv
SPECFILE=radenv.spec
PCMFILE=radenv.pcm
SRC=base.tmc herc_ad.tmc iopriv.oui herc_ad.c herc_ad.oui
SRC+=/usr/local/share/huarp/root.cmd /usr/local/share/huarp/phrtg.cmd
SRC+=radenv.cmd bmxs.cmd herc_dio.cc herc_dio.oui
SRC+=/usr/local/share/huarp/flttime.tmc radenv.tbl
SRC+=/usr/local/share/oui/cic.oui radenv.tma radenv.edf radenv.doit
SRC+=radenv.pcm
TOOL=radenv.spec Makefile
SCRIPT=interact
OBJ=radenvcol.cc tm.dac radenvcoloui.c radenvcoloui.o herc_ad.o
OBJ+=radenvcol.o radenvcmd.cc radenvcmd.dat radenvsrvr.o
OBJ+=radenvsrvroui.c radenvsrvroui.o herc_dio.o radenvtbl.tmc
OBJ+=radenvdisp.cc radenvdispoui.c radenvdispoui.o radenvdisp.o
OBJ+=radenvtblnc.tmc radenvdispnc.cc radenvdispncoui.c
OBJ+=radenvdispncoui.o radenvdispnc.o radenvalgoa.tmc radenvalgo.cc
OBJ+=radenvalgooui.c radenvalgooui.o radenvalgo.o radenvextedf.oui
OBJ+=radenvext.tmc radenvext.cc radenvextoui.c radenvextoui.o
OBJ+=radenvext.o doit.dep radenvclt.o radenvcltoui.c radenvcltoui.o
OBJ+=radenvcltnc.o radenvcltncoui.c radenvcltncoui.o
OBJ+=radenvtbl.tmc.dep radenvtblnc.tmc.dep
TGT=radenvcol radenvsrvr radenvdisp radenvdispnc radenvalgo
TGT+=radenvext doit radenvclt radenvcltnc
IGNORE=
DISTRIB=radenv.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit
SRCDIST=radenv.tbl radenv.tma base.tmc herc_ad.tmc
TMCBASE=base.tmc herc_ad.tmc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/phrtg.cmd radenv.cmd bmxs.cmd
COLBASE=
SWSBASE=
QCLIBASE=
GENUIBASE=
EXTBASE=
SPECDEPBASE=
SPECTGTBASE=
AG_CPPFLAGS=
PHTGT=radenvtbl.tmc
SOURCE=$(SRC) $(TOOL) $(SCRIPT)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/radenv
include /usr/local/share/huarp/appgen.mk

.PHONY : all all-dist extdistribution distribution clean clean-dist check_photon

IGNOREFILE=.cvsignore
all : Makefile check_photon $(TGT) $(IGNOREFILE)
all-dist : $(DSTRB) $(SRCDIST) VERSION
Makefile $(SPECTGTBASE) : radenv.spec $(SPECDEPBASE)
	appgen radenv.spec
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
radenvcol.cc : base.tmc herc_ad.tmc VERSION
	$(TMC.col) base.tmc herc_ad.tmc
radenvcoloui.c : iopriv.oui herc_ad.oui $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) iopriv.oui herc_ad.oui $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
radenvcoloui.o : radenvcoloui.c
herc_ad.o : herc_ad.c
radenvcol.o : radenvcol.cc
radenvcmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/phrtg.cmd radenv.cmd bmxs.cmd
	$(CMDGEN) -d radenvcmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/phrtg.cmd radenv.cmd bmxs.cmd
radenvsrvr.o : radenvcmd.cc
	$(COMPILE.srvr) radenvcmd.cc
radenvsrvroui.c : herc_dio.oui iopriv.oui $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) herc_dio.oui iopriv.oui $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
radenvsrvroui.o : radenvsrvroui.c
herc_dio.o : herc_dio.cc
radenvtbl.tmc : radenv.tbl
-include radenvtbl.tmc.dep
radenvdisp.cc : base.tmc herc_ad.tmc /usr/local/share/huarp/flttime.tmc radenvtbl.tmc VERSION
	$(TMC) base.tmc herc_ad.tmc /usr/local/share/huarp/flttime.tmc radenvtbl.tmc
radenvdispoui.c : /usr/local/share/oui/cic.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) /usr/local/share/oui/cic.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
radenvdispoui.o : radenvdispoui.c
radenvdisp.o : radenvdisp.cc
radenvtblnc.tmc : radenv.tbl
-include radenvtblnc.tmc.dep
radenvdispnc.cc : base.tmc herc_ad.tmc /usr/local/share/huarp/flttime.tmc radenvtblnc.tmc VERSION
	$(TMC) base.tmc herc_ad.tmc /usr/local/share/huarp/flttime.tmc radenvtblnc.tmc
radenvdispncoui.c : /usr/local/share/oui/cic.oui $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) /usr/local/share/oui/cic.oui $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
radenvdispncoui.o : radenvdispncoui.c
radenvdispnc.o : radenvdispnc.cc
radenvalgoa.tmc : radenv.tma radenvsrvr
	$(SERVER) ./radenvsrvr
	$(TMCALGO) -V "`./radenvsrvr -R`" radenv.tma
radenvalgo.cc : base.tmc herc_ad.tmc radenvalgoa.tmc VERSION
	$(TMC) base.tmc herc_ad.tmc radenvalgoa.tmc
radenvalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
radenvalgooui.o : radenvalgooui.c
radenvalgo.o : radenvalgo.cc
radenvextedf.oui : radenv.edf
	$(EDF2OUI) radenv.edf
radenvext.tmc : radenv.edf
	$(EDF2EXT) radenv.edf
radenvext.cc : base.tmc herc_ad.tmc radenvext.tmc VERSION
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
clean-dist : clean
$(IGNOREFILE) : Makefile
	@for i in $(OBJECT) $(IGNORE) $(TARGET); do echo "$$i"; done >$(IGNOREFILE)
