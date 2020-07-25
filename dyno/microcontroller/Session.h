/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* This file contains the data member and function declarations of the Session class.  */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#ifndef SESH_H
#define SESH_H
#include "constants.h"

class Session {
   public:
       //interface
       Session(const int POT_PIN, const int DRV_PIN, bool paused);
       void init_temp_sense(const int *TEMP_PINS);
       void check_for_command();
       bool check_paused();
       void read_pot();
       void read_temp();
       void drive_magnet();
       void print_report();
   private:
       //private functions
       void process_command();
       int ramp_signal(int sig_in);
      
       //data members
       int m_pot_pin;       
       int m_temp_pins[NUM_TEMP_SENSE];
       float m_temps[NUM_TEMP_SENSE];
       int m_drv_pin;
       int m_pwm;
       char com_buff[256];
       int com_buff_count;
       bool m_paused_flag;
};

#endif
