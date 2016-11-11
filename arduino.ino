/*
 * Arduino sketch for Project-Cas
 * https://github.com/FinlayDaG33k/project-cas
 * Jupp, I gotta clean up this code!
 */

// Constants for all fingers
const int Vin= 5;                     // Voltage input for resistance measuring
const float valDetrigger = 43000;     // Resistance in Ohms needed to detrigger a finger.
const float valTrigger = 45000;       // Resistance in Ohms needed to trigger a finger.

// Right Ring Finger
int RRFPin= 2;                         // Pin resitor pin
float RRFR1= 20000;                    // Resitor value in Ohm
float RRFR2= 0;                        // Resistor value for the finger.
int RRFraw= 0;                         // I don't remember what this does :D
int RRFLPin = 2;                       // Led pin
bool RRFB = false;                     // this will be true when the finger has been triggered (to not have it spam)

// Right Middle Finger
int RMFPin= 1;                         // Pin resitor pin
float RMFR1= 20000;                    // Resitor value in Ohm
float RMFR2= 0;                        // Resistor value for the finger.
int RMFraw= 0;                         // I don't remember what this does :D
int RMFLPin = 3;                       // Led pin
bool RMFB = false;                     // this will be true when the finger has been triggered (to not have it spam)

// Right Index Finger
int RIFPin= 0;                         // Pin resitor pin
float RIFR1= 20000;                    // Resitor value in Ohm
float RIFR2= 0;                        // Resistor value for the finger.
int RIFraw= 0;                         // I don't remember what this does :D
int RIFLPin = 4;                       // Led pin
bool RIFB = false;                     // this will be true when the finger has been triggered (to not have it spam)

// Left Index Finger
int LIFPin= 3;                         // Pin resitor pin
float LIFR1= 20000;                    // Resitor value in Ohm
float LIFR2= 0;                        // Resistor value for the finger.
int LIFraw= 0;                         // I don't remember what this does :D
int LIFLPin = 5;                       // Led pin
bool LIFB = false;                     // this will be true when the finger has been triggered (to not have it spam)

// Left Middle Finger
int LMFPin= 4;                         // Pin resitor pin
float LMFR1= 20000;                    // Resitor value in Ohm
float LMFR2= 0;                        // Resistor value for the finger.
int LMFraw= 0;                         // I don't remember what this does :D
int LMFLPin = 6;                       // Led pin
bool LMFB = false;                     // this will be true when the finger has been triggered (to not have it spam)

// Left Ring Finger
int LRFPin= 5;                         // Pin resitor pin
float LRFR1= 20000;                    // Resitor value in Ohm
float LRFR2= 0;                        // Resistor value for the finger.
int LRFraw= 0;                         // I don't remember what this does :D
int LRFLPin = 7;                       // Led pin
bool LRFB = false;                     // this will be true when the finger has been triggered (to not have it spam)

void RightRingFinger(){
  float buffer= 0;
  float Vout= 0;
  
  RRFraw= analogRead(RRFPin);
  if(RRFraw){                            // Check if there is a voltage coming in to the analog pin
    buffer= RRFraw * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    RRFR2= RRFR1 * buffer;                // Calculate the resistor value based on the 20K ohm resistor and the incoming voltage.
    if(RRFR2 > valTrigger){              // check if current resistor value is higher than trigger value
      digitalWrite(RRFLPin,HIGH);        // turn on the LED
      if(RRFB == false){                 // Check if trigger has been activated already
        Serial.println("R3");           // Send trigger to serial
        RRFB = true;                     // set the debounce value to true to not trigger it again until resistor has been lowered first
      }
    }
    if(RRFR2 < valDetrigger){            // check if current resistor value is lower than the detrigger value.
      digitalWrite(RRFLPin,LOW);         // Turn off the LED
      RRFB = false;                      // Set the debounce value to false for a new trigger
    }
  }
}

void RightMiddleFinger(){
  float buffer= 0;
  float Vout= 0;
  
  RMFraw= analogRead(RMFPin);
  if(RMFraw){
    buffer= RMFraw * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    RMFR2= RMFR1 * buffer;
    if(RMFR2 > valTrigger){
      digitalWrite(RMFLPin,HIGH);
      if(RMFB == false){
        Serial.println("R2");
        RMFB = true;
      }
    }
    if(RMFR2 < valDetrigger){
      digitalWrite(RMFLPin,LOW);
      RMFB = false;
    }
  }
}

