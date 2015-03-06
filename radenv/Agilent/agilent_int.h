#ifndef AGILENT_INT_H_INCLUDED
#define AGILENT_INT_H_INCLUDED

#include "Selector.h"
#include "agilent.h"
#include "collect.h"

class agilent_ctrl;
class TMcollect : public Selectee {
  public:
    TMcollect();
    int ProcessData(int flag);
    int init(agilent_ctrl *par, const char *name, void *data, int data_size);
    int send();
  private:
    send_id TMid;
	agilent_ctrl *par;
};

class Quitter : public Selectee {
  public:
    Quitter();
    int ProcessData(int flag);
};

class agilent_ctrl : public Selectee {
  public:
    TMcollect TM;
    agilent_ctrl();
    int ProcessData(int flag);
    void Request(); // sends the READ? command
  private:
    static const int devicePort;
    static const char hostname[];
    static const int BUFFER_SIZE;
    char *buffer;
    agilent_t TMdata;
};



extern int tcp_create( const char *hostname, int tcp_port );
extern int tcp_send( const char *cmd, int cmdleng );
extern int tcp_receive( void *received_packet, int packet_size );
extern int tcp_close(void);

#endif

