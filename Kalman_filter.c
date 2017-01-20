/*
 * Kalman_filter.c
 *
 * Created: 1/19/2017 10:35:57 PM
 *  Author: Zsolt
 */ 
//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include "Kalman_filter.h"

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------

//------------------------------------------------
//                void kalman_init(kalman_state*, float, float, float, float);
//------------------------------------------------
//initialize Kalman filter parameters
void kalman_init(kalman_state * ks, float q, float r, float p, float intial_value)
{
  ks->q = q;
  ks->r = r;
  ks->p = p;
  ks->x = intial_value;
}

//------------------------------------------------
//                void kalman_update(kalman_state* , int16_t*);
//------------------------------------------------
//update Kalman filter parameters with new measurement
void kalman_update(kalman_state* state, int16_t* measurement)
{
  //prediction update
  //omit x = x
  state->p = state->p + state->q;

  //measurement update
  state->k = state->p / (state->p + state->r);
  state->x = state->x + state->k * ((*measurement) - state->x);
  state->p = (1 - state->k) * state->p;
}