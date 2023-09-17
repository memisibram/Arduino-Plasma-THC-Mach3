#include <EEPROM.h>
void Default()
{

  //reset al eeprom values
//    for (int i = 0 ; i < EEPROM.length() ; i++) {
//      EEPROM.write(i, 0);
//    }

  SetVa = 0;
  DTa = 1;
  HySa = 2;
  StVa = 3;

  SetV = 100;
  DT   = 5;
  HyS  = 80;
  StV  = 100;
  EEPROM.update(0,   SetV);
  EEPROM.update(1  , DT);
  EEPROM.update(2 ,  HyS);
  EEPROM.update(3 ,  StV);

  EEPROM.update(4,   SetV);
  EEPROM.update(5  , DT);
  EEPROM.update(6 ,  HyS);
  EEPROM.update(7 ,  StV);

  EEPROM.update(8,   SetV);
  EEPROM.update(9  , DT);
  EEPROM.update(10 , HyS);
  EEPROM.update(11 , StV);

  EEPROM.update(100 ,  1);
}

void ReadProg()
{
  program = EEPROM.read(100);
}


void ReadDataProg_1()
{
  // Param Address   0,   1,  2,  3
  for (int j = 0; j < ParamItem; j++)
  {
    Param[j] = EEPROM.read(j);
  }
}

void ReadDataProg_2()
{
  // Param Address   4,  5,  6,  7
  for (int j = 0; j < ParamItem; j++)
  {
    Param[j] = EEPROM.read(j + 4);
  }
}

void ReadDataProg_3()
{
  // Param Address   8,   9,  10,  11
  for (int j = 0; j < ParamItem; j++)
  {
    Param[j] = EEPROM.read(j + 8);
  }
}

void SaveData(int add, int value)
{
  EEPROM.update(add, value);
}
