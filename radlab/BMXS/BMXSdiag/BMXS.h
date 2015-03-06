
#ifndef bmxs_h
#define bmxs_h

typedef struct{
	unsigned short resolution;
	char stat;
	unsigned short numcoads;
	unsigned short index;
} BMXS_t;

#define BMXS_ABSENT			0
#define BMXS_INITIALIZE 		1
#define BMXS_READY			2
#define BMXS_ACQUIRE		3
#define BMXS_TERMINATE		4

#endif
