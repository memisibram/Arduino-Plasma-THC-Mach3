#include <EEPROM.h>
void Default() {

  //reset al eeprom values
  //    for (int i = 0 ; i < EEPROM.length() ; i++) {
  //      EEPROM.write(i, 0);
  //    }

  SetVa = 0;
  DTa = 1;
  HySa = 2;
  StVa = 3;

  SetV = 100;
  DT = 5;
  HyS = 80;
  StV = 100;
  EEPROM.write(0, SetV);
  EEPROM.write(1, DT);
  EEPROM.write(2, HyS);
  EEPROM.write(3, StV);

  EEPROM.write(4, SetV);
  EEPROM.write(5, DT);
  EEPROM.write(6, HyS);
  EEPROM.write(7, StV);

  EEPROM.write(8, SetV);
  EEPROM.write(9, DT);
  EEPROM.write(10, HyS);
  EEPROM.write(11, StV);

  EEPROM.write(12, 1);

  EEPROM.commit();
}

void ReadProg() {
  EEPROM.begin(14);
  program = EEPROM.read(12);
}


void ReadDataProg_1() {
  // Param Address   0,   1,  2,  3
  for (int j = 0; j < ParamItem; j++) {
    Param[j] = EEPROM.read(j);
  }
}

void ReadDataProg_2() {
  // Param Address   4,  5,  6,  7
  for (int j = 0; j < ParamItem; j++) {
    Param[j] = EEPROM.read(j + 4);
  }
}

void ReadDataProg_3() {
  // Param Address   8,   9,  10,  11
  for (int j = 0; j < ParamItem; j++) {
    Param[j] = EEPROM.read(j + 8);
  }
}

void SaveData(int add, int value) {
  EEPROM.write(add, value);
  EEPROM.commit();
}
