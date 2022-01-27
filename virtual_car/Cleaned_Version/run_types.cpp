#include "run_types.h"
#include <fstream>
#define VERBOSE 1
#define VELOCITY 0
#define JOULES_100 3
#define JOULES_10 2
#define TIME_10 1
#define TIME_100 4

double get_kinetic_energy(double v_i, double v_f){
   double KE_init = 0.5*CAR_MASS*v_i*v_i;
   double KE_final = 0.5*CAR_MASS*v_f*v_f;
   return KE_final - KE_init;
}

vector<double> coast(motor* Motor, physical_forces* Phys, track* Track, double &starting_speed, double &joules_lost, int run_distance, int coast_distance){

    double time = 0.0;
    double incline = 0.0;
    double joules_10 = 0.0;
    //double joules_lost = 0.0;
    int throttle = 0;
    vector<double> ret;

    double velocity = starting_speed;
    double acceleration = 0.0;
    double distance = 0.0;
    double total_distance = run_distance + coast_distance;

    while(distance < total_distance){
            
        incline = Track->get_incline();
        double net_force = Motor->get_force(0, velocity) + Phys->get_grav_x(incline) + Phys->get_drag(velocity) + Phys->get_friction(incline);

        acceleration = net_force / CAR_MASS;
        double init_velocity = velocity;
        velocity = max(0.0, velocity + acceleration * TIC_LENGTH);
        distance += velocity * TIC_LENGTH;

        if(distance > run_distance){
            ret.push_back(velocity);
            ret.push_back(time);
            ret.push_back(joules_10);
        }

        Track->update_coordinates(distance);

        //TODO: FIX THIS LINE
        joules_10 +=  max(0.0, Motor->get_power() * TIC_LENGTH);
        joules_lost += max(0.0, Motor->get_power() * TIC_LENGTH) - get_kinetic_energy(init_velocity, velocity);
            
        time += TIC_LENGTH;

        if(VERBOSE){
            cout << "Made it to Coast" << endl;
            cout << "   Velocity: " << velocity << endl;
            cout << "   Distance: " << distance << endl;
            cout << "Power Consumption: " <<  Motor->get_power() * TIC_LENGTH << endl;
            cout << "Joules Lost: " << joules_lost << endl;
            cout << "Kinetic Energy Delta: " << get_kinetic_energy(init_velocity, velocity) << endl;
        }

        //if car comes to a stop everything will return -1
        if(velocity == 0){
            if(distance < run_distance){
                ret.push_back(-1);
                ret.push_back(-1);
            }
            ret.push_back(-1);
            return ret;
        }
            
    }
    ret.push_back(joules_lost);
    ret.push_back(time);
    return ret;
}

vector<double> run_coast(motor* Motor, physical_forces* Phys, track* Track, double &starting_speed, double &joules_lost, int run_distance, int coast_distance){

    double time = 0.0;
    double incline = 0.0;
    double joules_10 = 0.0;
    //double joules_lost = 0.0;
    int throttle = 0;


    double velocity = starting_speed;
    double acceleration = 0.0;
    double distance = 0.0;
    vector<double> ret;

    while(distance < run_distance){

        incline = Track->get_incline();
        double net_force = Motor->get_force(255, velocity) + Phys->get_grav_x(incline) + Phys->get_drag(velocity) + Phys->get_friction(incline);

        acceleration = net_force / CAR_MASS;
        double init_velocity = velocity;
        velocity = max(0.0, velocity + acceleration * TIC_LENGTH);
        distance += velocity * TIC_LENGTH;

        Track->update_coordinates(distance);

        //TODO: FIX THIS LINE

        //Calculates the amount of energy expended in the first 10 meters
        joules_10 += max(0.0, Motor->get_power() * TIC_LENGTH);

        //Calculates the energy dissipated
        joules_lost += max(0.0, Motor->get_power() * TIC_LENGTH) - get_kinetic_energy(init_velocity, velocity);
        

        time += TIC_LENGTH;


        if(VERBOSE){
            cout << "   Velocity: " << velocity << endl;
            cout << "   Distance: " << distance << endl;
            cout << "Made it to Run 10" << endl;
            cout << "Joules Generated: " <<  Motor->get_power() * TIC_LENGTH << endl;
            cout << "Joules Lost: " << joules_lost << endl;
            cout << "Kinetic Energy: " << get_kinetic_energy(init_velocity, velocity) << endl;
        }
    }

    ret.push_back(velocity);
    ret.push_back(time); //10 meter time
    ret.push_back(joules_10); //joules created in 10 meters
    ret.push_back(joules_lost); //

    while(distance < run_distance + coast_distance){

        incline = Track->get_incline();
        double net_force = Motor->get_force(0, velocity) + Phys->get_grav_x(incline) + Phys->get_drag(velocity) + Phys->get_friction(incline);

        acceleration = net_force / CAR_MASS;
        double init_velocity = velocity;
        velocity = max(0.0, velocity + acceleration * TIC_LENGTH);
        distance += velocity * TIC_LENGTH;

        Track->update_coordinates(distance);

        joules_lost += max(0.0, Motor->get_power() * TIC_LENGTH) - get_kinetic_energy(init_velocity, velocity);
        time += TIC_LENGTH;

        if(VERBOSE){
            cout << "   Velocity: " << velocity << endl;
            cout << "   Distance: " << distance << endl;
            cout << "Made it to Run 100" << endl;
            cout << "Joules Generated: " <<  Motor->get_power() * TIC_LENGTH << endl;
            cout << "Joules Lost: " << joules_lost << endl;
            cout << "Kinetic Energy: " << get_kinetic_energy(init_velocity, velocity) << endl;
        }

        
        if(velocity == 0){
            if(distance < run_distance){
                ret.push_back(-1);
                ret.push_back(-1);
            }
            ret.push_back(-1);
            return ret;
        }
    }
    ret.push_back(time); //100 meter time


    return ret;
}


