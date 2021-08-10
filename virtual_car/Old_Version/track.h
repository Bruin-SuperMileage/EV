#ifndef TRACK_H
#define TRACK_H
#include <vector>
using namespace std;
class car;

class track
{
  public:
      //constructor
    track();
    
      //accessor methods
    double get_c_static_friction();
    double get_c_dynamic_friction();
    double get_fluid_density();
    double get_total_length();
    
      //mutator methods
    void set_c_static_friction(double csf);
    void set_c_dynamic_friction(double cdf);
    void set_fluid_density(double fd);

    double time_to_run(car* Car, double v_target);
    double distance_between_coordinates(vector<double>* c1, vector<double>* c2);
    double angle_between_coordinates(vector<double>* c1, vector<double>* c2);
    double incline_between_coordinates(vector<double>* c1, vector<double>* c2);

    void update_coordinates(car* Car);

  private:
    double m_c_static_friction; // co-efficient of static friction
    double m_c_dynamic_friction; // co-efficient of dynamic friction
    double m_fluid_density; // only used for air in our case
    double m_total_length;
    double m_tic_length;
    double m_incline;
    double m_coord_angle;
    int m_coord_number;
    int m_direction;
    vector<vector<double>> m_coordinates;
    vector<double> m_current_coord;
    vector<double> m_next_coord;
};

#endif
