

#ifndef CLASS_H
#define CLASS_H

#include <Arduino.h>

class Pump_Sensor {

        /// @brief Stores the obligatory datas 
        class DataBlock{
            public:
                int vibration_sensor_PIN;
                int TX, RX;
                int pump_status;
                String message;
        };  
        
        DataBlock datablock;   
    private:
    
        /// @brief It reads the message from the RX and prases and stores it into the DataBlock        
        void SetMessage_help(String buff);
    public:
        /// @brief Constructor
        Pump_Sensor(int vibration_sensor_PIN, int TX, int RX);
        
        /// @brief It does the initialization of the arduino  
        void Initialization();

        /// @brief Reads the value from the pin than calls the SetMessage() function
        void SetMessage();
        
        /// @brief It returns the message 
        /// @return The message from DataBlock class
        String GetMessage();

        /// @brief It reads the status of the pump it can be LOW or HIGH
        void SetPumpStatus();

        /// @brief It returns the status 
        int GetPumpStatus();


        /// @brief Send the message
        void SendSMS(String message);

        /// @brief SIM 900 whether available
        /// @return True or False
        int Available();


        /// @brief Just a simple function to write the message into the output buffer of the SIM900 to send the message or something like that
        void Routine();
};


#endif