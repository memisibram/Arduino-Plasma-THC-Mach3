
void Setup_Timer1()
{
  TCCR1A = 0;    // set entire TCCR1A register to 0
  TCCR1B = 0;    // set entire TCCR1B register to 0
  TCNT1  = 0;  //initialize counter value to 0

  // set compare match register for 100hz increments
  OCR1A = 155;// (16*10^6) / (100*1024) - 1 = 155(must be <256)
  TCCR1A |= 0;
  TCCR1B |= (1 << WGM12) | (1 << CS12) | (0 << CS11) | (1 << CS10); //  Prescalar=1024
  TIMSK1 |= ( 1 << OCIE1A); // Timer Compare interrupt enable
}

ISR(TIMER1_COMPA_vect)
{
  Do = true;
}
