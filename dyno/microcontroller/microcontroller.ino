#include "Session.h"
#include "constants.h"

/////////Instance Declarations///////////
Session* sesh;                         //
int end_time;                          //       
/////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  sesh = new Session(POT_PIN, DRV_PINS, false);
  sesh->init_temp_sense(TEMP_PINS); //configure in constants.h
  end_time = 0; //report timer
}

void loop() {
  sesh->check_for_command();
  if (sesh->check_paused()) return;
  sesh->read_pot();
  sesh->read_temp();
  sesh->drive_magnet();
  if (millis() - end_time > REPORT_PERIOD) {
    sesh->print_report();
    end_time = millis();
  }
}
