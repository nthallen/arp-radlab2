/* herc_ad.h */
#ifndef HERC_AD_H_INCLUDED
#define HERC_AD_H_INCLUDED

#define HERCULES_BASE_ADDR 0x240

#ifdef __cplusplus
extern "C" {
#endif

void init_herc_dio( void );
void herc_cmd( int bit, int val );
void init_herc_ad( void );
void read_herc_ad( unsigned short *cvals );

#ifdef __cplusplus
};
#endif

#endif
