// Fill in with the pin on which it is connected
int CL = 0;
int OE = 1;
int DATA0 = 2;
int DATA1 = 3;
int DATA2 = 4; 
int DATA3 = 5;


void setup(){
  pinMode(CL, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(DATA0, OUTPUT);
  pinMode(DATA1, OUTPUT);
  pinMode(DATA2, OUTPUT);
  pinMode(DATA3, OUTPUT);
}

void writeOutput( int pin, byte value){
    if (value)
      digitalWrite(pin,HIGH);
    else
      digitalWrite(pin,LOW);
}
void load_register_data(byte data){
    // disable registre output
    digitalWrite(OE,HIGH);
    // load values
    writeOutput(DATA0, (data & 0b00000001));
    writeOutput(DATA1, (data & 0b00000010));
    writeOutput(DATA2, (data & 0b00000100));
    writeOutput(DATA3, (data & 0b00001000));
    //clock load signal
    digitalWrite(CL,LOW);
    digitalWrite(CL,HIGH);
}
void light_on(){
    // turn on the lights
    digitalWrite(OE,LOW);
}
  

void loop(){
  // main loop
  load_register_data(0b00001000);
  light_on();
  delay(100);
  load_register_data(0b00000100);
  light_on();
  delay(100);
  load_register_data(0b00000010);
  light_on();
  delay(100);
  load_register_data(0b00000001);
  light_on();
  delay(100);
}

