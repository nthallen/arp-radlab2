/* Hercules A/D */
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <errno.h>
#include <stdlib.h>
#include "nortlib.h"
#include "herc_ad.h"

/* Whether the range is actually P/M or just P is determined by the
   global bipolar/unipolar configuration. */
#define RANGE_PM_1_25 0x83
#define RANGE_PM_2_5 0x82
#define RANGE_PM_5 0x81
#define RANGE_PM_10 0x80
#define AD_HIGH_CHANNEL 15
#define AD_LOW_CHANNEL 0

static unsigned short Gain_Code[32] = {
  RANGE_PM_10, /*  0   Log Pressure  */
  RANGE_PM_10, /*  1 0-10V 1000 Torr */
  RANGE_PM_5,  /*  2 30K Therm 75K PU to 5V */
  RANGE_PM_10, /*  3 unused */
  RANGE_PM_5,  /*  4 30K Therm 75K PU to 5V */
  RANGE_PM_5,  /*  5 0-5V 0-1000 Torr */
  RANGE_PM_10, /*  6 unused */
  RANGE_PM_10, /*  7 unused */
  RANGE_PM_10, /*  8 unused */
  RANGE_PM_10, /*  9 unused */
  RANGE_PM_10, /* 10 unused */
  RANGE_PM_10, /* 11 unused */
  RANGE_PM_10, /* 12 unused */
  RANGE_PM_10, /* 13 unused */
  RANGE_PM_10, /* 14 unused */
  RANGE_PM_10, /* 15 unused */
  RANGE_PM_10, /* 16 unused */
  RANGE_PM_10, /* 17 unused */
  RANGE_PM_10, /* 18 unused */
  RANGE_PM_10, /* 19 unused */
  RANGE_PM_10, /* 20 unused */
  RANGE_PM_10, /* 21 unused */
  RANGE_PM_10, /* 22 unused */
  RANGE_PM_10, /* 23 unused */
  RANGE_PM_10, /* 24 unused */
  RANGE_PM_10, /* 25 unused */
  RANGE_PM_10, /* 26 unused */
  RANGE_PM_10, /* 27 unused */
  RANGE_PM_10, /* 28 unused */
  RANGE_PM_10, /* 29 unused */
  RANGE_PM_10, /* 30 unused */
  RANGE_PM_10  /* 31 unused */
};

static int int_id;
static unsigned short base = HERCULES_BASE_ADDR;

static const struct sigevent *herc_handler( void *area, int id ) {
  /* disable the counter */
  out8(HERCULES_BASE_ADDR+27,0x08);
  return NULL;
}

static void cleanup_herc_ad(void) {
  if (int_id != -1 && InterruptDetach(int_id) == -1 ) {
    nl_error( 2, "Error %d detaching interrupt", errno);
  }
}

void attach_herc_int( void ) {
  /* Attach the interrupt */
  ThreadCtl( _NTO_TCTL_IO, 0 );
  int_id = InterruptAttach(5, herc_handler, NULL, 0, 0);
  if ( int_id == -1 )
    nl_error( 3, "Error return %d from InterruptAttach", errno );
  if ( atexit(cleanup_herc_ad) == -1 )
    nl_error( 3, "Error return %d from atexit", errno );
}

void init_herc_ad( void ) {
  unsigned long sample_period = 8000; /* microseconds */
  int i;

  attach_herc_int();  
  /* Documented in section 10.1.2 of the Hercules Manual */
  out8(base+0, 0x40); /* Reset the data acquisition system */
  out8(base+0, 0x00); /* Select page zero: out8(base+0, 0x00) */
  // out8(base+1, 0x04); /* Configure A/D as Single-ended, bipolar. D/A unipolar (don't care) */
  out8(base+1, 0x07); /* Configure A/D as Differential, unipolar. D/A unipolar (don't care) */
  
  /* Configure the individual channel gains */
  for ( i = AD_LOW_CHANNEL; i <= AD_HIGH_CHANNEL; i++ ) {
    out8( base+2, i ); /* Select low channel */
    out8( base+4, Gain_Code[i] );
  }
  
  out8( base+2, AD_LOW_CHANNEL ); /* low channel */
  out8( base+3, AD_HIGH_CHANNEL ); /* High channel */
  out8( base+12, 0x49 ); /* Select individual channel gains, scan interval 9uS, Clk0 at 100KHz */

  /* Set up counter for sample_period */
  sample_period /= 10;
  out8( base+24, (unsigned char)(sample_period & 0xFF) );
  sample_period /= 0x100;
  out8( base+25, (unsigned char)(sample_period & 0xFF) );
  sample_period /= 0x100;
  out8( base+26, (unsigned char)(sample_period & 0xFF) );
  out8(base+27,0x02); /* Load the counter */

  out8( base+8, (AD_HIGH_CHANNEL-AD_LOW_CHANNEL)+1 ); out8( base+9, 0 ); /* Set FIFO threshold to one scan */
  out8( base+13, 0x19 ); /* AINTE, FIFOEN, CLKEN, CLKSEL Ctr0 */

  out8(base+27,0x04); /* Enable the Counter (and start converting) */
}

void read_herc_ad( unsigned short *cvals ) {
  int l;
  
  if ( (in8(base+14) & 0x12) == 0x12 ) {
    for ( l = AD_LOW_CHANNEL; l <= AD_HIGH_CHANNEL; l++ ) {
      cvals[l] = in16( base );
    }
    /* Check to see if FIFO is empty */
    if ( !(in8(base+14) & 1) ) {
      int n_xtra = 0;
      while ( !(in8(base+14) & 1)) {
        in16(base);
        ++n_xtra;
      }
      nl_error( 2, "FIFO was not empty: %d extra words", n_xtra );
      out8( base+2, 0 ); /* low channel */
    }
    out8(base+15,0x02); /* Clear A/D Interrupt Request */
    out8(base+27,0x02); /* Load the counter */
    out8(base+27,0x04); /* Enable the Counter */
  } else {
    nl_error( 1, "A/D Interrupt not pending\n" );
  }
}
