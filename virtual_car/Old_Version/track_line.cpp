#include "track.h"
#include "car.h"
#include "physics.h"
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <chrono>  // for high_resolution_clock
#include <algorithm> 
#include <windows.h> 

//#define TIME 1; //uncomment to see live time readings

using namespace std;

track::track()
{


    ifstream raw_data("sonoma.csv"); //reading in all the coordinates

    while(true) //assigning value to all coordinates 
    {
        string s;
        raw_data >> s;
        if(s=="") break;
        string delimiter = ",";
        vector<double> temp;
        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            temp.push_back(stod(token));
            s.erase(0, pos + delimiter.length());
        }
        temp.push_back(stod(s));

        m_coordinates.push_back(temp);
        
        if(raw_data.eof()) break;
    }

    m_c_static_friction = 0.7; //change to typical value for asphalt
    m_c_dynamic_friction = 0.6; //change to typical value for asphalt
    m_fluid_density = 1.292; //typical value for air at room pressure and standard atm press.
    m_total_length = 0.0;
    m_tic_length = 0.03125; //Tic length
    m_coord_number = 0;
    m_current_coord = m_coordinates[m_coord_number];
    m_next_coord = m_coordinates[m_coord_number + 1];
    m_incline = incline_between_coordinates(&m_current_coord, &m_next_coord);
    m_coord_angle = angle_between_coordinates(&m_current_coord, &m_next_coord);

    if(m_current_coord[0] > m_next_coord[0])
        m_direction = -1;
    else
        m_direction = 1;

    for (int i=0; i < m_coordinates.size()-1; i++) //calculating total length
    {
        double d = distance_between_coordinates(&m_coordinates[i], &m_coordinates[i+1]);
        m_total_length += d;
    }

    //Keep track of a current coordiante and a next coordinate
    //when we pass the x coordinate of the next coordinate then switch
    //grab everything from the current coordinate for gravity and things like that
}


 //accessor methods
double track::get_c_static_friction() {return m_c_static_friction;}
double track::get_c_dynamic_friction() {return m_c_dynamic_friction;}
double track::get_fluid_density() {return m_fluid_density;}
double track::get_total_length() {return m_total_length;}

//mutator methods - note: adjust angles and density for gravity, etc.

void track::set_c_static_friction(double csf) {m_c_static_friction = csf;}
void track::set_c_dynamic_friction(double cdf) {m_c_dynamic_friction = cdf;}
void track::set_fluid_density(double fd) {m_fluid_density = fd;}

double track::time_to_run(car* Car, double v_target)
{
    double time = 0.0;
    double position = 0.0;
    Car->set_velocity(v_target);
    Car->set_orientation(m_incline);
    //auto start = chrono::high_resolution_clock::now();
    //int tics = 0;
    while(position < m_total_length)
    {
        double u = Car->get_velocity();
        
        // when ~15 mph (6.7 m/s) has been reached, stop throttling
        //if (abs(u - v_target) < 0.45) // 0.22 m/s = 0.5 mph

        if(!kbhit()){
            Car->set_engine_force(0); //don't add to engine if not pressed
 
        }
        else
            if(getch() == 'a'){ //use getch() for real time run
            Car->set_engine_force(250); //sets force ie engine is pressed
            //cout << "Engine Pressed" << endl;
            }
            

        //update force and speed
        double net_force_x = Car->get_net_force_x();
        cout << "Force: " << net_force_x << endl;
        cout << "Coordinate: " << m_coord_number << endl;
        double a = net_force_x / Car->get_mass();
        //cout << "   Accel: " << a;
        //cout << "   Velocity_Change: " << a * m_tic_length;
        float v =  max(0.0, u + a * m_tic_length);
        
        double s = v * m_tic_length;
        //cout << "   Distance: " << s;

        //travel forward based on speed
        Car->travel(s, m_coord_angle);
        Car->set_velocity(v);
        //cout << "   Car Velocity: " << v;
        if(m_direction * Car->get_x() > m_direction * m_next_coord[0])
            update_coordinates(Car);
        position += s;
        cout << "  X Distance: " << Car->get_x() << endl;
        cout << "  Y Distance: " << Car->get_y() << endl;

        //cin.get();
        
        //adds to total time of run
        time += m_tic_length;

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

double track::distance_between_coordinates(vector<double>* c1, vector<double>* c2)
{
    double x1 = (*c1)[0];
    double y1 = (*c1)[1];
    double z1 = (*c1)[2];

    double x2 = (*c2)[0];
    double y2 = (*c2)[1];
    double z2 = (*c2)[2];

    double dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y2) + (z2-z1)*(z2-z1));
    return dist;
}

double track::incline_between_coordinates(vector<double>* c1, vector<double>* c2)
{
    double delta_z = (*c1)[2] - (*c2)[2];
    double dist = distance_between_coordinates(c1, c2);
    double angle = (-1.0)*asin(delta_z/dist); //retaining sign conventions
    return angle;
}

/*
double track::angle_between_coordinates(vector<double>* c1, vector<double>* c2)
{
    double delta_y = (*c1)[1] - (*c2)[1];
    double dist = distance_between_coordinates(c1, c2);
    double angle = 0;
    double diff =  delta_y/dist;
    //correct for negative change in position
    cout << "Diff: " << diff << endl;
    angle = asin(delta_y/dist);  
    
    cout << "Diff: " << diff;
    

    return angle;
}
*/

double track::angle_between_coordinates(vector<double>* c1, vector<double>* c2)
{
    double delta_x = (*c1)[0] - (*c2)[0];
    double delta_y = (*c1)[1] - (*c2)[1];
    double dist = distance_between_coordinates(c1, c2);
    double angle = 0;
    double numerator = (dist*dist) - (delta_x*delta_x) - (delta_y*delta_y);
    double denominator = -2.0 * abs(delta_x) * abs(delta_y);
    double diff = numerator/denominator;
    //correct for negative change in position
    angle = (-1.0)*acos(diff);  
    
    cout << "Diff: " << diff;
    
    return angle;
}


void track::update_coordinates(car* Car){
    m_coord_number++;
    m_current_coord = m_coordinates[m_coord_number];
    m_next_coord = m_coordinates[m_coord_number + 1];

    if(m_current_coord[0] > m_next_coord[0])
        m_direction = -1;
    else
        m_direction = 1;

    m_incline = incline_between_coordinates(&m_current_coord, &m_next_coord);
    m_coord_angle = angle_between_coordinates(&m_current_coord, &m_next_coord);

    Car->set_orientation(m_incline);
}