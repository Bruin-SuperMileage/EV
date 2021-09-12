#ifndef MOTOR_H
#define MOTOR_H

#include <string>
#include <math.h>
using namespace std;

// Motor Data for 60LH351A
const double RPM_CONVERSION_CONSTANT = 0.10472;
const double VOLTAGE = 24;
const double NO_LOAD_SPEED = 4200; 
const double SPEED_TO_TORQUE_RATIO = 6.3; 
const double MAX_EFFIENCY = 92; 
const double SPEED_AT_RATED_POWER = 3289;
const double RATED_CURRENT = 19;
const double MOTOR_CONSTANT = 17.9;
const double WINDING_RESISTANCE = 0.186;
const double NO_LOAD_CURRENT = 0.24;
const double DAMPING_FACTOR = .2;
const double STATIC_FRICTION = 1;
const double VELOCITY_CONSTANT = 175;
const double TORQUE_CONSTANT = 7.71*0.00706;
const double ROTOR_INERTIA = 11.8;
const double INDUCTANCE = 0.00016;
const double GEAR_RATIO = 9;
const double MOMENT_INERTIA = 35*pow(0.1, 2); // TODO: check numeric values

class Ramping;

class motor
{
  public:
    // Constructor
    motor();

    // Simulation functions

    double get_force(int throttle, double velocity);
    double get_current(); 
    double get_voltage();
    double get_power();


  private:
    // Related objects
    Ramping* m_ramp;

    string rampingType;

    // Changing motor simulated values

      // Constant motor specs
    double m_motor_sprocket; 
    double m_gear_ratio;
    double m_wheel_sprocket; 
    double m_current;
    double m_voltage;

    //timing
    int m_step;
    double m_tic_length;

    //helper functions
    unsigned long get_time();
    double get_voltage(int throttle);
    double getTorque(int throttle, double velocity);
};

#endif