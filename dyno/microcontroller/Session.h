/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* This file contains the data member and function declarations of the Session class.  */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#ifndef SESH_H
#define SESH_H
#include "constants.h"

struct SerialStats
{
    int m_chars_received = 0;
    int m_commands_received = 0;
    int m_commands_parsed = 0;
    int m_commands_not_parsed = 0;
};

class Session
{
public:
    //interface
    Session(const int POT_PIN, const int *DRV_PIN, bool paused, bool drive_w_pot = false);
    void init_temp_sense(const int *TEMP_PINS);
    void check_for_command();
    bool check_paused();
    void read_pot();
    void read_temp();
    void drive_magnet();
    void print_report();

private:
    //private functions
    bool process_command();
    int ramp_signal(int sig_in);

    //data members
    int m_pot_pin;
    int m_temp_pins[NUM_TEMP_SENSE];
    float m_temps[NUM_TEMP_SENSE];
    int m_drv_pins[8];
    int m_pwms[NUM_MAGNETS];
    char m_com_buff[256];
    int m_com_buff_count;
    bool m_paused_flag;
    bool m_drive_w_pot;
    SerialStats m_serial_stats;
};

#endif
