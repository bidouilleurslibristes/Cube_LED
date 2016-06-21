#include "Arduino.h"


void writeOutput( int pin, byte value);
void load_register_data(byte regist,byte data);
void load_register(byte regist);
void connect_mass(byte mass);
void disconnect_mass();
void light_a_stage(byte line0, byte line1, byte line2, byte line3, byte mass);
void light_cube(char table[4][4][4]);
void light_cube_delay(char table[4][4][4], float time);
