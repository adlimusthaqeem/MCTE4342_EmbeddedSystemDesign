void setup() 
  {
    char *ddrb = (char *)0x24;
    char *ddrc = (char *)0x27;
    char *ddrd = (char *)0x2A;
    char *adcsra = (char *)0x7A; *ddrb = 0b11111111; *ddrc = 0b11111111; *ddrd = 0b11111111; *adcsra = 0;
    for (;;)
    {
      
    }
  }
