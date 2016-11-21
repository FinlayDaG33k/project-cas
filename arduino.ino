/*
 * Arduino sketch for Project-Cas
 * https://github.com/FinlayDaG33k/project-cas
 * Jupp, I gotta clean up this code!
 * 
 * Libraries Used:
 * https://github.com/bblanchon/ArduinoJson
 */

/* 
JSON default-config
{"R1":{"sensorPin": 0,"sensorResistor": 20000,"sensorValue": 0,"raw": 0,"ledPin": 4,"triggered": false},"R2": {"sensorPin": 1,"sensorResistor": 20000,"sensorValue": 0,"raw": 0,"ledPin": 3,"triggered": false},"R3": {"sensorPin": 2,"sensorResistor": 20000,"sensorValue": 0,"raw": 0,"ledPin": 2,"triggered": false},"L1": {"sensorPin": 3,"sensorResistor": 20000,"sensorValue": 0,"raw": 0,"ledPin": 5,"triggered": false},"L2": {"sensorPin": 4,"sensorResistor": 20000,"sensorValue": 0,"raw": 0,"ledPin": 6,"triggered": false},"L3": {"sensorPin": 5,"sensorResistor": 20000,"sensorValue": 0,"raw": 0,"ledPin": 7,"triggered": false}}
*/

#include <ArduinoJson.h>
DynamicJsonBuffer jsonBuffer;

// Constants for all fingers
const int Vin= 5;                     // Voltage input for resistance measuring
const float valDetrigger = 43000;     // Resistance in Ohms needed to detrigger a finger.
const float valTrigger = 45000;       // Resistance in Ohms needed to trigger a finger.

// JSON Config (Don't forget to escape it!)
char* json = "{\"R1\":{\"sensorPin\": 0,\"sensorResistor\": 20000,\"sensorValue\": 0,\"raw\": 0,\"ledPin\": 4,\"triggered\": false},\"R2\": {\"sensorPin\": 1,\"sensorResistor\": 20000,\"sensorValue\": 0,\"raw\": 0,\"ledPin\": 3,\"triggered\": false},\"R3\": {\"sensorPin\": 2,\"sensorResistor\": 20000,\"sensorValue\": 0,\"raw\": 0,\"ledPin\": 2,\"triggered\": false},\"L1\": {\"sensorPin\": 3,\"sensorResistor\": 20000,\"sensorValue\": 0,\"raw\": 0,\"ledPin\": 5,\"triggered\": false},\"L2\": {\"sensorPin\": 4,\"sensorResistor\": 20000,\"sensorValue\": 0,\"raw\": 0,\"ledPin\": 6,\"triggered\": false},\"L3\": {\"sensorPin\": 5,\"sensorResistor\": 20000,\"sensorValue\": 0,\"raw\": 0,\"ledPin\": 7,\"triggered\": false}}"; // Set the config values in (escaped) JSON
JsonObject& variables = jsonBuffer.parseObject(json); // parse the JSON values in an array called: variables

void finger(char *fingerCode){
  float buffer= 0;
  float Vout= 0;
  variables[fingerCode]["raw"] = analogRead(variables[fingerCode]["sensorPin"]);
  if(variables[fingerCode]["raw"]){
    buffer = variables[fingerCode]["raw"].as<int>() * Vin;
    Vout= (buffer)/1024.0;
    buffer= (Vin/Vout) -1;
    variables[fingerCode]["sensorValue"]= variables[fingerCode]["sensorResistor"].as<float>() * buffer;
    if(variables[fingerCode]["sensorValue"] > valTrigger){
      digitalWrite(variables[fingerCode]["ledPin"],HIGH);
      if(variables[fingerCode]["triggered"] == false){
        Serial.println(fingerCode);
        variables[fingerCode]["triggered"] = true;
      }
    }
    if(variables[fingerCode]["sensorValue"] < valDetrigger){
      digitalWrite(variables[fingerCode]["ledPin"],LOW);
      variables[fingerCode]["triggered"] = false;
    }
  }
}

void setup(){
   Serial.begin(9600);
   pinMode(variables["R1"]["ledPin"], OUTPUT);
   pinMode(variables["R2"]["ledPin"], OUTPUT);
   pinMode(variables["R3"]["ledPin"], OUTPUT);
   pinMode(variables["L1"]["ledPin"], OUTPUT);
   pinMode(variables["L2"]["ledPin"], OUTPUT);
   pinMode(variables["L3"]["ledPin"], OUTPUT);
}

void loop(){
  finger("R1");
  finger("R2");
  finger("R3");
  finger("L1");
  finger("L2");
  finger("L3");
}
