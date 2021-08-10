#include "car.h"
#include "track.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <math.h>
#include <string>

using namespace std;

void check_input()
{
    if(!cin)
    {
        std::cout << "Invalid Input" << endl;
        exit(1);
    }
}

int main()
{
    track* t = new track; 
    car* c = new car(t);

    std::cout.setf(ios::fixed);
    std::cout.precision(2);

    std::cout << "Choose a car:" << endl << "Press 1 for 2019 Car" << endl << "Press 0 for car information" << endl; //include other options later
    int car_choice;
    cin >> car_choice;
    check_input();
    while(car_choice==0){
        std::cout << "2019 Car:" << endl;
        std::cout << "Weight: 73 pounds" << endl << endl;
        //add other specs when we get them, like crr, drag coeff, wheel radius perhaps
        std::cout << "Choose a car:" << endl << "Press 1 for 2019 Car" << endl << "Press 0 for car information" << endl;
        cin >> car_choice;
        check_input();
    }
    if(car_choice==1){
        c->set_mass(33.11);
    }else{
        std::cout << "Invalid choice" << endl;
        exit(1);
    }
    std::cout << "Enter speed in miles per hour (15 mph suggested):" << endl;
    double speed_choice;
    cin >> speed_choice;
    check_input();
    speed_choice = speed_choice/2.237; //convert to m/s

    std::cout << "Enter number of laps:" << endl;
    int lap_choice;
    cin >> lap_choice;
    check_input();
    if (lap_choice<0)
    {
        std::cout << "Invalid choice" << endl;
        exit(1);
    }
    
    double time = 0.0;
    double l = 0.0;
    double v = 0.0;
    for(int i=0;i<lap_choice;i++) {
        time += t->time_to_run(c, speed_choice);
        l += t->get_total_length();
        v = l/time;
    }
    
    //output to text file
    ofstream outdata;
    ofstream updatedata;

    ifstream fin("current_trial.txt");

    int trial_number;
    fin >> trial_number;
    string trial_name = "Trial" + to_string(trial_number) + ".txt";

    //FILE PATHS NEED TO BE UPDATED
    outdata.open("C:\\Users\\jsand\\OneDrive\\Documents\\SMV\\Virtual_Car\\Virtual-Car\\Trials\\" + trial_name);
    updatedata.open("C:\\Users\\jsand\\OneDrive\\Documents\\SMV\\Virtual_Car\\Virtual-Car\\current_trial.txt");

    //Writes to trial files
    if(!outdata){
        std::cout << "Error: Invalid File" << endl;
        exit(2);
    }
    else
        outdata << "Spd;" << v*2.237 << ";Lat;" << l << ";Time;" << time << endl;
    
    //Updates current trial number
    if(!updatedata){
    std::cout << "Error: Invalid File" << endl;
    exit(2);
    }
    else
        updatedata << trial_number+1 << endl;



    std::cout << "time: " << time << " s"<< endl;
    std::cout << "average velocity: " << v*2.237 << " mph" << endl;
    std::cout << "distance traveled: " << l << " m" << endl;
    delete c;
    delete t;
}
