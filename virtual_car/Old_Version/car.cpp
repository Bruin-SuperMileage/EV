#include "car.h"
#include "track.h"
#include <math.h>
#include <iostream>
//#include <algorithm.h>
using namespace std;

car::car(track* Track): m_track(Track)
{
    m_mass = 0; // kg
    m_gravity = -9.81; //m/s^2
    m_s = 0; // m
    m_v = 0; // m/s
    m_a = 0; // m/s^2
    m_altitude = 0; // m above starting point
    set_orientation(0); // radians
    m_throttle = 0; // m/s^2?
    m_engine_force = 0; // N
    m_net_force_x = 0; // N
    m_net_force_y = 0; // N
    m_power = 0; // W
    m_c_rolling_resistance = 0; // unitless
    m_c_drag = 0; // unitless
    m_drag_force = 0 ; // N
    m_drag_area = 0; // m^2

    //Implement GPS Struct to keep track of internal position 
}

//auxillary functions
void car::update_net_force()
{
    m_net_force_x = get_frictional_force() + m_drag_force + m_gravitational_force_x + m_engine_force;
    //cout << "drag force: " << m_drag_force << endl;
    //cout << "Grav Force: " << m_gravitational_force_x << endl;
    //cout << "Engine force: " << m_engine_force << endl;
    m_net_force_y = m_gravitational_force_y + m_normal_force;
}

  // accessor methods
double car::get_mass() {return m_mass;}
double car::get_distance() {return m_s;}
double car::get_velocity() {return m_v;}
double car::get_acceleration() {return m_a;}
double car::get_altitude() {return m_altitude;}
double car::get_orientation() {return m_orientation;}
double car::get_throttle() {return m_throttle;}
double car::get_engine_force() {return m_engine_force;}
double car::get_gravitational_force_x() {return m_gravitational_force_x;}
double car::get_gravitational_force_y() {return m_gravitational_force_y;}
double car::get_normal_force() {return m_normal_force;}

double car::get_frictional_force()
{
    cout << "Car Velocity: " << m_v << endl;
    if (m_v==0)
        return (-1.0 * m_track->get_c_static_friction())*m_normal_force; // opposes other forces
    else if (m_v > 0)
        return (-1.0 * m_track->get_c_dynamic_friction())*m_normal_force;
    else
        return m_track->get_c_dynamic_friction()*m_normal_force;
}
double car::get_net_force_x() {
    update_net_force();
    return m_net_force_x;
}
double car::get_net_force_y() {
    update_net_force();
    return m_net_force_y;
}

double car::get_power() {return m_power;}
double car::get_c_rolling_resistance() {return m_c_rolling_resistance;}
double car::get_c_drag() {return m_c_drag;}
double car::get_drag_area() {return m_drag_area;}
double car::get_drag_force() {return m_drag_force;}

  // mutator methods
void car::set_mass(double m)
{
    m_mass = m;
    set_orientation(m_orientation); //must change values that depend on mass
    update_net_force();
}
void car::climb(double d) {m_altitude += d;}
void car::set_orientation(double o)
{
    m_orientation = o;
    m_gravitational_force_x = m_mass * m_gravity * sin(m_orientation);
    m_gravitational_force_y = m_mass * m_gravity * cos(m_orientation);
    m_normal_force = (-1.0) * m_gravitational_force_y;
    update_net_force();
}
void car::set_throttle(double t) {m_throttle = t;}
void car::set_engine_force(double ef)
{
    m_engine_force = ef;
    update_net_force();
}
void car::set_power(double p) {m_power = p;}
void car::set_c_rolling_resistance(double cr){m_c_rolling_resistance = cr;}
void car::set_c_drag(double cd) {m_c_drag = cd;}
void car::set_drag_area(double da) {m_drag_area = da;}
void car::set_drag_force(double df) {m_drag_force = df;}
void car::travel(double d) {m_s += d;}
void car::set_velocity(double v) {m_v = v;}
