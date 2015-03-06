
#ifndef bmxs_h
#define bmxs_h
//! Used to communicate pertinent data with telemetry
typedef struct{
	unsigned short resolution;
	char stat;
	unsigned short numcoads;
	unsigned short index;
	unsigned short channels;
} BMXS_t;

#define BMXS_ABSENT			0
#define BMXS_INITIALIZE 	1
#define BMXS_READY			2
#define BMXS_ACQUIRE		3
// acquire is set when first broadcast does not create a tcp connection
#define BMXS_TERMINATE		4

#endif
