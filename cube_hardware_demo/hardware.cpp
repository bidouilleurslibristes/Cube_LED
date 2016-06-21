//Build up a list of coordonates that can be used to adress a LED

// Y correspond to a data send to a DEMUX in order to enable this output
byte Y0 = 0b00000000;
byte Y1 = 0b00000001;
byte Y2 = 0b00000010;
byte Y3 = 0b00000011;



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

void light_cube_delay(char table[4][4][4], float time){
  for (int i=0; i<time/4; i++){
    light_cube(table);
  }
}

