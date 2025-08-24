//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 16, 2);

//#include <Wire.h>
//#include <LiquidCrystal_AIP31068_I2C.h>
//LiquidCrystal_AIP31068_I2C lcd( 0x27, 16, 2 );

#include <Wire.h>
#include <hd44780.h>                        // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h>  // i2c expander i/o class header
hd44780_I2Cexp lcd(0x27);

// make some custom characters
byte armsUpDn[8] = {
  B00000,
  B00100,
  B01110,
  B00100,
  B00000,
  B01110,
  B00000,
  B00000
};

byte customUp[8] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000
};
byte customDown[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B00000
};

void Setup_LCD() {
  // set up the LCD's number of columns and rows:
  //  lcd.init(); //LiquidCrystal_I2C
  //  lcd.backlight(); //LiquidCrystal_I2C

  //lcd.init(); //LiquidCrystal_AIP31068_I2C

  lcd.begin(16, 2);  //hd44780

  // create a new character
  lcd.createChar(0, armsUpDn);
  lcd.createChar(1, customUp);
  lcd.createChar(2, customDown);

  lcd.setCursor(1, 0);
  lcd.print("MEHMET IBRAHIM");
  lcd.setCursor(3, 1);
  lcd.print("Plasma THC");
  delay(1500);
  lcd.clear();
}

void doLCD() {
  if (show >= 2) {
    show = 0;
    switch (menu) {
      case 0:
        doLCDDefault();
        break;
      case 1:
        doLCDMenu();
        break;
      case 11:
        doLCDMenuSetup();
        break;
      case 111:
        doLCDDelayTime();
        break;
      case 112:
        doLCDHysreresis();
        break;
      case 113:
        doLCDStartVoltage();
        break;
      case 114:
        doLCDLoadDefault();
        break;
      case 12:
        doLCDTest();
        break;
      case 115:
        doTestUp();
        break;
      case 116:
        doTestDown();
        break;
      case 13:
        doLCDProgramSellect();
        break;
      case 121:
        doProgramSet(1);
        break;
      case 122:
        doProgramSet(2);
        break;
      case 123:
        doProgramSet(3);
        break;

      default:
        doLCDDefault();
    }
  }
}

void doProgramSet(int prg) {
  if (prg == 1) {
    SetVa = 0;
    DTa = 1;
    HySa = 2;
    StVa = 3;
    ReadDataProg_1();
  } else if (prg == 2) {
    SetVa = 4;
    DTa = 5;
    HySa = 6;
    StVa = 7;
    ReadDataProg_2();
  } else {
    SetVa = 8;
    DTa = 9;
    HySa = 10;
    StVa = 11;
    ReadDataProg_3();
  }

  SaveData(100, prg);
  program = prg;

  SetV = Param[0];
  DT = Param[1];
  HyS = Param[2];
  StV = Param[3];
  //Preset value for encoder;
  encoderVal = SetV;
  menu = 0;
}

