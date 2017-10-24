/*
 * Arduino code drives stepper motor to move glass carrier
 * and play led animations. 
 * All informations are sent from Raspberry Pi through serial
 * and Arduino send fedbacks about status
 */
//===== Neopixel Configuration ===== 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN_GLASS_LED  6                        //Data IN circular neopixel
#define NBPIXELS_GLASS 16                       //LED Quantity on circular neopixel
#define PIN_FRAME_LED 5                         //Data IN neopixel strip
#define NBPIXELS_FRAME 40                       //LED Quantity on neopixel strip
Adafruit_NeoPixel pixels_glass = Adafruit_NeoPixel(NBPIXELS_GLASS, PIN_GLASS_LED, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_frame = Adafruit_NeoPixel(NBPIXELS_FRAME, PIN_FRAME_LED, NEO_GRB + NEO_KHZ800);
//===== Carrier Configuration =====
//--Stepper
#include <Stepper.h>
#define Pin_A 8   //1A
#define Pin_B 9   //1B
#define Pin_AA 10 //2A
#define Pin_BB 11 //2B
#define ENABLE 12
const int stepsPerRevolution = 200;             //Set step number for one revolution
Stepper STEPPER (stepsPerRevolution, Pin_A, Pin_B, Pin_AA, Pin_BB);
int speed=60;
//--Homing
#define home_stop 4                             //Switch pin for homing
//===== LoadCell Configuration ===== 
// VCC = 3V3!!!
#include "HX711.h"
#define DOUT  3
#define CLK   2
HX711 scale(DOUT, CLK);                         // Initialize loadcell on I2C pins
float calibration_factor=-10000000;             //Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
//===== Timer ===== 
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
//--- Arduino boot actions------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);                           // Start serial communication to 9600
  pixels_glass.begin();
  pixels_frame.begin();
}
//------------------------------------------------------------------------------------------------
void homing(){                                  // Initialize carrier position
    STEPPER.setSpeed(speed);                    // set the speed
    STEPPER.step(50);                           // Move stepper 50 steps Clockwise
    int j=0;                                    // variable for increment
    
    while(home_stop==0){                    // While home switch is not activated movve stepper back to it.
        j--;
        STEPPER.step(j);    
    }   
    Serial.println("OK");                         // Send position confirmation   
  }
void do_tare(){                                 // Check glass tare
  scale.tare();                                 // Reset the scale to zero
  Serial.println("OK");                           // Send tare confirmation
}
void get_weight(){                              // check glass weight and return it
   scale.set_scale(calibration_factor);
   Serial.println(scale.get_units(), 5);
} 
void move_carrier(){                            // Move stepper
    int step_to_do = Serial.read();
      
    STEPPER.setSpeed(speed);                    // set the speed
    STEPPER.step(step_to_do);                   // +Clockwise / -Counterclockwise
    Serial.println("OK");                         // Send position confirmation   
}
void glass_animation(){                         // Indicate glass infill for each step take the quantity and estimate the time
    /*
    ---- Example table ----
    |Quantity| Infill Duration  |
    |   1 cl |  1000 ms         |
    |   2 cl |  2000 ms         |
    |   3 cl |  3000 ms         |
    
    Serial.read ("duration_from_raspberry");
    int InfillDuration= ("duration_from_raspberry");
    delay_step_glass=NBPIXELS_GLASS/InfillDuration; // Estimate time between each step
    int i=0;
    
    currentMillis = millis();
    
    for(i==NBPIXELS_GLASS){
      pixels_glass.setPixelColor(i, pixels_glass.Color(150,0,150));
        if (currentMillis - previousMillis >= delay_step_glass) {
            previousMillis = currentMillis;
            i++;
            pixels_glass.show();
        }      
    }
    */
  }
void frame_animation(){ // Indicate glass placement
    for(int i=0;i<NBPIXELS_FRAME;i++){  
      pixels_frame.setPixelColor(i, pixels_frame.Color(0,150,150));
      pixels_frame.show();
    }
  }
  
void loop() {
    
    char action;
    
    /*Serial.read("action");
    
    switch (action) {
        case "homing":
            homing();
            break;
        case "tare":
            do_tare();
            break;
        case "get_weight":
            get_weight();
            break;
        case "move_carrier":
            move_carrier();
            break;
        case "glass_animation":
            glass_animation();
            break;
        case "frame_animation":
            frame_animation();
            break;
        default: 
        // statements
        break;
    }   
    */
}
