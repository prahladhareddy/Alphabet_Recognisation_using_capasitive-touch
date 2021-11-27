#include <Wire.h>
#include "Adafruit_MPR121.h"          // Adafruit APR121 library for interactions with MPR121

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();
uint16_t currtouched = 0;
       
#define INIT 200     // this many iterations are used to initialize means and then goes to take input
#define MAX 200      // Waits for input this many itterations and goes to initialization again

bool taking_input = 0;    // wethere we are in process of taking input (already points are noted)
uint16_t init_suma[12] = {};  // sum of voltages while initialising
float init_avg[12] = {};  // average of voltages while initialising

uint16_t t = 0;   // itteration number
int last_touch = -1; // iteration when last touch obsorved

int board[6][6]={};  // to store touched vertices

int X = -1;
int Y = -1;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
  while (!Serial) {
    delay(10);
  }
  
  Serial.println("MPR121 identified");
  
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  
  Serial.println("MPR121 found!");
}

void _init(){       // notes voltages for 100 iterations
  currtouched = cap.touched();
  if(currtouched != 0){
    Serial.println("Initializing plese dont touch ");
    Serial.println(currtouched);
    t = -1;
    return;
  }
  if(t==0){
    for(int i=0;i<12;i++){
      init_suma[i] = 0;
    }
  } 
  for(int i=0;i<12;i++){
    init_suma[i] += cap.filteredData(i);
  }
  if(t == INIT-1){
    for(int i=0;i<12;i++){
      init_avg[i] = (init_suma[i]*1.0)/INIT;
    }
  }
}

bool mark_touched(){   // Identifies touched nodes and marks them
  float b[12]={};
  
  for(int i=0;i<10;i++){
    for(int j=0;j<12;j++){
      b[j] += cap.filteredData(j);
    }
  }

  float _max_x = 0;  // max average dip rows * 10
  int x = 0;

  float _max_y = 0;  // max average dip coloms * 10
  int y = 0;
  
  for(int i=0;i<6;i++){
    float p = 10*init_avg[i] - b[i];
    if(p>_max_y){
      y = i;
      _max_y = p;
    }
  }

  for(int i=6;i<12;i++){
    float p = 10*init_avg[i] - b[i];
    if(p>_max_x){
      x = i-6;
      _max_x = p;
    }
  }
  
  if(_max_x * _max_y < 1000){     // identifying touch
    return 0;
  }

// ---------------for debugging --------------------------
//  Serial.print(x);
//  Serial.print(" ");
//  Serial.print(y);
//  Serial.print("\n");
//  Serial.print(_max_x);
//  Serial.print(" ");
//  Serial.print(_max_y);
//  Serial.print("\n");
//----------------------------------------------------------

  if(t - last_touch <= 3){          // interpolation for missing points
    if(X-x <= 1 && X-x >=-1 && Y-y >= -1 && Y-y <= -1){
    } else {
      board[(x+X)/2][(y+Y)/2]+=1;
    }
  }
  board[x][y]+=1;
  X=x;
  Y=y;
  return 1;
}

void send_output(){   // sending matrix to pc
  Serial.print("MATRIX \n");
  for(int i=0;i<6;i++){
    for(int j=0;j<6;j++){
      Serial.print(board[i][j]);
      Serial.print(" ");
      board[i][j]=0;
    }
    Serial.print("\n");
  }
}

void loop() {
  ------------------------------------initialization phase-----------------------------------------
  if(t<INIT){
    if(t%5 == 0){
      Serial.print("Initializing \n");
    }
    if(t==0){
      digitalWrite(LED_BUILTIN, LOW);
    }
    _init();
  } 
  ------------------------------------touch recognisation phase -------------------------------------
  else if(t < INIT + MAX || (taking_input == 1 )){
    if(t==INIT + 1){
      digitalWrite(LED_BUILTIN, HIGH);
    }
    if(t%5 == 0){
      Serial.print("Listening \n");
    }
    if(mark_touched()){
      taking_input = 1;
      last_touch = t;
    } else if(last_touch != -1 && (t - last_touch) > 20){
      send_output();
      taking_input = 0;
      last_touch = -1;
      t=INIT+MAX;
    }
  } 
  ---------------------------------------returning to initialization phase-------------------------------------------------
  else {
    t = -1;
  }
 
  t++;
}
