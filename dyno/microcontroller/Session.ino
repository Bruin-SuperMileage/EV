/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* This file contains the function implementations of the Session class.  */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#include "Session.h"

Session::Session(const int POT_PIN, const int DRV_PIN, bool paused) {
  m_pot_pin = POT_PIN;
  m_drv_pin = DRV_PIN;
  memset(com_buff, 0, sizeof(com_buff));
  com_buff_count = 0;
  if (paused) m_paused_flag = 1;
  else m_paused_flag = 0;
}

void Session::init_temp_sense(const int *TEMP_PINS) {
  for (int i = 0; i < NUM_TEMP_SENSE; i++) {
    m_temp_pins[i] = TEMP_PINS[i];
  }
}

void Session::process_command() {
  if (com_buff_count == 1) {
    //easy parsing for single char commands
    if (com_buff[0] == 'R') {
      //resume
      m_paused_flag = false;
    }
    if (com_buff[0] == 'P') {
      //pause
      m_paused_flag = true;
    }
  }
  //command stored in 256 byte buffer => can implement multi-char commands too
}

void Session::check_for_command() {
  //buffer incoming data until ; indicates end of command
  char incomingByte;
  while (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == ';') {
      process_command();
      memset(com_buff, 0, sizeof(com_buff));
      com_buff_count = 0;
    }
    else {
      com_buff[com_buff_count] = incomingByte;
      com_buff_count += 1;
    }
  }
}

bool Session::check_paused() {
  //paused flag is read only, writeable only by LP
  return m_paused_flag;
}

int Session::ramp_signal(int sig_in) {
  //currently does not ramp. Probably worth implementing to avoid unrealistic load spikes
  return (int) map(sig_in, POT_LOWER, POT_UPPER, 0, 255);
}

void Session::read_pot() {
  m_pwm = ramp_signal(analogRead(m_pot_pin));
}

void Session::read_temp() {
  float voltage;
  for (int i = 0; i < NUM_TEMP_SENSE; i++) {
    voltage = analogRead(m_temp_pins[i]) * 5.0 / 1024.0;
    m_temps[i] = (voltage - 0.5) * 100;
  }
}

void Session::drive_magnet() {
  analogWrite(m_drv_pin, m_pwm);
}

void Session::print_report() {
  //print a bunch of diagnostic stuff
}
