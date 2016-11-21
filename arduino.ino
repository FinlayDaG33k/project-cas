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
{"Vin":5,"trigger":45000,"detrigger":43000,"R1":{"sensorPin": 0,"sensorResistor": 20000,"sensorValue": 0,"raw": 0,"ledPin": 4,"triggered": false},"R2": {"sensorPin": 1,"sensorResistor": 20000,"sensorValue": 0,"raw": 0,"ledPin": 3,"triggered": false},"R3": {"sensorPin": 2,"sensorResistor": 20000,"sensorValue": 0,"raw": 0,"ledPin": 2,"triggered": false},"L1": {"sensorPin": 3,"sensorResistor": 20000,"sensorValue": 0,"raw": 0,"ledPin": 5,"triggered": false},"L2": {"sensorPin": 4,"sensorResistor": 20000,"sensorValue": 0,"raw": 0,"ledPin": 6,"triggered": false},"L3": {"sensorPin": 5,"sensorResistor": 20000,"sensorValue": 0,"raw": 0,"ledPin": 7,"triggered": false}}
*/

#include <ArduinoJson.h>
DynamicJsonBuffer jsonBuffer;

// JSON Config (Don't forget to escape it!)
char* json = "{\"Vin\":5,\"trigger\":45000,\"detrigger\":43000,\"fingers\":{\"R1\":{\"sensorPin\": 0,\"sensorResistor\": 20000,\"sensorValue\": 0,\"raw\": 0,\"ledPin\": 4,\"triggered\": false},\"R2\": {\"sensorPin\": 1,\"sensorResistor\": 20000,\"sensorValue\": 0,\"raw\": 0,\"ledPin\": 3,\"triggered\": false},\"R3\": {\"sensorPin\": 2,\"sensorResistor\": 20000,\"sensorValue\": 0,\"raw\": 0,\"ledPin\": 2,\"triggered\": false},\"L1\": {\"sensorPin\": 3,\"sensorResistor\": 20000,\"sensorValue\": 0,\"raw\": 0,\"ledPin\": 5,\"triggered\": false},\"L2\": {\"sensorPin\": 4,\"sensorResistor\": 20000,\"sensorValue\": 0,\"raw\": 0,\"ledPin\": 6,\"triggered\": false},\"L3\": {\"sensorPin\": 5,\"sensorResistor\": 20000,\"sensorValue\": 0,\"raw\": 0,\"ledPin\": 7,\"triggered\": false}}}\n"; // Set the config values in (escaped) JSON
JsonObject& variables = jsonBuffer.parseObject(json); // parse the JSON values in an array called: variables
JsonObject& fingers =  variables["fingers"]; // get all fingers

void checkFinger(char *fingerCode){
  float buffer= 0;
  float Vout= 0;
  variables["fingers"][fingerCode]["raw"] = analogRead(variables["fingers"][fingerCode]["sensorPin"]);
  if(variables["fingers"][fingerCode]["raw"]){
    buffer = variables["fingers"][fingerCode]["raw"].as<int>() * variables["Vin"].as<int>();
    Vout= (buffer)/1024.0;
    buffer= (variables["Vin"].as<int>()/Vout) -1;
    variables["fingers"][fingerCode]["sensorValue"]= variables["fingers"][fingerCode]["sensorResistor"].as<float>() * buffer;
    if(variables["fingers"][fingerCode]["sensorValue"] > variables["trigger"].as<float>()){
      digitalWrite(variables["fingers"][fingerCode]["ledPin"],HIGH);
      if(variables["fingers"][fingerCode]["triggered"] == false){
        Serial.println(fingerCode);
        variables["fingers"][fingerCode]["triggered"] = true;
      }
    }
    if(variables["fingers"][fingerCode]["sensorValue"] < variables["detrigger"].as<float>()){
      digitalWrite(variables["fingers"][fingerCode]["ledPin"],LOW);
      variables["fingers"][fingerCode]["triggered"] = false;
    }
  }
}

void setup(){
   Serial.begin(9600);
   for (auto finger : fingers){
    pinMode(variables[finger.key]["ledPin"], OUTPUT);
   }   
}

void loop(){
  for (auto finger : fingers){
    checkFinger(finger.key);
  }  
}
