
int PulseTime;

void Setup_Stepper()
{
  pinMode(outputDirPin, OUTPUT); //PORTD 5
  pinMode(outputPulPin, OUTPUT); //PORTD 6

  pinMode(relayDir, OUTPUT); //PORTD 7
  pinMode(relayPul, OUTPUT); //PORTB 0
  pinMode(relay5V, OUTPUT);  //PORTB 1

  digitalWrite(relayDir, HIGH);
  digitalWrite(relayPul, HIGH);
  digitalWrite(relay5V, HIGH);

  digitalWrite(outputDirPin, 1); // set dir HIGH starting
}

void RunStepper()
{
  if (thcOK == 1) { // arch ok , steep on arduino

    //Relays active
    bitWrite(PORTD, 7, 0);
    bitWrite(PORTB, 0, 0);
    bitWrite(PORTB, 1, 0);

    if (thcUp == 1 || thcDwn == 1) {
      PulseTime = map(analogRead(speedPot), 0, 1023, 31, fregCy);

      // Set direction
      if (reverse) {
        bitWrite(PORTD, 5, thcUp);
      } else {
        bitWrite(PORTD, 5, thcDwn);
      }

      // Run stepper with tone function
      tone(outputPulPin, PulseTime);

    } else {
      noTone(outputPulPin);
    }

  } else { // arch no , step on mach3

    // Stepper stop
    noTone(outputPulPin);

    //Relays passive
    bitWrite(PORTD, 7, 1);
    bitWrite(PORTB, 0, 1);
    bitWrite(PORTB, 1, 1);
  }

}
