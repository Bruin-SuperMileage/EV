#include "track.h"
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <chrono>  // for high_resolution_clock

using namespace std;
#define VERBOSE 0

track::track()
{

    ifstream raw_data("sonoma.csv"); //reading in all the coordinates

    while(true)
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

    m_total_length = 0.0;
    m_coord_number = 0;
    m_current_coord = m_coordinates[m_coord_number];
    m_next_coord = m_coordinates[m_coord_number + 1];
    m_total_coords = m_coordinates.size();
    m_incline = get_incline();
    m_coord_angle = angle_between_coordinates();

    for (int i=0; i < m_coordinates.size()-1; i++) //calculating total length
    {
        double d = distance_between_coordinates(&m_coordinates[i], &m_coordinates[i+1]);
        m_total_length += d;
        (m_coordinates[i]).push_back(m_total_length);
    }

    m_incline = get_incline();
    m_coord_angle = angle_between_coordinates();
    
}


track& track::operator = (const track &T){

    if(this == &T)
        return *this;

    m_total_length = T.m_total_length;
    m_coord_number = T.m_coord_number;
    m_coordinates = T.m_coordinates;
    m_current_coord = T.m_current_coord;
    m_next_coord = T.m_next_coord;
    m_total_coords = T.m_total_coords;
    m_incline = T.m_incline;
    m_coord_angle = T.m_coord_angle;
    return *this;
}


double track::get_track_length() {return m_total_length;}

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

double track::get_incline()
{
    double delta_z = m_current_coord[2] - m_next_coord[2];
    double dist = distance_between_coordinates(&m_current_coord, &m_next_coord);
    double angle = -1.0 * asin(delta_z/dist); //retaining sign conventions
    return angle;
}


double track::angle_between_coordinates()
{
    double delta_x = m_current_coord[0] - m_next_coord[0];
    double delta_y = m_current_coord[1] - m_next_coord[1];
    double dist = distance_between_coordinates(&m_current_coord, &m_next_coord);
    double angle = 0;
    double numerator = (dist*dist) - (delta_x*delta_x) - (delta_y*delta_y);
    double denominator = -2.0 * abs(delta_x) * abs(delta_y);
    double diff = numerator/denominator;
    //correct for negative change in position
    angle = (-1.0)*acos(diff);  
    
    return angle;
}

void track::update_coordinates(double distance){

    
    while(distance > m_next_coord[3]){
        if(VERBOSE) 
            cout << "Coordinate_Change" << endl;
        m_coord_number++;

        if(m_coord_number == m_total_coords){
            m_coord_number = 0;
            m_current_coord = m_coordinates[m_coord_number];
            m_next_coord = m_coordinates[m_coord_number + 1];
            break;
        }

        m_current_coord = m_coordinates[m_coord_number];
        m_next_coord = m_coordinates[m_coord_number + 1];

        if(m_current_coord[0] > m_next_coord[0])
            m_direction = -1;
        else
            m_direction = 1;

        m_incline = get_incline();
        if(VERBOSE) 
            cout << "Incline: " << m_incline << endl;
        m_coord_angle = angle_between_coordinates();
    }
}