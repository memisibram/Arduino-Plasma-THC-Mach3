/*
  Last update 24.08.2025

  Project:  THC for Plasma CNC controller
  Platform: Arduino UNO R3
  Created:  April 2015
  Version:  02.00
  By:       Pham Duy Anh - phamduyanh@gmail.com

  Update and changes
  By: Mehmet İbrahim - memisibram@gmail.com
  Youtube: https://www.youtube.com/c/MehmetIbrahim

  Adaptation to esp32 24.08.2025  Mehmet İbrahim

  Require:
  -> input
  <- output

  -> serial Tx
  -> serial Rx
  -> reset

  -> rotary encoder      digital - interrupt
  -> rotary encoder      digital - interrupt
  -> totary button       digital

  -> plasma Torch on     digital
  -> plasma Arc Ok       analog or digital)
  -> plasma arc voltage  analog 0-5V

  <- Arc Ok              optocoupler
  <- torch Up            optocoupler
  <- torch Down          optocuopler

  <- LCD
  <- LCD
  <- LCD
  <- LCD
  <- LCD
  <- LCD
*/

#include <esp_timer.h>  // ESP32 Timer library

#define encoderPinA 13  //PORTD 2 - INT0
#define encoderPinB 16  //PORTD 3 - INT1
#define buttonPin 17    //PORTD 4

#define outputDirPin 18  //PORTD 5
#define outputPulPin 19  //PORTD 6

#define relayDir 23  //PORTD 7
#define relayPul 25  //PORTB 0
#define relay5V 26   //PORTB 1

#define arcVoltPin 34  //PORTC 0
#define speedPot 39    //PORTC 1

#define defaultLCDtime 500  // s * 100



#define PWM_CHANNEL 0
esp_timer_handle_t timer_handle;
double espV_value = 3.3;  // voltage value

/*
  Parameter
   DT  - Delay time - Delay time of output closed despite no supply voltage, when the system detects the main (cutting) arc, 0.1~19.9s.
   HyS - Hysreresis - The hysteresis voltage - a rangge in which the voltage is measured, in which ther are signals controlling Up/Down, (+-1V ~ +-15V)
   StV - Started Voltage - Value of the off load voltage detection in the plasma cutter - uesd to detect the main (cutting) arc: 50~300V.
   +

*/

int SetVa = 0, DTa = 1, HySa = 2, StVa = 3;

int SetV, DT, HyS, StV;

//(divRato) It is a value that varies depending on the voltage divider you use, a low value increases Arc.V, a high value decreases it.
//The welding machine gives continuous output. Comparison can be made by connecting the voltage divider to the welding machine :)
//int divRato = 43;
int divRato = 39;

unsigned long ArcV;
int oldValue;


//Taking Average read voltage (values)
bool takingAverage = false;  //Read the voltage with a few examples true or false
//10 samples readings will be taken and averaged to arch voltage read
int sampleReadV = 10;               //10 samples
unsigned int millisdelayReadV = 3;  // Waiting time for between samples readings  [ms]
int counterVo = 0;
unsigned long readVMillis;
unsigned long prevReadVMillis = 0;
unsigned long readingsV = 0;

//stepper motor signal frequency
unsigned int fregCy = 2000;  // Motor speed potentiometer min 33 max 65535

bool reverse = false;  // If the movement is reversed in the test menu, change it (true or false)

int thcOK = 0, thcUp = 0, thcDwn = 0;

int program;

// Array of Param
//              SetV, DT, HYS, StV, divRato,
// Param Address   0,  1,   2,   3,       4,
int Param[4] = { SetV, DT, HyS, StV };  //, divRato};
byte ParamItem = 4;

// Enable to do THC
boolean Do;
boolean DoStepper;

// Encoder, menu, pos
int encoderVal;
byte menu = 0;
byte pos = 0;
byte show = 0;
unsigned int LCDtime = 0;

void setup() {

  //Set ADC resolution to 12 bits (0-4095)
  analogSetWidth(12);
  // Set the pin's voltage attenuation (11dB for 0-3.3V)
  analogSetPinAttenuation(arcVoltPin, ADC_11db);

  Setup_Encoder();
  Setup_LCD();
  Setup_Stepper();
  Setup_Timer1();

  //Read parameter from EEPROM
  ReadProg();
  if (program == 255) {  // Configure eeprom defaults on first boot
    Default();
    ReadProg();  //Now read the parameters again
  }
  switch (program) {
    case 1:
      ReadDataProg_1();
      break;
    case 2:
      ReadDataProg_2();
      break;
    case 3:
      ReadDataProg_3();
      break;
  }

  //Set value for all parameter
  SetV = Param[SetVa];
  DT = Param[DTa];
  HyS = Param[HySa];
  StV = Param[StVa];
  //Preset value for encoder
  encoderVal = SetV;
  //Serial.begin(9600);
}

void loop() {
  //Read voltage
  if (takingAverage) {
    // Read Average voltage value from ADC
    readVMillis = millis();
    if (readVMillis - prevReadVMillis >= millisdelayReadV) {
      prevReadVMillis = readVMillis;
      counterVo++;
      double rawAnalogValue = analogRead(arcVoltPin);
      ArcV = (rawAnalogValue * double(espV_value / 4095.0)) * double(100.00 / divRato);
      //readingsV += double(analogRead(arcVoltPin)) * double(100.00 / divRato);
    }
    if (counterVo == sampleReadV) {
      ArcV = readingsV / sampleReadV;
      counterVo = 0;
      readingsV = 0;
    }

  } else {
    // Read voltage value from ADC
    double rawAnalogValue = analogRead(arcVoltPin);
    ArcV = (rawAnalogValue * double(espV_value / 4095.0)) * double(100.00 / divRato);
    //ArcV = double(analogRead(arcVoltPin)) * double(100.00 / divRato);
  }

  checkButton();
  checkMenu();
  doTHC();
  doLCD();
  RunStepper();

  //RS232();
}