void doLCDDefault() {
  if (encoderVal < 0) encoderVal = 0;
  else if (encoderVal > 250) encoderVal = 250;
  SetV = encoderVal;
  if (SetV != oldValue) {
    SaveData(SetVa, SetV);
    oldValue = SetV;
  }
  lcd.setCursor(0, 0);
  lcd.print("P ");
  if (thcUp == 1) {
    lcd.write(1);
  } else {
    lcd.print(" ");
  }
  lcd.print(" ");
  lcd.setCursor(4, 0);
  lcd.print("Set.V: ");
  lcd.print(SetV);
  lcd.print("   ");
  lcd.setCursor(0, 1);
  lcd.print(program);
  lcd.print(" ");
  if (thcDwn == 1) {
    lcd.write(2);
  } else {
    lcd.print(" ");
  }
  lcd.print(" ");
  lcd.setCursor(4, 1);
  lcd.print("Arc.V: ");
  lcd.print(ArcV / 10);
  lcd.print("    ");
}
//Main menu
void doLCDMenu() {
  if (encoderVal < 0) encoderVal = 3;
  pos = encoderVal % 4;
  switch (pos) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("> Exit          ");
      lcd.setCursor(0, 1);
      lcd.print("  Program       ");
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("> Program       ");
      lcd.setCursor(0, 1);
      lcd.print("  Setup         ");
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("> Setup         ");
      lcd.setCursor(0, 1);
      lcd.print("  Test          ");
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("> Test          ");
      lcd.setCursor(0, 1);
      lcd.print("  Exit       ");
      break;
  }
}
//Program
void doLCDProgramSellect() {
  if (encoderVal < 0) encoderVal = 3;
  pos = abs(encoderVal % 4);
  switch (pos) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print(">> Exit         ");
      lcd.setCursor(0, 1);
      lcd.print("   Load Prog: 1 ");
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print(">> Load Prog: 1 ");
      lcd.setCursor(0, 1);
      lcd.print("   Load Prog: 2 ");
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print(">> Load Prog: 2 ");
      lcd.setCursor(0, 1);
      lcd.print("   Load Prog: 3 ");
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print(">> Load Prog: 3 ");
      lcd.setCursor(0, 1);
      lcd.print("   Exit         ");
      break;
  }
}
// Setup
void doLCDMenuSetup() {
  if (encoderVal < 0) encoderVal = 4;
  pos = abs(encoderVal % 5);
  switch (pos) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print(">> Exit         ");
      lcd.setCursor(0, 1);
      lcd.print("   Delay Time   ");
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print(">> Delay Time   ");
      lcd.setCursor(0, 1);
      lcd.print("   Hysteresis   ");
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print(">> Hysteresis   ");
      lcd.setCursor(0, 1);
      lcd.print("   Start Voltage");
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print(">> Start Voltage");
      lcd.setCursor(0, 1);
      lcd.print("   Load Default ");
      break;
    case 4:
      lcd.setCursor(0, 0);
      lcd.print(">> Load Default ");
      lcd.setCursor(0, 1);
      lcd.print("   Exit         ");
      break;
  }
}
// Test
void doLCDTest() {
  if (encoderVal < 0) encoderVal = 2;
  pos = abs(encoderVal % 3);
  switch (pos) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("Test > Exit     ");
      lcd.setCursor(0, 1);
      lcd.print("       Torch Up ");
      thcDwn = 0;
      thcUp = 0;
      thcOK = 0;
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Test > Torch Up ");
      lcd.setCursor(0, 1);
      lcd.print("       Torch Dn ");
      if (thcOK == 0) LCDtime = 0;
      if (LCDtime >= 200) {  // 100 LCDtime = 1s
        thcDwn = 0;
        thcUp = 0;
        thcOK = 0;
      }
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Test > Torch Dn ");
      lcd.setCursor(0, 1);
      lcd.print("       Exit     ");
      if (thcOK == 0) LCDtime = 0;
      if (LCDtime >= 200) {
        thcDwn = 0;
        thcUp = 0;
        thcOK = 0;
      }
      break;
  }
}
void doTestUp() {
  thcDwn = 0;
  thcUp = 1;
  thcOK = 1;
  LCDtime = 0;
  menu = 12;
  encoderVal = 1;
}
void doTestDown() {
  thcDwn = 1;
  thcUp = 0;
  thcOK = 1;
  LCDtime = 0;
  menu = 12;
  encoderVal = 2;
}

void doLCDDelayTime() {
  if (encoderVal < 1) encoderVal = 1;
  else if (encoderVal > 200) encoderVal = 200;

  DT = encoderVal;
  if (DT != oldValue) {
    SaveData(DTa, DT);
    oldValue = DT;
    LCDtime = 0;
  }

  double x = DT / 10.00;
  lcd.setCursor(0, 0);
  lcd.print("Set > Delay Time");
  lcd.setCursor(0, 1);
  lcd.print("     : ");
  lcd.print(x, 1);
  lcd.print(" s       ");
}
void doLCDHysreresis() {
  if (encoderVal < 1) encoderVal = 1;
  else if (encoderVal > 99) encoderVal = 99;

  HyS = encoderVal;
  if (HyS != oldValue) {
    SaveData(HySa, HyS);
    oldValue = HyS;
    LCDtime = 0;
  }

  double x = HyS / 10.00;
  lcd.setCursor(0, 0);
  lcd.print("Set > Hysteresis");
  lcd.setCursor(0, 1);
  lcd.print("     :");
  lcd.write(0);
  lcd.print(x, 1);
  lcd.print(" V       ");
}
void doLCDStartVoltage() {
  if (encoderVal < 50) encoderVal = 50;
  else if (encoderVal > 250) encoderVal = 250;

  StV = encoderVal;
  if (StV != oldValue) {
    SaveData(StVa, StV);
    oldValue = StV;
    LCDtime = 0;
  }

  lcd.setCursor(0, 0);
  lcd.print("Set > Start Volt");
  lcd.setCursor(0, 1);
  lcd.print("     : ");
  lcd.print(StV);
  lcd.print(" V       ");
}
void doLCDLoadDefault() {
  Default();

  for (byte i = 0; i < 100; i++) {
    lcd.setCursor(0, 0);
    lcd.print("     Default    ");
    lcd.setCursor(0, 1);
    lcd.print("Load   ");
    lcd.print(i);
    lcd.print(" ");
    lcd.print("%");
    lcd.print("        ");
    delay(5);
  }
  lcd.setCursor(0, 0);
  lcd.print("Default:  DONE  ");
  lcd.setCursor(0, 1);
  lcd.print("Please Restart  ");
  exit(0);
  //menu = 11;
}
