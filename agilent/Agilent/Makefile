CPPFLAGS=-I/usr/local/include
CXXFLAGS=-Wall -g
LDFLAGS=-L/usr/local/lib -Wl,-rpath,/usr/local/lib
LIBS=-lsocket -ltm -ltmpp -lnort
include /usr/local/share/huarp/appgen.mk

.PHONY : clean

OBJS=agilentDriver.o tcp.o agilentoui.o
agilentDriver : $(OBJS)
	$(LINK.cc) -o agilentDriver $(OBJS) $(LIBS)
	usemsg agilentDriver agilentoui.c
agilentoui.c : agilent.oui
	$(OUI) agilent.oui
clean :
	rm *.o agilentDriver
