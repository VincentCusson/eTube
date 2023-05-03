//****************************************************************************//
// Puara Module Manager                                                       //
// Metalab - Société des Arts Technologiques (SAT)                            //
// Input Devices and Music Interaction Laboratory (IDMIL), McGill University  //
// Edu Meneses (2022) - https://www.edumeneses.com                            //
//****************************************************************************//

unsigned int firmware_version = 20220906;

#include "Arduino.h"
#include <BleGamepad.h>
// Include Puara's module manager
// If using Arduino.h, include it before including puara.h
#include "puara.h"

// Include Puara's high-level descriptor library if planning to use the high-level
// descriptors' functions
#include "puara_gestures.h"

/* Include Libmapper (and liblo) to send and receive OSC messages
 * 
 */
#include <mapper.h>  // libmapper

BleGamepad bleGamepad("eTube","Vincent Cusson",90);

#define numOfButtons 2

byte previousButtonStates[numOfButtons];
byte currentButtonStates[numOfButtons];
byte buttonPins[numOfButtons] = { 21, 19 };
byte physicalButtons[numOfButtons] = { 1, 2 };

// declaring the libmapper device
mpr_dev lm_dev = 0;

// Initialize Puara's module manager
Puara puara;

// dummy sensor data
float sensor;
std::string sigName = "dummy_sensor";
std::string inSigName = "dummy_income";

// creating/declaring libmapper information on dummy sensor data
float lm_min = 0.0;
float lm_max = 10.0;
mpr_sig dummy_signal = 0;

// creating a handler function for the incoming signal + signal
void lm_callback(mpr_sig sig, mpr_sig_evt evt, mpr_id inst, int length,
                mpr_type type, const void* value, mpr_time time) {
    std::cout << "value received: " << *((float*)value) << std::endl;
}
mpr_sig dummy_income = 0;

/*
 * Creating liblo addresses for sending direct OSC messages.
 * Those will be populated with IP address and port provided
 * by the puara module manager.
 */
lo_address osc1;
lo_address osc2;

// Declare a new liblo server and set an error callback
void error(int num, const char *msg, const char *path) {
    printf("Liblo server error %d in path %s: %s\n", num, path, msg);
    fflush(stdout);
}
lo_server_thread osc_server;

/* 
 * Generic handler that catches any incoming messages and display them. 
 * Returning 1 means that the message has not been fully handled and the server 
 * should try other methods.
 * (based on https://github.com/radarsat1/liblo/blob/master/examples/example_server.c)
 */
int generic_handler(const char *path, const char *types, lo_arg ** argv,
                    int argc, lo_message data, void *user_data) {
    int i;

    printf("OSC message received; path: %s\n", path);
    for (i = 0; i < argc; i++) {
        printf("arg %d '%c' ", i, types[i]);
        lo_arg_pp((lo_type)types[i], argv[i]);
        printf("\n");
    }
    printf("\n");
    fflush(stdout);

    return 1;
}