void RightIndexFinger(){
  float buffer= 0;
  float Vout= 0;
  
  RIFraw= analogRead(RIFPin);
  if(RIFraw){
    buffer= RIFraw * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    RIFR2= RIFR1 * buffer;
    if(RIFR2 > valTrigger){
      digitalWrite(RIFLPin,HIGH);
      if(RIFB == false){
        Serial.println("R1");
        RIFB = true;
      }
    }
    if(RIFR2 < valDetrigger){
      digitalWrite(RIFLPin,LOW);
      RIFB = false;
    }
  }
}


void LeftIndexFinger(){
  float buffer= 0;
  float Vout= 0;
  
  LIFraw= analogRead(LIFPin);
  if(LIFraw){                            // Check if there is a voltage coming in to the analog pin
    buffer= LIFraw * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    LIFR2= LIFR1 * buffer;                // Calculate the resistor value based on the 20K ohm resistor and the incoming voltage.
    if(LIFR2 > valTrigger){              // check if current resistor value is higher than trigger value
      digitalWrite(LIFLPin,HIGH);        // turn on the LED
      if(LIFB == false){                 // Check if trigger has been activated already
        Serial.println("L1");           // Send trigger to serial
        LIFB = true;                     // set the debounce value to true to not trigger it again until resistor has been lowered first
      }
    }
    if(LIFR2 < valDetrigger){            // check if current resistor value is lower than the detrigger value.
      digitalWrite(LIFLPin,LOW);         // Turn off the LED
      LIFB = false;                      // Set the debounce value to false for a new trigger
    }
  }
}

void LeftMiddleFinger(){
  float buffer= 0;
  float Vout= 0;
  
  LMFraw= analogRead(LMFPin);
  if(LMFraw){                            // Check if there is a voltage coming in to the analog pin
    buffer= LMFraw * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    LMFR2= LMFR1 * buffer;                // Calculate the resistor value based on the 20K ohm resistor and the incoming voltage.
    if(LMFR2 > valTrigger){              // check if current resistor value is higher than trigger value
      digitalWrite(LMFLPin,HIGH);        // turn on the LED
      if(LMFB == false){                 // Check if trigger has been activated already
        Serial.println("L2");           // Send trigger to serial
        LMFB = true;                     // set the debounce value to true to not trigger it again until resistor has been lowered first
      }
    }
    if(LMFR2 < valDetrigger){            // check if current resistor value is lower than the detrigger value.
      digitalWrite(LMFLPin,LOW);         // Turn off the LED
      LMFB = false;                      // Set the debounce value to false for a new trigger
    }
  }
}

void LeftRingFinger(){
  float buffer= 0;
  float Vout= 0;
  
  LRFraw= analogRead(LRFPin);
  if(LRFraw){                            // Check if there is a voltage coming in to the analog pin
    buffer= LRFraw * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    LRFR2= LRFR1 * buffer;                // Calculate the resistor value based on the 20K ohm resistor and the incoming voltage.
    if(LRFR2 > valTrigger){              // check if current resistor value is higher than trigger value
      digitalWrite(LRFLPin,HIGH);        // turn on the LED
      if(LRFB == false){                 // Check if trigger has been activated already
        Serial.println("L3");           // Send trigger to serial
        LRFB = true;                     // set the debounce value to true to not trigger it again until resistor has been lowered first
      }
    }
    if(LRFR2 < valDetrigger){            // check if current resistor value is lower than the detrigger value.
      digitalWrite(LRFLPin,LOW);         // Turn off the LED
      LRFB = false;                      // Set the debounce value to false for a new trigger
    }
  }
}

void setup(){
   Serial.begin(9600);
   pinMode(RRFLPin, OUTPUT);
   pinMode(RMFLPin, OUTPUT);
   pinMode(RIFLPin, OUTPUT);
   pinMode(LIFLPin, OUTPUT);
   pinMode(LRFLPin, OUTPUT);
   pinMode(LMFLPin, OUTPUT);
}

void loop(){
  RightIndexFinger();
  RightRingFinger();
  RightMiddleFinger();
  LeftIndexFinger();
  LeftRingFinger();
  LeftMiddleFinger();
}
