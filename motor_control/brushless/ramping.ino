#include "ramping.h"
#include "constants.h"
Ramping::Ramping():m_currentSpd(MIN_SPD), m_desiredSpd(MIN_SPD){}
void Ramping::setCurrentSpd(byte spd)      {  m_currentSpd = spd; }
void Ramping::setDesiredSpd(byte spd)      {  m_desiredSpd = spd; }

byte Ramping::getCurrentSpd() const {  return m_currentSpd; }
byte Ramping::getDesiredSpd() const {  return m_desiredSpd; }

bool Ramping::isTimeToChangeSpd(){
  if(millis() - m_time >= m_maxWaitTime){
    m_time = millis();
    return true;
  }
  else{
    return false;
  }
}

void Ramping::spdUp(byte amount){
  if(m_currentSpd + amount >= MAX_SPD)
    m_currentSpd = MAX_SPD;
  else
    m_currentSpd += amount;
}

void Ramping::spdDown(byte amount){
  if(m_currentSpd - amount <= MIN_SPD)
    m_currentSpd = MIN_SPD;
  else
    m_currentSpd -= amount; 
}

byte Linear::newSpd(int throttle){
  setDesiredSpd(map(throttle, NEUTRAL_THROTTLE, MAX_THROTTLE, MIN_SPD, MAX_SPD));
  
  if(isTimeToChangeSpd()){
    if(getCurrentSpd() != getDesiredSpd()){
      if(getCurrentSpd() < getDesiredSpd())
        spdUp(RAMP_SPD);
     else
       spdDown(RAMP_SPD); 
    }
  }
  return getCurrentSpd();
}

PD::PD(): m_error(0), m_prevError(0), m_rateError(0){}

byte PD::newSpd(int throttle){
  setDesiredSpd(map(throttle, NEUTRAL_THROTTLE, MAX_THROTTLE, MIN_SPD, MAX_SPD));
  
  if(isTimeToChangeSpd()){
    m_error = getDesiredSpd() - getCurrentSpd();
    m_rateError = m_error - m_prevError;
    m_prevError = m_error;

    byte spdChange = Kp * m_error + Kd * m_rateError;
  
    if(spdChange >= 0)
      spdUp(spdChange);
    else
      spdDown(spdChange);
  }
  return getCurrentSpd();
}
