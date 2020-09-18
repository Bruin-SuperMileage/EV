#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

class CurrentSensor : public Sensor
{
public:
    CurrentSensor(const int &pin);

    void read_sensor_value();
};

#endif //CURRENT_SENSOR
