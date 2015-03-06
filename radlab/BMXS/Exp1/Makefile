# Makefile
# For BMXSD
#
CPPFLAGS = -I /usr/local/include
CFLAGS = -Wall -g
LDFLAGS = -L/usr/local/lib
LIBS = -ltm -lnort -lsocket

bmxsd: udomain.o tcp.o bom_socket.o udp.o packet_reader.o user.o bmxsoui.o
	gcc -o bmxsd $(LDFLAGS) $(CFLAGS) udomain.o tcp.o udp.o packet_reader.o bom_socket.o user.o bmxsoui.o $(LIBS)
	usemsg bmxsd bmxsoui.c
user.o: bmxs_all.h user.c

tcp.o: bmxs_all.h tcp.c

udp.o: bmxs_all.h udp.c

bom_socket.o: bmxs_all.h bom_socket.c 

packet_reader.o: bmxs_all.h packet_reader.c 

udomain.o: bmxs_all.h udomain.c 

bmxsoui.c : bmxsdrv.oui
	oui -o bmxsoui.c	bmxsdrv.oui
	
update:
	cp bmxsd /home/BMXSdiag/bin/1.0
	
updategse:
	cp bmxsd /net/radgse/home/BMXSdiag/bin/1.0

clean:
	rm *.o bmxsd
