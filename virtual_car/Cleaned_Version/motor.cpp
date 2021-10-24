#include <math.h>
#include <string>
#include <iostream>
#include <chrono>
#include <time.h>
#include <ctime>
#include <algorithm>

#include "motor.h"
#include "physical_constants.h"
//#include "rampingCopy.h" //ADD THIS IN AND BE LINEAR 

using namespace std;

motor::motor() // Need to add parameter to choose rampingType
{
    // TODO: Add in a way to choose which type of ramping function the user wants 
    rampingType = "Linear";
    if (rampingType == "Linear")
    {
        m_ramp = nullptr;
    }
    //m_tic_length = 0.03125; //Tic length
    // TODO: possibly set calculated motor specs here by calling functions
}


double motor::get_voltage(int throttle) //throttle will be taken from UI (IDK how that will be implemented)
{
    //int speed = m_ramp->newSpd(throttle, get_time());
    double voltage = (throttle * 24)/255 ; //converts speed into a percentage of battery
    return voltage;
}

double motor::get_current() {return m_current;}
double motor::get_voltage() {return m_voltage;}
double motor::get_power() {return m_current * m_voltage;}

// Automatically updates m_rpm
double motor::getTorque(int throttle, double velocity)
{  
    m_voltage = get_voltage(throttle);
    double numIter = 1; //maybe change to TIC_LENGTH/Step_size in the future
    double angularVelocity = velocity / WHEEL_RADIUS;
    
    // Update values
    double deltaV = m_voltage - angularVelocity/(VELOCITY_CONSTANT*RPM_CONVERSION_CONSTANT);
    m_current = deltaV/sqrt(pow(WINDING_RESISTANCE,2) + pow(angularVelocity*INDUCTANCE, 2));
    double torque = TORQUE_CONSTANT*m_current*GEAR_RATIO;

   // cout << "m_current: " << m_current << endl;
   // cout << "deltaV: " << deltaV << endl;
   // cout << "angularVelocity: " << angularVelocity << endl;


    /*
    cout << "Voltage: " << voltage << endl;
    cout << "DeltaV: " << deltaV << endl;
    cout << "Current: " << m_current << endl;
    */

    return torque;
}

double motor::get_force(int throttle, double current_velocity) 
{
    // Compute and return motor output force
    double torque = getTorque(throttle, current_velocity);
    double force = max(0.0, torque/WHEEL_RADIUS);
    //cout << "Motor Force: " << force << endl;
    /*
        cout << "Torque: " << torque << endl;
        cout << "Engine Force: " << force << endl;
    */
    return force;
}

