/*
 * Kalman_filter.h
 *
 * Created: 1/19/2017 10:35:33 PM
 *  Author: Zsolt
 */ 


#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_

//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include <stdio.h>

//------------------------------------------------
//               DEFINES
//------------------------------------------------
typedef struct {
  float q; //process noise covariance
  float r; //measurement noise covariance
  float x; //value
  float p; //estimation error covariance
  float k; //kalman gain
} kalman_state;

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------
void kalman_init(kalman_state*, float, float, float, float);
void kalman_update(kalman_state* , int16_t*);

//------------------------------------------------
//               VARIABLES
//------------------------------------------------


#endif /* KALMAN_FILTER_H_ */