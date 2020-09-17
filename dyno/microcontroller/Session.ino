/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* This file contains the function implementations of the Session class.  */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#include "Session.h"

Session::Session(const int POT_PIN, const int *DRV_PINS, bool paused, bool drive_w_pot)
{
  m_pot_pin = POT_PIN;
  pinMode(m_pot_pin, INPUT);
  for (int i = 0; i < NUM_MAGNETS; i++)
  {
    m_drv_pins[i] = DRV_PINS[i];
    m_pwms[i] = 0;
    pinMode(m_drv_pins[i], OUTPUT);
  }
  memset(m_com_buff, 0, sizeof(m_com_buff));
  m_com_buff_count = 0;
  m_drive_w_pot = drive_w_pot;
  if (paused)
    m_paused_flag = 1;
  else
    m_paused_flag = 0;
}

void Session::init_temp_sense(const int *TEMP_PINS)
{
  for (int i = 0; i < NUM_TEMP_SENSE; i++)
  {
    m_temp_pins[i] = TEMP_PINS[i];
    pinMode(m_temp_pins[i], INPUT);
  }
}

bool Session::process_command()
{
  auto command_parsed = false;
  if (m_com_buff_count == 1)
  {
    //easy parsing for single char commands
    if (m_com_buff[0] == 'R')
    {
      //resume
      m_paused_flag = false;
      command_parsed = true;
    }
    if (m_com_buff[0] == 'P')
    {
      //pause
      m_paused_flag = true;
      command_parsed = true;
    }
  }
  else
  { //multi-char commands
    //extract command prefix
    String command = "";
    int i;
    for (i = 0; i < m_com_buff_count; i++)
    {
      if (m_com_buff[i] != '=')
        command += m_com_buff[i];
      else
      {
        i++;
        break;
      }
    }

    //handle commands
    if (command == "MAGNET")
    {
      //assumed format:
      //MAGNET=1:240,3:000,
      while (i < m_com_buff_count)
      {
        //still more to be parsed
        String pwm_str = String(m_com_buff[i + 2]) + String(m_com_buff[i + 3]) + String(m_com_buff[i + 4]);
        m_pwms[m_com_buff[i] - '0'] = pwm_str.toInt();
        i += 6;
      }
      command_parsed = true;
    }
  }
  //command stored in 256 byte buffer => can implement multi-char commands too

  return command_parsed;
}

void Session::check_for_command()
{
  //buffer incoming data until ; indicates end of command
  char incomingByte;
  while (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    m_serial_stats.m_chars_received += 1;
    if (incomingByte == ';')
    {
      m_serial_stats.m_commands_received += 1;
      if (process_command())
      {
        m_serial_stats.m_commands_parsed += 1;
        Serial.write("ack=200;");
      }
      else
      {
        m_serial_stats.m_commands_not_parsed += 1;
        Serial.write("ack=400;");
      }
      memset(m_com_buff, 0, sizeof(m_com_buff));
      m_com_buff_count = 0;
    }
    else
    {
      m_com_buff[m_com_buff_count] = incomingByte;
      m_com_buff_count += 1;
    }
  }
}

bool Session::check_paused()
{
  //paused flag is read only, writeable only by LP
  return m_paused_flag;
}

int Session::ramp_signal(int sig_in)
{
  //currently does not ramp. Probably worth implementing to avoid unrealistic load spikes
  return (int)map(sig_in, POT_LOWER, POT_UPPER, 0, 255);
}

void Session::read_pot()
{
  int pot_sig = analogRead(m_pot_pin);
  if (m_drive_w_pot)
    for (int i = 0; i < NUM_MAGNETS; i++)
      m_pwms[i] = ramp_signal(pot_sig);
}

void Session::read_temp()
{
  float voltage;
  for (int i = 0; i < NUM_TEMP_SENSE; i++)
  {
    voltage = analogRead(m_temp_pins[i]) * 5.0 / 1024.0;
    m_temps[i] = (voltage - 0.5) * 100;
  }
}

void Session::drive_magnet()
{
  for (int i = 0; i < NUM_MAGNETS; i++)
  {
    analogWrite(m_drv_pins[i], m_pwms[i]);
  }
}

void Session::print_report()
{
  //print a bunch of diagnostic stuff
}
