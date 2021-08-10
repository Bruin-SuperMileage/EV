
#include "motor.h"
#include "track.h"
#include "physical_forces.h"
#include "physical_constants.h"
#include <conio.h> //for khbit 
#include <algorithm>
#include <windows.h> 
#include <iostream>



double run_lap(motor* Motor, physical_forces* Phys, track* Track, double starting_speed)
{      
    double time = 0.0;
    double incline = 0.0;
    int throttle = 0;

    double velocity = starting_speed;
    double acceleration = 0.0;
    double distance = 0.0;

        
    //auto start = chrono::high_resolution_clock::now();
    //int tics = 0;
    while(distance < Track->get_track_length())
    {
        //double u = Car->get_velocity();
        //grab last velocity

        //grab track conditions
        
        

        if(!kbhit()){
            throttle = 0; //don't add to engine if not pressed

        }
        else
            if(getch() == 'a'){ //use getch() for real time run
            throttle = 250; //sets force ie engine is pressed
            //cout << "Engine Pressed" << endl;
            }
            
        incline = Track->get_incline();
        double net_force = Motor->get_force(throttle, velocity) + Phys->get_grav_x(incline) + Phys->get_drag(velocity) + Phys->get_friction(incline);

        acceleration = net_force / CAR_MASS;
        velocity = max(0.0, velocity + acceleration * TIC_LENGTH);
        distance += velocity * TIC_LENGTH;

        
        cout << "   Velocity: " << velocity << endl;
        cout << "   Distance: " << distance << endl;
        

        Track->update_coordinates(distance);
        
        //adds to total time of run
        time += TIC_LENGTH;

        Sleep(15); //give program enough time to register next keyboard input

        //TIMING TEST///////////////////////////
        
        #ifdef TIME
        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = finish - start;

        cout << elapsed.count() << endl;
        #endif    
        //cout << "time: " << t << " s"<< endl;
        //cout << "average velocity: " << v*2.237 << " mph" << endl;
        //cout << "distance traveled: " << s << " m" << endl;
        //cout << "Time: " << elapsed.count() << endl;
    }
    //cout << tics << endl;
    
    return time;
}


//TODO: CHANGE THE VELOCITY TO LINE UP WITH RUNGE KUTTA
double getNewVelocity(double net_force, double old_velocity){

//update parameters
    double acceleration = net_force / CAR_MASS;

    // Calculate c1, c2, c3, c4
    double c1 = acceleration*1;
    double c2 = acceleration*(1+c1/2);
    double c3 = acceleration*(1+c2/2);
    double c4 = acceleration*(1+c3);
        
    // Calculate instanteous rpm 
    double new_velocity = c1/6 + c2/3 + c3/3 + c4/6 + old_velocity;
    return new_velocity;
}





int main(){

    cout << "Made it to Main" << endl;
    double total_distance = 0.0;
    double average_velocity = 0.0;
    double time = 0;

    //TODO: Make these user inputs
    double current_speed = 0.0;
    int lap_number = 1;

    physical_forces* Phys = new physical_forces;
    cout << "made it past phys forces" << endl;
    motor* Motor = new motor;
    cout << "made it past motor" << endl;
    track* Track = new track;
    cout << "made it past track" << endl;

    for(int i=0;i<lap_number;i++) {
            cout << "made it to for loop" << endl;
            time += run_lap(Motor, Phys, Track, current_speed);
            total_distance += Track->get_track_length();
    }
    
    cout << "made it out of for loop" << endl;
    average_velocity = total_distance/time;
    return 0;
}