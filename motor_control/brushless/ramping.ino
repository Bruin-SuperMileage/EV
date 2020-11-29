#include "ramping.h"

Ramping::Ramping():m_throttleIP(0), m_currentSpd(0), m_desiredSpd(0){}
void Ramping::setThrottle(int throttle){ m_throttleIP = throttle; }
void Ramping::setCurrentSpd(byte spd)      {  m_currentSpd = spd; }
void Ramping::setDesiredSpd(byte spd)      {  m_desiredSpd = spd; }

int  Ramping::getThrottle()   const { return m_throttleIP;  }
byte Ramping::getCurrentSpd() const {  return m_currentSpd; }
byte Ramping::getDesiredSpd() const {  return m_desiredSpd; }

void Ramping::spdUp(byte amount)   {  m_currentSpd += amount; }
void Ramping::spdDown(byte amount) {  m_currentSpd -= amount; }

// LINEAR CLASS =================================================================================
Linear::Linear(byte rampSpd):m_RAMPSPD(rampSpd){}

// INPUT: throttle(int) that reads from A0
// OUTPUT: new speed value(byte) to write to the motor
// DESC: this 
byte Linear::newSpd(int throttle){
  setDesiredSpd(map(throttle, 512, 1023, 0, 255));
  // constrain to maintain positive current speed

  if(getCurrentSpd() != getDesiredSpd()){
    if(getCurrentSpd() < getDesiredSpd())
      spdUp(m_RAMPSPD);
    // if RAMP_SPD defined to be something other than 1,
    // we need to consider in case if desired spd is in the boundary of [currentSpd - RAMPSPD, currentSpd + RAMPSPD]
    // for current spd not to bounce
    else
      spdDown(m_RAMPSPD);
  }
  
//  Serial.print("Current speed: ");
//  Serial.print(getCurrentSpd());
//  Serial.print(", Desired speed: ");
//  Serial.println(getDesiredSpd());
  
  setThrottle(throttle);
  return getCurrentSpd();
}

// PD CLASS ====================================================================================
PD::PD(byte Kp, byte Kd):m_Kp(Kp), m_Kd(Kd), m_error(0), m_prevError(0), m_rateError(0){}

byte PD::newSpd(int throttle){
  // constrain to maintain positive current speed
  
  setDesiredSpd(map(throttle, 0, 1023, 0, 255));
  
  m_error = getDesiredSpd() - getCurrentSpd();
  m_rateError = m_error - m_prevError;

  // need to examine following two equations
  byte spdChange = Kp * m_error + Kd * m_rateError;
  setCurrentSpd(getCurrentSpd() + spdChange);
  
  m_prevError = m_error;
    
//  Serial.print("Current speed: ");
//  Serial.print(getCurrentSpd());
//  Serial.print(", Desired speed: ");
//  Serial.println(getDesiredSpd());
  
  return getCurrentSpd();
}
