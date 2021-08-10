#ifndef PHYSICAL_FORCES_H
#define PHYSICAL_FORCES_H

using namespace std;


class physical_forces{

    public:
        physical_forces();
        double get_grav_x(double incline);
        double get_drag(double velocity);
        double get_friction(double incline);
    
    private:
        double get_normal_force(double incline);
};






#endif