
#include "motor.h"
#include "track.h"
#include "physical_forces.h"
#include "physical_constants.h"
#include <conio.h> //for khbit 
#include <algorithm>
#include <windows.h> 
#include <iostream>


#ifndef RUN_TYPES
#define RUN_TYPES

double run(motor* Motor, physical_forces* Phys, track* Track, double starting_speed, int lap_number, double &joules);
double simulated_run(motor* Motor, physical_forces* Phys, track* Track, double starting_speed, int lap_number, double &joules, double threshold, int run_distance, int coast_distance, string filename);
vector<double> coast(motor* Motor, physical_forces* Phys, track* Track, double &starting_speed, double &joules, int run_distance, int coast_distance);
vector<double> run_coast(motor* Motor, physical_forces* Phys, track* Track, double &starting_speed, double &joules, int run_distance, int coast_distance);
double getNewVelocity(double net_force, double old_velocity);

#endif