void setup()
{
  DisableADCandComparator();
  EnableExternalInterrupts();
  for (;;)
  {
    DeepSleep();
    char* pind = (char*) 0x29;
    bool red_pressed = ((*pind) & 2); //PD2
    bool green_pressed = ((*pind) & 4); //PD3
    if (red_pressed)
    {
      TransmitChannel1();
    }

    if (green_pressed)
    {
      TransmitChannel2();
    }
  }
}

ISR(INT0_vect) {}
ISR(IN1_vect) {}

void DeepSleep()
{
  char *smcr = (char *)0x53;
  volatile char *mcucr = (char *) 0x55; *smcr = 5; //Sleep mode = POWER DOWN, Sleep Enable = True
  *mcucr = 0b01100000; //Set Both BODS and BODSE
  *mcucr = 0b01000000; //Set BODS and clear BODSE
  asm("sleep"); //Invoke in line assembler to sleep
}

void DisableADCandComparator()
{
  char* adcsra = (char *)0x7A;
  char* acsr = (char *) 0x50; *adcsra = 0; //Disable ADC
  *acsr = 1 << 7; //Disable comparator
}

void EnableExternalInterrupts()
{
  char* sreg = (char*) 0x5F;
  char* eimsk = (char*) 0x3D;
  char* eicra = (char*) 0x69; *sreg |= (1 << 7); //Enable interrupts
  *eimsk = 3; //Enable INT0 and INT1
  *eicra = 15; //Set trigger mode to LOW TO HIGH
}

void TransmitChannel1()
{
  //Transmit code for channel 1
}

void TransmitChannel2()
{
  //Transmit code for channel 2
}
