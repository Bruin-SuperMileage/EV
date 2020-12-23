#ifndef RAMPING_H
#define RAMPING_H
class Ramping{
public:
  Ramping();
  virtual byte newSpd(int throttle) = 0;
protected:
  void setCurrentSpd(byte spd); 
  void setDesiredSpd(byte spd);

  byte getCurrentSpd() const;
  byte getDesiredSpd() const;

  bool isTimeToChangeSpd();

  void spdUp(byte amount);
  void spdDown(byte amount);
private:
  byte m_currentSpd;
  byte m_desiredSpd;
  long m_time = 0;
  const long m_maxWaitTime = 100;
};

class Linear : public Ramping{
public:
  byte newSpd(int throttle);
};

class PD : public Ramping{
public:
  PD();
  byte newSpd(int throttle);
private:
  byte m_error, m_prevError, m_rateError;
};
#endif
