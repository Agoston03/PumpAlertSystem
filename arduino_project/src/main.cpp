
#include "class.h"

Pump_Sensor Checker(4,7,8);

void setup() {Checker.Initialization();}

void loop() { 
    while (Checker.Available()){
        Checker.SetMessage();  
    }

    Serial.println(Checker.GetMessage());

    delay(2000);

    if(Checker.GetMessage() == "ON" || Checker.GetMessage() == "On" || Checker.GetMessage() == "on" || Checker.GetMessage() == "oN" ){
        Checker.SetPumpStatus();
        Serial.println(Checker.GetPumpStatus());
        
        if(Checker.GetPumpStatus() == LOW){
            Checker.SendSMS("A pump leallt!");
            Serial.println("SMS");
            
            while (Checker.GetPumpStatus() != HIGH){
                while (Checker.Available()){
                    Checker.SetMessage();
                }
                
                if(Checker.GetMessage() == "OFF" || Checker.GetMessage() == "Off" || Checker.GetMessage() == "oFF" || Checker.GetMessage() == "oFf" || Checker.GetMessage() == "ofF"){
                    break;
                }
            }
            Serial.println("END");        
        }
    }
    delay(2000);

    /// @brief folosleges vizsgalni az ellentetes esetet mert nyilvan kikapcsolt allapotot nem lehet kikapcsolni, igy az infinit loop then is going on 
    delay(2000);
    
    /*
    while(Serial.available()){
        Checker.Routine();
    }*/
}