double simulated_run(motor* Motor, physical_forces* Phys, track* Track, double starting_speed, int lap_number, double &joules, double threshold, int run_distance, int coast_distance, string filename){

    double time = 0.0;
    double incline = 0.0;
    int throttle = 0;
    double distance = 0.0;

    double velocity = starting_speed;
    double acceleration = 0.0;
    
    int cur_lap = 0;

    track cur_track = *Track;
    track track_run;
    track track_coast;

    double cur_speed = starting_speed;
    double speed_run;
    double speed_coast;
    

    double cur_joules = joules;
    int joules_lost = 0;
    double joules_run;
    double joules_coast;
    

    //TESTING INTS
    int coast_num = 0;
    int run_num = 0;

    while(cur_lap < lap_number)
        {

            // TODO: MAKE ASSIGNMENT OPERATOR FOR TRACK (AND ANYTHING ELSE WE NEED) 

            //Update data from Selected Run
            track_run = cur_track;
            track_coast = cur_track;

            speed_run = cur_speed;
            speed_coast = cur_speed;

            
            joules_run = cur_joules;
            joules_coast = cur_joules;

            //Runs with either pressing accelerator or coasting
            vector<double> run_data = run_coast(Motor, Phys, &track_run, speed_run, joules_run, run_distance, coast_distance);
            vector<double> coast_data = coast(Motor, Phys, &track_coast, speed_coast, joules_coast, run_distance, coast_distance);
            distance += run_distance;

            double time_diff =  run_data[TIME_100] - coast_data[TIME_100];
            double joules_diff = run_data[JOULES_100] - coast_data[TIME_100];
           
            double ratio = joules_diff / time_diff;

            if(VERBOSE){
                cout << "   Velocity: " << velocity << endl;
                cout << "   Distance: " << distance << endl;
                cout << "Ratio: " << ratio << endl;
            }

            ofstream file;
            file.open("./results/" + filename + ".txt", fstream::app);
            file.precision(4);

            file << "Current Velocity: " << cur_speed << "\t";
            file << "Joules Lost Run: " << run_data[TIME_100] << "\t";
            file << "Joules Lost Coast: " << coast_data[TIME_100] << "\t";

           if(ratio > threshold || coast_data[TIME_10] == -1 || coast_data[TIME_100] == -1){
                cur_track = track_run;
                cur_speed = run_data[VELOCITY];
                cur_joules = run_data[JOULES_10];
                time += run_data[TIME_10];
                run_num++;

                file << "Final Velocity: " << run_data[VELOCITY] << "\t" << "Power Conmsumption: " << cur_joules << "\t";
                file << "Distance: " << distance << "\t" << "Time: " <<  run_data[2] << "\t";
                file << "Run  " << "\t";
            }

           else{
                cur_track = track_coast;
                cur_speed = coast_data[VELOCITY];
                cur_joules = coast_data[JOULES_10];
                time += coast_data[TIME_10];
                coast_num++;

                file << "Final Velocity: " << coast_data[0] << "\t" << "Power Consumption: " << cur_joules << "\t";
                file << "Distance: " << distance << "\t" << "Time: " <<  coast_data[2] << "\t";
                file << "Coast" << "\t";
           }

            file << endl;
            file.close();

            //grab track conditions
            if(distance > Track->get_track_length()){
                distance -= Track->get_track_length();
                cur_lap++;
            }

        }
    
    cout << "Runs: " << run_num << endl;
    cout << "Coasts: " << coast_num << endl;

    joules = cur_joules;
    return time;
}


double run(motor* Motor, physical_forces* Phys, track* Track, double starting_speed, int lap_number, double &joules)
{      
    double time = 0.0;
    double incline = 0.0;
    int throttle = 0;

    double velocity = starting_speed;
    double acceleration = 0.0;
    double distance = 0.0;
    int cur_lap = 0;

        
    //auto start = chrono::high_resolution_clock::now();
    //int tics = 0;
    while(cur_lap < lap_number)
    {
        //double u = Car->get_velocity();
        //grab last velocity
        cout << cur_lap << endl;

        if(!kbhit()){
            throttle = 0; //don't add to engine if not pressed

        }
        else
            if(getch() == 'a'){ //use getch() for real time run
            throttle = 250; //sets force ie engine is pressed
            //cout << "Engine Pressed" << endl;
            }

        //Get incline of the car based on current track position    
        incline = Track->get_incline();

        //Calculate total forces from all sources being enacted on the car
        double net_force = Motor->get_force(throttle, velocity) + Phys->get_grav_x(incline) + Phys->get_drag(velocity) + Phys->get_friction(incline);

        acceleration = net_force / CAR_MASS;
        velocity = max(0.0, velocity + acceleration * TIC_LENGTH);
        distance += velocity * TIC_LENGTH;
        

        Track->update_coordinates(distance);

        //grab track conditions
        if(distance > Track->get_track_length()){
            distance -= Track->get_track_length();
            cur_lap++;
        }
        
        //Updates energy output of run
        joules += Motor->get_current() * velocity * TIC_LENGTH;

        //adds to total time of run
        time += TIC_LENGTH;

        if(VERBOSE){
            cout << "   Velocity: " << velocity << endl;
            cout << "   Distance: " << distance << endl;
            cout << "Joules: " << joules << endl;
        }

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


