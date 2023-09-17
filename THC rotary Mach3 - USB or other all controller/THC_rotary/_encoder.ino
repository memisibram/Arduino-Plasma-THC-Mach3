//Encoder Interrupt time require <2us
boolean A, B, lastA, lastB;
boolean ButtonOk, ButtonStat, lastButtonStat;
//unsigned long oncekiZaman;

void Setup_Encoder()
{
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(buttonPin,   INPUT_PULLUP);
  attachInterrupt(0, doEncoder, CHANGE);
}


void doEncoder()
{

  A = bitRead(PIND, 2);
  B = bitRead(PIND, 3);
  //if (millis() - oncekiZaman > 3) {
  if (B != lastA) {
    if (B == HIGH) {
      if (A == LOW) {
        encoderVal++;
      } else {
        encoderVal--;
      }
    }
    LCDtime = 0;
  }
  lastA = B;
  // oncekiZaman = millis();
  //}

}

//////////////////////////////////////////////////////////////////////////////////////////////////
// Button
void checkButton()
{
  ButtonStat = bitRead(PIND, 4);
  if (ButtonStat != lastButtonStat)
  {
    if (!ButtonStat) ButtonOk = true;
    lastButtonStat = ButtonStat;
  }
}

void checkMenu()
{
  if (ButtonOk)
  {
    ButtonOk = false;
    LCDtime = 0;

    if (menu == 0) menu = 1;
    else if (menu == 1)
    {
      if (pos == 0)      menu = 0;
      else if (pos == 1) menu = 13;
      else if (pos == 2) menu = 11;
      else if (pos == 3) menu = 12;
    }

    else if (menu == 11)
    {
      if (pos == 0) menu = 1;
      else if (pos == 1) menu = 111;
      else if (pos == 2) menu = 112;
      else if (pos == 3) menu = 113;
      else if (pos == 4) menu = 114;
    }
    else if (menu == 111) menu = 11;
    else if (menu == 112) menu = 11;
    else if (menu == 113) menu = 11;

    else if (menu == 13)
    {
      if (pos == 0)      menu = 1;
      else if (pos == 1) menu = 121;
      else if (pos == 2) menu = 122;
      else if (pos == 3) menu = 123;
    }

    else if (menu == 12)
    {
      if (pos == 0)      menu = 1;
      else if (pos == 1) menu = 115;
      else if (pos == 2) menu = 116;
      //menu = 1;
    }


    if (menu == 0)        encoderVal = SetV;
    else if (menu == 111) encoderVal = DT;
    else if (menu == 112) encoderVal = HyS;
    else if (menu == 113) encoderVal = StV;
    else                  encoderVal = 0;
  }
}
