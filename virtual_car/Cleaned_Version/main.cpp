
#include "motor.h"
#include "track.h"
#include "physical_forces.h"
#include "physical_constants.h"
#include "run_types.h"
#include <conio.h> //for khbit 
#include <algorithm>
#include <windows.h> 
#include <iostream>
#include <fstream>

int main(){

    double total_distance = 0.0;
    double average_velocity = 0.0;
    double time = 0;
    int lap_number;
    double joules = 0.0;
    int run_distance = 0;
    int coast_distance = 0;
    double threshold = 0;
    string filename;

    //TODO: Make these user inputs
    double current_speed = 0.0;



    string start = "";
    cout << "Hit 'a' to begin simulation, 'b' for run 10 coast 90 test, 'c' for coast test, 't for current test, 'l' for one lap test, (or 'q' to quit)" << endl;
    cin >> start;

    if(tolower(start[0]) == 'q')
        cout << "Simulation Quit";
    
    if(tolower(start[0]) == 'a'){

        cout << "Input Lap Number" << endl;
        cin >> lap_number;

        physical_forces* Phys = new physical_forces;
        motor* Motor = new motor;
        track* Track = new track;

        time = run(Motor, Phys, Track, current_speed, lap_number, joules);
        total_distance = Track->get_track_length() * lap_number;

        average_velocity = total_distance/time;

        cout << "Time: " << time << endl;
        cout << "Ave Velocity: " << average_velocity << endl;
        cout << "Joules: " << joules << endl;
    }

    if(tolower(start[0]) == 'c'){
        physical_forces* Phys = new physical_forces;
        motor* Motor = new motor;
        track* Track = new track;

        

        cout << "Input Run Distance" << endl;
        cin >> run_distance;

        cout << "Input Coast Distance" << endl;
        cin >> coast_distance;
        
        current_speed = 15.00;
        vector<double> coast_data;
        coast_data = coast(Motor, Phys, Track, current_speed, joules, run_distance, coast_distance);

        total_distance = 100.00;
        average_velocity = total_distance/time;

        cout << "Time: " << time << endl;
        cout << "Ave Velocity: " << average_velocity << endl;
        cout << "Joules: " << joules << endl;
    }

    if(tolower(start[0]) == 'b'){
        physical_forces* Phys = new physical_forces;
        motor* Motor = new motor;
        track* Track = new track;
        
        current_speed = 15.00;

        cout << "Input Run Distance" << endl;
        cin >> run_distance;

        cout << "Input Coast Distance" << endl;
        cin >> coast_distance;

        vector<double> run_data = run_coast(Motor, Phys, Track, current_speed, joules, run_distance, coast_distance);

        total_distance = 100.00;
        average_velocity = total_distance/run_data[2];
        double miles_per_kwh = total_distance/run_data[1]*MILES_PER_KWH_CONVERSION;

        cout << "Time: " << run_data[2] << endl;
        cout << "Ave Velocity: " << average_velocity << endl;
        cout << "Joules: " << joules << endl;
    }

    if(tolower(start[0]) == 't'){
        cout << "Input Lap Number" << endl;
        cin >> lap_number;

        cout << "Input Run Distance" << endl;
        cin >> run_distance;

        cout << "Input Coast Distance" << endl;
        cin >> coast_distance;

        cout << "Input Threshold" << endl;
        cin >> threshold;

        cout << "Input Output Filename" << endl;
        cin >> filename;

        physical_forces* Phys = new physical_forces;
        motor* Motor = new motor;
        track* Track = new track;

        time = simulated_run(Motor, Phys, Track, current_speed, lap_number, joules, threshold, run_distance, coast_distance, filename);
        total_distance = Track->get_track_length() * lap_number;

        average_velocity = total_distance/time;
        double miles_per_kwh = total_distance/joules*MILES_PER_KWH_CONVERSION;

        ofstream file;
        file.open("./results/" + filename + ".txt", fstream::app);
        file << "Time: " <<  time  << endl << average_velocity << endl << "M/KWH: " << miles_per_kwh << endl;
        file.close();

        cout << "Time: " << time << endl;
        cout << "Ave Velocity: " << average_velocity << endl;
        cout << "M/KWH: " << miles_per_kwh << endl;
    }

    if(tolower(start[0]) == 'l'){
        lap_number = 1;
        run_distance = 10;
        coast_distance = 90;
        threshold = 87;
        filename = "CurrentTest";

        physical_forces* Phys = new physical_forces;
        motor* Motor = new motor;
        track* Track = new track;

        time = simulated_run(Motor, Phys, Track, current_speed, lap_number, joules, threshold, run_distance, coast_distance, filename);
        total_distance = Track->get_track_length() * lap_number;

        average_velocity = total_distance/time;
        double miles_per_kwh = total_distance/joules*MILES_PER_KWH_CONVERSION;

        ofstream file;
        file.open("./results/" + filename + ".txt", fstream::app);
        file << "Time: " <<  time  << endl << average_velocity << endl << "M/KWH: " << miles_per_kwh << endl;
        file.close();

        cout << "Time: " << time << endl;
        cout << "Ave Velocity: " << average_velocity << endl;
        cout << "M/KWH: " << miles_per_kwh << endl;
    }
    

    return 0;
}
