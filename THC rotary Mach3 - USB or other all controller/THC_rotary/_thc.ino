unsigned int delayTime;
unsigned int SetVx10;

void doTHC()
{
  if (Do)
  {
    Do = false;
    LCDtime ++;
    show ++;
    // CKD test signal.
    //bitWrite(PORTB, 2, !bitRead(PORTB, 2));

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

        thcOK = 1; // arch ok

        if (ArcV >= SetVx10 + HyS)   // 6 up - 5 down
        {
          //Serial.println("D1S1");
          thcUp = 0;
          thcDwn = 1;
        }
        else if (ArcV <= SetVx10 - HyS)
        {
          //Serial.println("D0S1");
          thcDwn = 0;
          thcUp = 1;
        }
        else
        {
          //Serial.println("OK");
          thcUp = 0;
          thcDwn = 0;
        }
      }
    }
    else if (menu != 12)
    {
      delayTime = 0;
      thcOK = 0;
      thcDwn = 0;
      thcUp = 0;
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
