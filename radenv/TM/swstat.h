/* swstat.h */
#ifndef SWSTAT_H_INCLUDED
#define SWSTAT_H_INCLUDED

typedef struct {
  unsigned short SWStat;
  unsigned short FlipState;
} __attribute__((packed)) swstat_t;
extern swstat_t SWData;

#define SWS_OK 0
#define SWS_IDLE 1
#define SWS_ACQUIRE 2

#define SWS_TIME_WARP 253
#define SWS_READFILE 254
#define SWS_SHUTDOWN 255

#endif
