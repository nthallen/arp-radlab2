#ifndef bmxstypedef_
#define bmxstypedef_

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#include <stdio.h>
//#define RECV_BUF_SIZE 100000
#define RECV_BUF_ELEMENTS 60000	// number of elements to be allocated in the buffer (multiply by appropriate type)
typedef float coad_t;
typedef short SINT16;

//! This struct is intended to help limit the number of items passed to a function.
typedef struct BmxsHelper{ 
	unsigned short numcoads;
	mlf_def_t *mlf;
	int startingpoint;
	int t_num_bytes;

	// buffers are now to be allocated with malloc to take them off the stack and put them in heap.
	union{
		// unsigned char rawbuffer[RECV_BUF_SIZE];
		unsigned char *rawbuffer;
	// SINT16 intbuffer[RECV_BUF_SIZE / sizeof(SINT16) ];
		SINT16 *intbuffer;
	} buffer;
	//coad_t coadbuf[RECV_BUF_SIZE / sizeof(SINT16) ]; // to get same number of elements as the intbuffer
	coad_t *coadbuf;
} bmxsStruct;

#endif
