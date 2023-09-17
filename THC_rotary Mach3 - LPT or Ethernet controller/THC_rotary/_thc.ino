unsigned int delayTime;
unsigned int SetVx10;

void Setup_THC()
{
  pinMode(outputUpPin, OUTPUT); //PORTD 6
  pinMode(outputOkPin, OUTPUT); //PORTD 7
  pinMode(outputDnPin, OUTPUT); //PORTD 5
  //pinMode(13, OUTPUT); // CKD test signal.
}

void doTHC()
{
  if (Do)
  {
    Do = false;
    LCDtime ++;
    show ++;
    // CKD test signal.
    //bitWrite(PORTB, 5, !bitRead(PORTB, 5));

    if (LCDtime > defaultLCDtime)
    {
      menu = 0;
      pos  = 0;
      LCDtime = 0;
      encoderVal = SetV;
    }
    if ((500 < ArcV) & (ArcV < 2500))
    {
      if (ArcV > StV * 10) delayTime ++;

      if (delayTime >= DT * 10)
      {
        SetVx10 = SetV * 10;
        delayTime = DT * 10;

        bitWrite(PORTD, 7, 1); // arch ok

        if (ArcV >= SetVx10 + HyS)   // 6 up - 5 down
        {
          //Serial.println("D1S1");
          bitWrite(PORTD, 6, 0);
          bitWrite(PORTD, 5, 1);
        }
        else if (ArcV <= SetVx10 - HyS)
        {
          //Serial.println("D0S1");
          bitWrite(PORTD, 5, 0);
          bitWrite(PORTD, 6, 1);
        }
        else
        {
          //Serial.println("OK");
          bitWrite(PORTD, 6, 0);
          bitWrite(PORTD, 5, 0);
        }
      }
    }
    else if (menu != 12)
    {
      delayTime = 0;
      bitWrite(PORTD, 6, 0);
      bitWrite(PORTD, 7, 0);
      bitWrite(PORTD, 5, 0);
    }
  }
}

//void RS232()
//{
//  Serial.print("SetV:");
//  Serial.print(SetVx10);
//  Serial.print(" ArcV:");
//  Serial.print(ArcV);
//  Serial.print(" StV:");
//  Serial.print(StV);
//  Serial.print(" DTime:");
//  Serial.print(delayTime);
//  Serial.println("");
//}
