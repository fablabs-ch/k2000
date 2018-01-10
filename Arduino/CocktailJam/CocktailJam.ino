/*
 * Arduino code drives stepper motor to move glass carrier and play led animations.
 * Raspberry Pi sends commands through serial and Arduino send feedbacks about status
 * 
 * FabLabs-CH for swiss fablabs
 * Copyright (C) 2018  Christophe Cachin & Gaétan Collaud
 */

//===== Carrier Configuration =====
//Homing
#define HOME 53                            			    //Switch pin for homing (endstop)
int endstop=0;

//-Stepper
#include <Arduino.h>
#include "BasicStepperDriver.h"
#define MOTOR_STEPS 200
#define RPM 120
#define MICROSTEPS 16

#define DIR 3                                      //Pin on Pololu 4988
#define STEP 2

BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

#define STEPS_PER_MM  80 							             //Step per millimeter: (step per revolution * driver_microstep) / (belt pitch * teeth number pulley) => (200*16)/(2*20)
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000

#define MAXPOSITION 1000							             //Maximum carrier travel in millimeter
int currentPosition =0;	
int steps_to_do=0;

//-Servos
#include <Servo.h>
#define NBSERVOS 10
Servo servo[NBSERVOS];                                  //Servo object in an array
int servo_pins[10]={4,5,6,7,8,9,10,11,12,13};	    //Define servo pins in an array


#define OPEN 0										                //Servo angle for open state
#define CLOSE 180									                //Servo angle for close state

//===== LoadCell Configuration =====
#include "HX711.h"
#define DOUT  3
#define CLK   2
HX711 scale(DOUT, CLK);                         	//Initialize loadcell on I2C pins
float CALIBRATION_FACTOR=-10000000;             	//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands

int targetWeight=0;									              //Weight initialization
int currentWeight=0;
int infill_purcentage=0;

//===== Neopixel Configuration =====
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN_GLASS_LED  44                        	//Data IN circular neopixel
#define NBPIXELS_GLASS 16                      	 	//LED Quantity on circular neopixel
#define PIN_FRAME_LED 45                         	//Data IN neopixel strip
#define NBPIXELS_FRAME 40                       	//LED Quantity on neopixel strip
Adafruit_NeoPixel pixels_glass = Adafruit_NeoPixel(NBPIXELS_GLASS, PIN_GLASS_LED, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_frame = Adafruit_NeoPixel(NBPIXELS_FRAME, PIN_FRAME_LED, NEO_GRB + NEO_KHZ800);

int pixelGlassToDisplay=0;
int pixelFrameToDisplay=0;


void setup() {
	Serial.begin(115200);                       	  //Start serial communication to 115200

  pinMode(HOME,INPUT);
  digitalWrite(HOME, HIGH);                       //Activate pullup home pin
  
	stepper.begin(RPM, MICROSTEPS);
	stepper.enable();
	stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);

	int i=0;
	int j=4;

	for(int i=0; i<NBSERVOS; i++){
    servo[i].attach(servo_pins[i]);
  }

  
}




//=== CARRIER =================================================================================================================================
void homing(){// Initialize carrier position
    stepper.move(50*MICROSTEPS);

    int j=0;                                    	
    int endstop=digitalRead(HOME);
    
    if(endstop==LOW){            				    //While home switch is not activated move stepper back to it.
        j--;
        stepper.move(j);
    }
	  currentPosition = 0;
    Serial.println("OK");                      	 	//Send position confirmation
  }

void move_carrier(){								              //Move carrier

	int targetPosition = ("value_received_from_RPI_mm");

	
	pixelFrameToDisplay=(targetPosition/MAXPOSITION)/NBPIXELS_FRAME;	//Calculate until which pixel the leds have to be turned on according to sent position.

    for(int i=0;i<pixelFrameToDisplay;i++){
      pixels_frame.setPixelColor(i, pixels_frame.Color(0,150,0));  //Set green color
      pixels_frame.show();
    }
	
	steps_to_do=(targetPosition-currentPosition)*STEPS_PER_MM;

	stepper.move(steps_to_do);
	currentPosition=targetPosition;
	fill();
	Serial.println("OK");
}




//=== WEIGHT & FILL============================================================================================================================
void do_tare(){ // Check glass tare
	scale.tare();                                 	//Reset the scale to zero
	Serial.println("OK");                        	  //Send tare confirmation
}

float get_weight(){                              	//Check glass weight and return it
   scale.set_scale(CALIBRATION_FACTOR);
   Serial.println(scale.get_units(), 5);
   return scale.get_units();
}

void fill(){										                  //Open Servo x while weight is not equal target weight including glass animation

	servo[1].write(CLOSE);
	
	targetWeight=("value_received_from_RPI_gr");
	currentWeight=get_weight();

	do{
		servo[1].write(OPEN);													//Fill glass
		pixelGlassToDisplay=NBPIXELS_GLASS*currentWeight/targetWeight;					        //Calculate which pixel to display according to current weight
		pixels_glass.setPixelColor(pixelGlassToDisplay, pixels_glass.Color(50,90,255));	//Set dark blue color
		pixels_glass.show();                          //Show glass animation						
	}while(currentWeight<targetWeight);
	
}




 
void loop() {

/*
		//Status 	- s:{distanceInMm}:{weightInGr}
		//Fill 			- f:{distanceInMm}:{gr}
		//Tare		- t
		//Home		- h
		
		if (stream) {																	    //Get and parse rpi serial commands
			while (stream->available()) {
				char c = stream->read();
				if (c == '\r') {															//Ignore \r
				} else if (c == '\n') {														//Save only from \n 
					anaylseLine(buffer);
					buffer = String();
				} else {
					buffer += c;
				  }
			}
		}

buffer.indexOf("{"}
*/
}
