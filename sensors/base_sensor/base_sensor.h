#ifndef BASE_SENSOR_H
#define BASE_SENSOR_H

class data_value{
    string name = 0;
    double value = rand() % 90 + 10;
}


class Sensor
{
public:
    Sensor(const int &pin);

    virtual void read_sensor_value() = 0; // this needs to be implemented differently for each sensor

    double get_raw_value() const; // should only be used to debug
    double get_sensor_value() const;
   
protected:
    double m_raw_value;
    double m_sensor_value;
    int m_sensor_pin;
    data_value list_of_values[3];
};

#endif //BASE_SENSOR
