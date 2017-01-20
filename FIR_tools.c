/*
 * FIR_tools.c
 *
 * Created: 1/20/2017 9:16:44 PM
 *  Author: Zsolt
 */ 
//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include "FIR_tools.h"

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------

//------------------------------------------------
//                void FIR_update(FIR_delay *, int16_t *)
//------------------------------------------------
//update FIR with the new raw value
void FIR_update(FIR_delay * fp, int16_t *rawValue)
{
	fp->x4 = fp->x3;
	fp->x3 = fp->x2;
	fp->x2 = fp->x1;
	fp->x1 = fp->x0;
	fp->x0 = *rawValue;
	fp->calcVal = fp->x0 * H0 + fp->x1 * H1 + fp->x2 * H2 + fp->x3 * H3 + fp->x4 * H4;
}
