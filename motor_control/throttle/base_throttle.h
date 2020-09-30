#ifndef BASE_THR_H
#define BASE_THR_H

class Throttle
{
public:
    Throttle(const int &pin);

    virtual int compute_motor_value() = 0; // this needs to be implemented differently for variable/button throttle

    void read_sensor_value();
    int get_raw_value() const; // should only be used to debug
    int get_motor_value() const;
    int get_pin() const;

private:
    int m_raw_value;
    int m_motor_value;
    int m_sensor_pin;
};

#endif
