/*
  Project:  THC for Plasma CNC controller
  Platform: Arduino UNO R3
  Created:  April 2015
  Version:  02.00
  By:       Pham Duy Anh - phamduyanh@gmail.com
  
  Update and changes
  By: Mehmet İbrahim - memisibram@gmail.com
  Youtube: https://www.youtube.com/c/MehmetIbrahim

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

#define encoderPinA     2                 //PORTD 2 - INT0
#define encoderPinB     3                 //PORTD 3 - INT1
#define buttonPin       4                 //PORTD 4

#define outputOkPin     7                //PORTD 7
#define outputUpPin     6                //PORTD 6
#define outputDnPin     5                //PORTD 5

#define arcVoltPin      A0                //PORTC 0

#define defaultLCDtime  500               // s * 100

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
//int divRato = 43 ;
int divRato = 39;

unsigned long ArcV;
int oldValue;


//Taking Average read voltage (values)
bool takingAverage = false; //Read the voltage with a few examples true or false
//10 samples readings will be taken and averaged to arch voltage read
int sampleReadV = 10; //10 samples
unsigned int millisdelayReadV = 3; // Waiting time for between samples readings  [ms]
int counterVo = 0;
unsigned long readVMillis;
unsigned long prevReadVMillis = 0;
unsigned long readingsV = 0;


int program;

// Array of Param
//              SetV, DT, HYS, StV, divRato,
// Param Address   0,  1,   2,   3,       4,
int Param[4] = {SetV, DT, HyS, StV};//, divRato};
byte ParamItem = 4;

// Enable to do THC
boolean Do;
// Encoder, menu, pos
int encoderVal;
byte menu = 0;
byte pos  = 0;
byte show = 0;
unsigned int LCDtime = 0;

void setup()
{
  Setup_Encoder();
  Setup_LCD();
  Setup_THC();
  Setup_Timer2();
  
  //Read parameter from EEPROM
  ReadProg();
  if (program == 255){ // Configure eeprom defaults on first boot
    Default();
    ReadProg(); //Now read the parameters again
  }
  switch (program)
  {
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
  DT   = Param[DTa];
  HyS  = Param[HySa];
  StV  = Param[StVa];
  //Preset value for encoder
  encoderVal = SetV;
  //Serial.begin(9600);
}

void loop()
{
  //Read voltage
  if (takingAverage)
  {
    // Read Average voltage value from ADC
    readVMillis = millis();
    if (readVMillis - prevReadVMillis >= millisdelayReadV)
    {
      prevReadVMillis = readVMillis;
      counterVo++;
      readingsV += double(analogRead(arcVoltPin)) * double(100.00 / divRato);
    }
    if (counterVo == sampleReadV)
    {
      ArcV = readingsV / sampleReadV;
      counterVo = 0;
      readingsV = 0;
    }
    
  } else {
    // Read voltage value from ADC
    ArcV = double(analogRead(arcVoltPin)) * double(100.00 / divRato);
  }


  checkButton();
  checkMenu();
  doTHC();
  doLCD();

  //RS232();
}
