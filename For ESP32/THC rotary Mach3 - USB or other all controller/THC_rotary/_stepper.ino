
int PulseTime;

void Setup_Stepper() {
  pinMode(outputDirPin, OUTPUT);  //PORTD 5
  pinMode(outputPulPin, OUTPUT);  //PORTD 6

  pinMode(relayDir, OUTPUT);  //PORTD 7
  pinMode(relayPul, OUTPUT);  //PORTB 0
  pinMode(relay5V, OUTPUT);   //PORTB 1

  digitalWrite(relayDir, HIGH);
  digitalWrite(relayPul, HIGH);
  digitalWrite(relay5V, HIGH);

  digitalWrite(outputDirPin, 1);  // set dir HIGH starting

  // for Arduino-ESP32 v3.0.0 > or newer version
  ledcAttachChannel(outputPulPin, fregCy, 8, PWM_CHANNEL);

  // for Arduino-ESP32 v2.x.x
  // ledcSetup(PWM_CHANNEL, fregCy, 8);  // 1 kHz frekans, 8 bit çözünürlük
  // ledcAttachPin(outputPulPin, PWM_CHANNEL);
}

void RunStepper() {
  if (thcOK == 1) {  // arch ok , steep on arduino

    //Relays active
    digitalWrite(relayDir, LOW);
    digitalWrite(relayPul, LOW);
    digitalWrite(relay5V, LOW);

    if (thcUp == 1 || thcDwn == 1) {
      PulseTime = map(analogRead(speedPot), 0, 4095, 31, fregCy);

      // Set direction
      if (reverse) {
        digitalWrite(outputDirPin, thcUp);
      } else {
        digitalWrite(outputDirPin, thcDwn);
      }

      // Run stepper with tone function
      ledcWriteTone(PWM_CHANNEL, PulseTime);

    } else {
      ledcWriteTone(PWM_CHANNEL, 0);
    }

  } else {  // arch no , step on mach3

    // Stepper stop
    ledcWriteTone(PWM_CHANNEL, 0);

    //Relays passive
    digitalWrite(relayDir, HIGH);
    digitalWrite(relayPul, HIGH);
    digitalWrite(relay5V, HIGH);
  }
}
