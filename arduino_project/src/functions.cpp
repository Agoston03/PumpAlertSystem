
#include "class.h"
#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8); //TX and RX



Pump_Sensor::Pump_Sensor(int vibration_sensor_PIN, int TX, int RX){
  
  datablock.vibration_sensor_PIN = vibration_sensor_PIN;
  datablock.TX = TX;
  datablock.RX = RX;

}


void Pump_Sensor::Initialization(){

    pinMode(datablock.vibration_sensor_PIN, INPUT);

    Serial.begin(19200);
    SIM900.begin(19200);
    //SMS text mode
    SIM900.print("AT+CMGF=1\r"); 

    Serial.println("Initializing is finished");
    Serial.println(datablock.vibration_sensor_PIN);
}


void Pump_Sensor::SetPumpStatus(){
  datablock.pump_status = digitalRead(datablock.vibration_sensor_PIN);
}

int Pump_Sensor::GetPumpStatus(){
  return datablock.pump_status;
}

String Pump_Sensor::GetMessage(){
  return datablock.message;
}



void Pump_Sensor::SetMessage(){
  SetMessage_help(SIM900.readString());
}



void Pump_Sensor::SetMessage_help(String buff) {
    
  unsigned int index;

  //Remove sent "AT Command" from the response string.
  index = buff.indexOf("\r");
  buff.remove(0, index + 2);
  buff.trim();

  if (buff != "OK") {
    index = buff.indexOf(":");
    String cmd = buff.substring(0, index);
    cmd.trim();

    buff.remove(0, index + 2);

    //Parse necessary message from SIM800L Serial buffer string
    if (cmd == "+CMT") {

      //get newly arrived memory location and store it in temp
      index = buff.lastIndexOf(0x0D);//Looking for position of CR(Carriage Return)
      datablock.message = buff.substring(index + 2, buff.length());//Writes message to variable "msg"
      datablock.message.toLowerCase();//Whole message gets changed to lower case
    }
  }
}




void Pump_Sensor::SendSMS(String message){
// AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT+CMGS=\"+36303653884\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println(message); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
}


int Pump_Sensor::Available(){
  return SIM900.available();
}


void Pump_Sensor::Routine(){
  SIM900.println(Serial.readString());
}
