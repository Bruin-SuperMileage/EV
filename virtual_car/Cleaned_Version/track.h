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
    double get_track_length();
    void update_coordinates(double distance);
    double get_incline();
    track& operator = (const track &T);

  private:

    double distance_between_coordinates(vector<double>* c1, vector<double>* c2);
    double angle_between_coordinates();
    


    double m_total_length;
    double m_incline;
    double m_coord_angle;
    int m_coord_number;
    int m_total_coords;
    int m_direction;

    vector<vector<double>> m_coordinates;
    vector<double> m_current_coord;
    vector<double> m_next_coord;
};

#endif