void setup() {
    #ifdef Arduino_h
        Serial.begin(115200);
    #endif

    for (byte currentPinIndex = 0 ; currentPinIndex < numOfButtons ; currentPinIndex++){
        pinMode(buttonPins[currentPinIndex], INPUT_PULLUP);
        previousButtonStates[currentPinIndex] = HIGH;
        currentButtonStates[currentPinIndex] =  HIGH;
    }
    BleGamepadConfiguration bleGamepadConfig;
    bleGamepadConfig.setButtonCount(numOfButtons);
    bleGamepadConfig.setAutoReport(false);
    bleGamepad.begin(&bleGamepadConfig);
    

    // // Optional: set a custom version (firmware) number
    // puara.set_version(firmware_version);

    /*
     * the Puara start function initializes the spiffs, reads config and custom json
     * settings, start the wi-fi AP/connects to SSID, starts the webserver, serial 
     * listening, MDNS service, and scans for WiFi networks.
     */
    // puara.start();

    // // Populating liblo addresses and server port
    // osc1 = lo_address_new(puara.getIP1().c_str(), puara.getPORT1Str().c_str());
    // osc2 = lo_address_new(puara.getIP2().c_str(), puara.getPORT2Str().c_str());
    // osc_server = lo_server_thread_new(puara.getLocalPORTStr().c_str(), error);
    
    // // Add method that will match any path and args and start server
    // lo_server_thread_add_method(osc_server, NULL, NULL, generic_handler, NULL);
    // lo_server_thread_start(osc_server);

    // // creating the libmapper device
    // lm_dev = mpr_dev_new(puara.get_dmi_name().c_str(), 0);

    // // Creating dummy signals
    // dummy_signal = mpr_sig_new(lm_dev, MPR_DIR_OUT, sigName.c_str(), 1, MPR_FLT, "un",
    //                             &lm_min, &lm_max, 0, 0, 0);
    // dummy_income = mpr_sig_new(lm_dev, MPR_DIR_IN, inSigName.c_str(), 1, MPR_FLT, "un",
    //                             &lm_min, &lm_max, 0, lm_callback,
    //                             MPR_SIG_UPDATE);

    // // Printing custom settings stored:
    // std::cout << "\n" 
    // << "Settings stored in settings.json:\n" 
    // << "Hitchhiker: " << puara.getVarText ("Hitchhiker") << "\n"
    // << "answer_to_everything: " << puara.getVarNumber("answer_to_everything") 
    // << "\n" << std::endl;
}

void loop() {
    // Poll libmapper
    // mpr_dev_poll(lm_dev, 0);

    // // Update dummy sensor with random number and send (OSC and libmapper)
    // sensor = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10));

    // // updating libmapper dummy_signal
    // mpr_sig_set_value(dummy_signal, 0, 1, MPR_FLT, &sensor);

    // /* 
    //  * Sending OSC messages.
    //  * If you're not planning to send messages to both addresses (OSC1 and OSC2),
    //  * it is recommended to set the address to 0.0.0.0 to avoid cluttering the 
    //  * network (WiFiUdp will print an warning message in those cases).
    //  */
    // if (puara.IP1_ready()) { // set namespace and send OSC message for address 1
    //     std::string oscNamespace = "/" + puara.get_dmi_name() + "/" + sigName;
    //     lo_send(osc1, oscNamespace.c_str(), "f", sensor);
    //     //sendOSC(puara.getIP1(),puara.getPORT1(), puara.get_dmi_name(), sigName, sensor);
    // }
    // if (puara.IP2_ready()) { // set namespace and send OSC message for address 2
    //     std::string oscNamespace = "/" + puara.get_dmi_name() + "/" + sigName;
    //     lo_send(osc2, oscNamespace.c_str(), "f", sensor);
    //     //sendOSC(puara.getIP2(),puara.getPORT2(), puara.get_dmi_name(), sigName, sensor);
    // }

    // // run at 100 Hz
    // vTaskDelay(10 / portTICK_PERIOD_MS);
    if(bleGamepad.isConnected())
    {
        for (byte currentIndex = 0 ; currentIndex < numOfButtons ; currentIndex++)
        {
        currentButtonStates[currentIndex]  = digitalRead(buttonPins[currentIndex]);

        if (currentButtonStates[currentIndex] != previousButtonStates[currentIndex])
        {
            if(currentButtonStates[currentIndex] == LOW)
            {
            bleGamepad.press(physicalButtons[currentIndex]);
            }
            else
            {
            bleGamepad.release(physicalButtons[currentIndex]);
            }
        } 
        }
        
        if (currentButtonStates != previousButtonStates)
        {
        for (byte currentIndex = 0 ; currentIndex < numOfButtons ; currentIndex++)
        {
            previousButtonStates[currentIndex] = currentButtonStates[currentIndex]; 
        }
        
        bleGamepad.sendReport();
        }
        
        delay(20);
    }
}

/* 
 * The Arduino header defines app_main and conflicts with having an app_main function
 * in code. This ifndef makes the code valid in case we remove the Arduino header in
 * the future.
 */
#ifndef Arduino_h
    extern "C" {
        void app_main(void);
    }

    void app_main() {
        setup();
        while(1) {
            loop();
        }
    }
#endif
