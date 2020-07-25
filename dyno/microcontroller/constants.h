/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* This file contains pin number declarations and other constants.     */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

const int POT_PIN = A0;
const int NUM_TEMP_SENSE = 5;
const int TEMP_PINS[NUM_TEMP_SENSE] = {A1, A2, A3, A4, A5}; //Use TMP36 sensors
const int DRV_PIN = 5;
const int POT_LOWER = 0;
const int POT_UPPER = 1023;
const int REPORT_PERIOD = 500; //in ms

#endif
