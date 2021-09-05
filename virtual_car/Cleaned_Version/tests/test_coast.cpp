#include "main.cpp"

using namespace std;

int main(){
    
    double total_distance = 0.0;
    double average_velocity = 0.0;
    double time = 0;
    int lap_number;
    double joules = 0.0;

    //TODO: Make these user inputs
    double current_speed = 0.0;

    physical_forces* Phys = new physical_forces;
    motor* Motor = new motor;
    track* Track = new track;


    time = coast_100(Motor, Phys, Track, current_speed, joules);

    cout << time << endl;
    cout << joules << endl;
}