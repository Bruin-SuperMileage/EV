#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

class Current_Sensor : public Sensor
{
public:
    Current_Sensor(const int &pin);

    virtual void read_sensor_value();

private:

};

#endif //CURRENT_SENSOR
