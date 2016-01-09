// Fill in with the pin on which it is connected
int DX0E3 = 4; // Demux register enable
int DX0A0 = 5; // Demux register Data0
int DX0A1 = 6; // Demux register Data1
int DATA0 = 0;
int DATA1 = 1;
int DATA2 = 2; 
int DATA3 = 3;
int DX1A0 = 7; // Demux masse Data0
int DX1A1 = 8; // Demux masse Data1
int DX1E3 = 9; // Demux masse enable


//Build up a list of coordonates that can be used to adress a LED

// Y correspond to a data send to a DEMUX in order to enable this output
byte Y0 = 0b00000000;
byte Y1 = 0b00000001;
byte Y2 = 0b00000010;
byte Y3 = 0b00000011;

void setup(){
  pinMode(DX0E3, OUTPUT);
  pinMode(DX0A0, OUTPUT);
  pinMode(DX0A1, OUTPUT);
  pinMode(DATA0, OUTPUT);
  pinMode(DATA1, OUTPUT);
  pinMode(DATA2, OUTPUT);
  pinMode(DATA3, OUTPUT);
  pinMode(DX1A0, OUTPUT);
  pinMode(DX1A1, OUTPUT);
  pinMode(DX1E3, OUTPUT);
}

void writeOutput( int pin, byte value){
    if (value){
      digitalWrite(pin,HIGH);
    }
    else{
      digitalWrite(pin,LOW);
    }
}
void load_register_data(byte regist,byte data){
    // send the data to all register
    writeOutput(DATA0, (data & 0b00000001));
    writeOutput(DATA1, (data & 0b00000010));
    writeOutput(DATA2, (data & 0b00000100));
    writeOutput(DATA3, (data & 0b00001000));
    //select the register to load and load it
    load_register(regist);
}

void load_register(byte regist){
    digitalWrite(DX0E3,LOW);
    writeOutput(DX0A0, (regist & 0b00000001));
    writeOutput(DX0A1, (regist & 0b00000010));
    digitalWrite(DX0E3,HIGH);
    digitalWrite(DX0E3,LOW);
}

void connect_mass(byte mass){
  writeOutput(DX1A0, (mass & 0b00000001));
  writeOutput(DX1A1, (mass & 0b00000010));
  digitalWrite(DX1E3,HIGH);
}

void disconnect_mass(){
  digitalWrite(DX1E3,LOW);
}

void light_a_stage(byte line0, byte line1, byte line2, byte line3, byte mass){
  load_register_data(Y0,line0);
  load_register_data(Y1,line1);
  load_register_data(Y2,line2);
  load_register_data(Y3,line3);
  connect_mass(mass);
  delay(2);
  disconnect_mass();
}

void light_cube(char table[4][4][4]){
  byte line[4];
  for (int z=0; z<4;z++){
    for (int y=0;y<4;y++){
      line[y]=0b00000000;
      for (int x=0; x<4; x++){
        if (table[z][y][x]){
          line[y] = (0b00000001 << x) ^ line[y];
        }
      }
    }
    light_a_stage(line[0],line[1],line[2],line[3],z);
  }
}



// Etapes pour un allumage:
// Remplir les registres
// Light sur un étage
// délai 1s/25/nb_etage
// changer d'étage

void loop(){
  // main loop
  char tableau1[4][4][4]= {{{0,0,0,1},
                            {0,0,0,0},
                            {0,0,0,0},
                            {0,0,0,0}},
                       
                           {{0,0,0,0},
                            {0,0,1,0},
                            {0,0,0,0},
                            {0,0,0,0}},
                          
                           {{0,0,0,0},
                            {0,0,0,0},
                            {0,1,0,0},
                            {0,0,0,0}},
                         
                           {{0,0,0,0},
                            {0,0,0,0},
                            {0,0,0,0},
                            {1,0,0,0}}};
   light_cube(tableau1);
}


