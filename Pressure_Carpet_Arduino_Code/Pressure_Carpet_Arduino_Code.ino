// include the interface software library
#include "serialScreen.h"
serialScreen serialscreen;

// MAT CONFIGURATION START

// if c=0, then communication is off; if c=1, then communication is on (cause delay).
int c=1;

// set if the sensor activate the realy and buzzer
// if value = 1, then sensor is active; if value = 0, then sensor is not active;
byte AreaSetup[6][6] = {
        {0,0,0,1,1,1},
        {0,0,0,1,1,1},
        {0,0,0,1,1,1},
        {1,1,1,0,0,0},
        {1,1,1,0,0,0},
        {1,1,1,0,0,0}  };
        
// MAT CONFIGURATION END
        
// select the input pin inputs and outputs
int sensorWire1 = A0; 
int sensorWire2 = A1; 
int sensorWire3 = A2; 
int sensorWire4 = A3; 
int sensorWire5 = A4; 
int sensorWire6 = A5;
int Wire1 = 13;
int Wire2 = 12;
int buzzer = 11;
int Wire3 = 10;
int Wire4 = 9;
int Wire5 = 8;
int Wire6 = 7;
int relay = 2;

// set the analog input reference to consider the activated
// the maximum analog input value is 922
int InputReference = 900;

// create internal memories for the program
int AreaSensors[6][6];
int mrelay = 0; 
String color1 = "black";
int s;
int w;
int l;


void setup() {
  
  // set the communication to 9600 bits per second
  // communication cause delay in the looping program
  if (c==1) {Serial.begin(9600);}
  
  // set the communication to 115200 bits per second
  // communication does not cause delay in the looping program, but interface software stops working
  if (c==0) {Serial.begin(115200);}

  // create pin modes as input/output
  pinMode(sensorWire1, INPUT);
  pinMode(sensorWire2, INPUT);
  pinMode(sensorWire3, INPUT);
  pinMode(sensorWire4, INPUT);
  pinMode(sensorWire5, INPUT);
  pinMode(sensorWire6, INPUT);
  pinMode(Wire1, OUTPUT);
  pinMode(Wire2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(Wire3, OUTPUT);
  pinMode(Wire4, OUTPUT);
  pinMode(Wire5, OUTPUT);
  pinMode(Wire6, OUTPUT);
  pinMode(relay, OUTPUT);
}

void loop() {
     
     // read the 36 sensors using progressive scan and write in the "AreaSensors" matrix memory
     digitalWrite(Wire1, HIGH);
     byte a = 0;
     AreaSensors[a][0] = analogRead(sensorWire1);
     AreaSensors[a][1] = analogRead(sensorWire2);
     AreaSensors[a][2] = analogRead(sensorWire3);
     AreaSensors[a][3] = analogRead(sensorWire4);
     AreaSensors[a][4] = analogRead(sensorWire5);
     AreaSensors[a][5] = analogRead(sensorWire6);
     digitalWrite(Wire1, LOW);
     digitalWrite(Wire2, HIGH);
     a = 1;
     AreaSensors[a][0] = analogRead(sensorWire1);
     AreaSensors[a][1] = analogRead(sensorWire2);
     AreaSensors[a][2] = analogRead(sensorWire3);
     AreaSensors[a][3] = analogRead(sensorWire4);
     AreaSensors[a][4] = analogRead(sensorWire5);
     AreaSensors[a][5] = analogRead(sensorWire6);     
     digitalWrite(Wire2, LOW);
     digitalWrite(Wire3, HIGH);
     a = 2;
     AreaSensors[a][0] = analogRead(sensorWire1);
     AreaSensors[a][1] = analogRead(sensorWire2);
     AreaSensors[a][2] = analogRead(sensorWire3);
     AreaSensors[a][3] = analogRead(sensorWire4);
     AreaSensors[a][4] = analogRead(sensorWire5);
     AreaSensors[a][5] = analogRead(sensorWire6);     
     digitalWrite(Wire3, LOW);
     digitalWrite(Wire4, HIGH);
     a = 3;
     AreaSensors[a][0] = analogRead(sensorWire1);
     AreaSensors[a][1] = analogRead(sensorWire2);
     AreaSensors[a][2] = analogRead(sensorWire3);
     AreaSensors[a][3] = analogRead(sensorWire4);
     AreaSensors[a][4] = analogRead(sensorWire5);
     AreaSensors[a][5] = analogRead(sensorWire6);    
     digitalWrite(Wire4, LOW);
     digitalWrite(Wire5, HIGH);
     a = 4;
     AreaSensors[a][0] = analogRead(sensorWire1);
     AreaSensors[a][1] = analogRead(sensorWire2);
     AreaSensors[a][2] = analogRead(sensorWire3);
     AreaSensors[a][3] = analogRead(sensorWire4);
     AreaSensors[a][4] = analogRead(sensorWire5);
     AreaSensors[a][5] = analogRead(sensorWire6);     
     digitalWrite(Wire5, LOW);
     digitalWrite(Wire6, HIGH);
     a = 5;
     AreaSensors[a][0] = analogRead(sensorWire1);
     AreaSensors[a][1] = analogRead(sensorWire2);
     AreaSensors[a][2] = analogRead(sensorWire3);
     AreaSensors[a][3] = analogRead(sensorWire4);
     AreaSensors[a][4] = analogRead(sensorWire5);
     AreaSensors[a][5] = analogRead(sensorWire6);  
     digitalWrite(Wire6, LOW);

     // reset the relay memory
     mrelay = 0;

  // create a intern looping to analize the analog input and communicate with the interface software
  for (byte k=0; k<6; ++k){   
     for (byte m=0; m<6; ++m){
      
      // if any analog input (922maximum) is greater than Inputreference (settled as 900)
      // and the sensor is activated by the "AreaSetup" memory
      // write the value 1 in the memory "mrelay"
      if ((AreaSetup[m][k]==1)&&(AreaSensors[m][k] > InputReference)) {
        mrelay = 1;
        } 

      // set the color to draw the square area in the drawing software interface
      // if the set value in "AreaSetup" memory is 1 (sensor activated) than the color is red
      // otherwise is green (sensor not activated)
      if (AreaSetup[m][k]==1) {color1 = "red";}
      else {color1 = "green";}

      // draw a square for each sensor in its respective position with the resulting color above
      l=375+k*100;
      w=m*100;
      serialscreen.setBrush(color1);
      serialscreen.fillRect(l,w,100,100);

      // if the sensor is activated
      // draw the square for the sensor in its respective in yellow color
      if (AreaSensors[m][k] > InputReference) {
        l=400+k*100;
        w=25+m*100;
        serialscreen.setBrush("yellow");
        serialscreen.fillRect(l,w, 50, 50);
      }
    }
  }
    // run all the functions started with "serialscreen" in the software program
    serialscreen.drawScreen();
    // clean the serial communication memory to the next program looping
    Serial.flush();

    // if any sensor was activated in the intern looping
    // activate the relay and the buzzer
    if (mrelay == 1) {
      digitalWrite(relay, HIGH);
      analogWrite(buzzer, 10);
      }        
    // otherwise deactivate the relay and the buzzer
    else {
      digitalWrite(relay, LOW);
      analogWrite(buzzer, 0);
      }           
}

