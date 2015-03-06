#include <sys/neutrino.h>
#include <hw/inout.h>
#include <errno.h>
#include <string.h>
#include "herc_ad.h"
#include "nortlib.h"
    
void init_herc_dio(void) {
  out8(HERCULES_BASE_ADDR+22, 0x01); /* A output */
}

void herc_cmd( int bit, int val ) {
  if ( bit < 0 || bit > 5 )
    nl_error( 2, "Invalid bit to herc_cmd" );
  else {
    unsigned char vals, mask;
    vals = in8(HERCULES_BASE_ADDR+16);
    mask = 1<<bit;
    if ( val ) vals |= mask;
    else vals &= ~mask;
    out8(HERCULES_BASE_ADDR+16,vals);
  }
}
