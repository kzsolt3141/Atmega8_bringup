/*
 * FIR_tools.h
 *
 * Created: 1/20/2017 9:16:30 PM
 *  Author: Zsolt
 */ 


#ifndef FIR_TOOLS_H_
#define FIR_TOOLS_H_

//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include <stdio.h>

//------------------------------------------------
//               DEFINES
//------------------------------------------------
#define H0 0.1
#define H1 0.2
#define H2 0.3
#define H3 0.3
#define H4 0.1

typedef struct {
	int16_t x0;
	int16_t x1;
	int16_t x2;
	int16_t x3;
	int16_t x4;
	float calcVal;
} FIR_delay;

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------
void FIR_update(FIR_delay *, int16_t * );

//------------------------------------------------
//               VARIABLES
//------------------------------------------------
FIR_delay fd;

#endif /* FIR_TOOLS_H_ */