// Fill in with the pin on which it is connected
int OE = 0 ; 

//register demux data
int DX0A0 = 7 ; 
int DX0A1 = 6 ;
int DX0A2 = 8 ;
//register demux enable
int DX0E3 = 5 ; 

// registers data
int DATA0 = 1 ; 
int DATA1 = 2 ;
int DATA2 = 3 ; 
int DATA3 = 4 ;


void setup(){
  pinMode(OE, OUTPUT);
  pinMode(DX0A0, OUTPUT);
  pinMode(DX0A1, OUTPUT);
  pinMode(DX0A2, OUTPUT);
  pinMode(DX0E3, OUTPUT);
  pinMode(DATA0, OUTPUT);
  pinMode(DATA1, OUTPUT);
  pinMode(DATA2, OUTPUT);
  pinMode(DATA3, OUTPUT);
}

void writeOutput( int pin, byte value){
    if (value){
      digitalWrite(pin,HIGH);
    }
    else{
      digitalWrite(pin,LOW);
    }
}

void send_register_data(byte data){
    // disable registre output
    digitalWrite(OE,HIGH);
    // load values
    writeOutput(DATA0, (data & 0b00000001));
    writeOutput(DATA1, (data & 0b00000010));
    writeOutput(DATA2, (data & 0b00000100));
    writeOutput(DATA3, (data & 0b00001000));
}

void light_on(){
    // turn on the lights
    digitalWrite(OE,LOW);
}

void all_light_off(){
  // turn off all the lights
  load_register_data(0b00000000,0b00000000);
  load_register_data(0b00000001,0b00000000);
}

// select the register witch shall load datas
void select_register(byte data){
    // get input values
    writeOutput(DX0A0, (data & 0b00000001));
    writeOutput(DX0A1, (data & 0b00000010));
    writeOutput(DX0A2, (data & 0b00000100));
    
    // enable demux output
    digitalWrite(DX0E3,HIGH);
    digitalWrite(DX0E3,LOW);
}

void load_register_data(byte regist , byte data){
  //send the data
  send_register_data(data);
  //load the data on the selected register
  select_register(regist);
}

void loop(){
  // main loop
  load_register_data(0b0000000,0b00000001);
  light_on();
  delay(100);
  all_light_off();
    load_register_data(0b0000000,0b00000010);
  light_on();
  delay(100);
  all_light_off();
  load_register_data(0b0000000,0b00000100);
  light_on();
  delay(100);
  all_light_off();
  load_register_data(0b0000000,0b00001000);
  light_on();
  delay(100);
  all_light_off();
  load_register_data(0b0000001,0b00001000);
  light_on();
  delay(100);
  all_light_off();
  load_register_data(0b0000001,0b00000100);
  light_on();
  delay(100);
  all_light_off();
  load_register_data(0b0000001,0b00000010);
  light_on();
  delay(100);
  all_light_off();
  load_register_data(0b0000001,0b00000001);
  light_on();
  delay(100);
}

