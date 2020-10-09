#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

class Accelerometer: public Sensor
{
public:
    Accelerometer(const int &pin);

    void read_sensor_value();
};

#endif //ACCELEROMETER
