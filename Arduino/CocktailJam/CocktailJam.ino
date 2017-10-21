/*
 * Arduino code drives stepper motor to move glass carrier
 * and play led animations. 
 * All informations are sent from Raspberry Pi through serial
 * and Arduino send fedbacks about status
 */

// Neopixel Configuration
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN_GLASS_LED  6    //Data IN circular neopixel
#define NBPIXELS_GLASS 16   //LED Quantity on circular neopixel

#define PIN_FRAME_LED 5     //Data IN neopixel strip
#define NBPIXELS_FRAME 40   //LED Quantity on neopixel strip

Adafruit_NeoPixel pixels_glass = Adafruit_NeoPixel(NBPIXELS_GLASS, PIN_GLASS_LED, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_frame = Adafruit_NeoPixel(NBPIXELS_FRAME, PIN_FRAME_LED, NEO_GRB + NEO_KHZ800);

// Stepper Configuration
#include <Stepper.h>

#define Pin_A 8   //1A
#define Pin_B 9   //1B
#define Pin_AA 10 //2A
#define Pin_BB 11 //2B
#define ENABLE 12

const int stepsPerRevolution = 200; //Set step number for one revolution
Stepper STEPPER (stepsPerRevolution, Pin_A, Pin_B, Pin_AA, Pin_BB);
int stepCount =0;

// LoadCell Configuration
// VCC = 3V3!!!
#include "HX711.h"
#define DOUT  3
#define CLK   2


HX711 scale(DOUT, CLK);
 
//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
float calibration_factor = -106600;// 96650; //-106600 worked for my 40Kg max scale setup

void setup() {
  pixels_glass.begin();
  pixels_frame.begin();
  Serial.begin(9600);

  calibration_factor=-10000000;
  scale.set_scale();
  scale.tare();
}


int homing(){ // Initialize carrier position
  // Return ok
  }

void do_tare(){      // Check glass tare
  scale.tare();  //Reset the scale to zero
  Serial.println("Tare done!");

}

int get_weight(){ // check glass weight and return it
   scale.set_scale(calibration_factor);
   Serial.println(scale.get_units(), 5);  
} 

int move_carrier(){ // Move stepper

}


void glass_animation(){ // Indicate glass infill for each step
    //----> Should take the quantity and estimate the time
    for(int i=0;i<NBPIXELS_GLASS;i++){
      pixels_glass.setPixelColor(i, pixels_glass.Color(150,0,150));
      pixels_glass.show();
    }
  }

void frame_animation(){ // Indicate where glass placement
    for(int i=0;i<NBPIXELS_FRAME;i++){  
      pixels_frame.setPixelColor(i, pixels_frame.Color(0,150,150));
      pixels_frame.show();
    }
  }
  

void loop() {
  //glass_animation();
  //frame_animation();

   

   if(Serial.available()){
    char temp = Serial.read();
    if(temp == 't')
      do_tare(); 
   }
   
    get_weight();
}

