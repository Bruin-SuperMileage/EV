#include "physical_forces.h"
#include "physical_constants.h"
#include <iostream>
#include <math.h>


physical_forces::physical_forces(){}

double physical_forces::get_grav_x(double incline){
    double grav_force_x = -1.0 * CAR_MASS * GRAVITY * sin(incline);
    //cout << "GRAV FORCE: " << grav_force_x << endl;
    return grav_force_x;
}

double physical_forces::get_drag(double velocity){
    double drag_force =  -0.5*DRAG_CONSTANT*DRAG_AREA*FLUID_DENSITY*pow(velocity, 2);
    //cout << "DRAG FORCE: " << drag_force << endl;
    return drag_force;
}

double physical_forces::get_friction(double incline){
    double friction_force = -1.0 * get_normal_force(incline) * ROLLING_KINETIC_FRICTION;
    //cout << "FRICTION FORCE: " << friction_force << endl;
    return friction_force;
}

//private methods
double physical_forces::get_normal_force(double incline){
    double normal_force = CAR_MASS * GRAVITY * cos(incline);
    return normal_force;
}