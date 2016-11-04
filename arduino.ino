int Vin= 5;
float valDetrigger = 43000;
float valTrigger = 45000;

// Right Ring Finger
int RFPin= 2;
float RFR1= 20000;
float RFR2= 0;
int RFraw= 0;
int RFLPin = 2;
bool RFB = false;

// Right Middle Finger
int MFPin= 1;
float MFR1= 20000;
float MFR2= 0;
int MFraw= 0;
int MFLPin = 3;
bool MFB = false;

// Right Index Finger
int IFPin= 0;
float IFR1= 20000;
float IFR2= 0;
int IFraw= 0;
int IFLPin = 4;
bool IFB = false;

void ringFinger(){
  float buffer= 0;
  float Vout= 0;
  
  RFraw= analogRead(RFPin);
  if(RFraw){
    buffer= RFraw * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    RFR2= RFR1 * buffer;
    if(RFR2 > valTrigger){
      digitalWrite(RFLPin,HIGH);
      if(RFB == false){
        Serial.println("R3");
        RFB = true;
      }
    }
    if(RFR2 < valDetrigger){
      digitalWrite(RFLPin,LOW);
      RFB = false;
    }
  }
}

void middleFinger(){
  float buffer= 0;
  float Vout= 0;
  
  MFraw= analogRead(MFPin);
  if(MFraw){
    buffer= MFraw * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    MFR2= MFR1 * buffer;
    if(MFR2 > valTrigger){
      digitalWrite(MFLPin,HIGH);
      if(MFB == false){
        Serial.println("R2");
        MFB = true;
      }
    }
    if(MFR2 < valDetrigger){
      digitalWrite(MFLPin,LOW);
      MFB = false;
    }
  }
}

void indexFinger(){
  float buffer= 0;
  float Vout= 0;
  
  IFraw= analogRead(IFPin);
  if(IFraw){
    buffer= IFraw * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    IFR2= IFR1 * buffer;
    if(IFR2 > valTrigger){
      digitalWrite(IFLPin,HIGH);
      if(IFB == false){
        Serial.println("R1");
        IFB = true;
      }
    }
    if(IFR2 < valDetrigger){
      digitalWrite(IFLPin,LOW);
      IFB = false;
    }
  }
}

void setup(){
   Serial.begin(9600);
   pinMode(RFLPin, OUTPUT);
   pinMode(MFLPin, OUTPUT);
   pinMode(IFLPin, OUTPUT);
}

void loop(){
  indexFinger();
  ringFinger();
  middleFinger();
}
