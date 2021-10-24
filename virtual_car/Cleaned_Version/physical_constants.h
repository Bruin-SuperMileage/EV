#ifndef PHYSICAL_CONSTANTS_H
#define PHYSICAL_CONSTANTS_H

const double GRAVITY = 9.81;
const double ROLLING_KINETIC_FRICTION = 0.015; //change to typical value for asphalt
const double CAR_MASS = 80; //taken from 2019 car, change to variable in main later
const double DRAG_CONSTANT = 0.5;
const double DRAG_AREA = 0.15;
const double FLUID_DENSITY = 1.292; //typical value for air at room pressure and standard atm press.
const double TIC_LENGTH = 0.03125; //Tic length
const double WHEEL_RADIUS = 0.5; // Need to calculate or find out for torque -> force calculation 
const double MILES_PER_KWH_CONVERSION = 2236.94;

#endif