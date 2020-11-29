#ifndef RAMPING_H
#define RAMPING_H

class Ramping{
public:
  Ramping();
  virtual byte newSpd(int throttle) = 0;
  
protected:
  void setThrottle(int throttle);
  void setCurrentSpd(byte spd); 
  void setDesiredSpd(byte spd);

  int  getThrottle()   const;
  byte getCurrentSpd() const;
  byte getDesiredSpd() const;

  void spdUp(byte amount);
  void spdDown(byte amount);
private:
  int  m_throttleIP;
  byte m_currentSpd;
  byte m_desiredSpd;
};

class Linear : public Ramping{
public:
  Linear(byte rampSpd);
  byte newSpd(int throttle);
private:
  byte m_RAMPSPD;
};

class PD : public Ramping{
public:
  PD(byte Kp, byte Kd);
  byte newSpd(int throttle);
private:
  byte m_error, m_prevError, m_rateError;
  byte m_Kp, m_Kd;
};
#endif
