/*
 * This Arduino code manages glass moving carrier, led animation and glass infill.
 * Raspberry Pi sends commands through serial and Arduino do the rest.
 * 
 * For hardware connection, see schematic: https://github.com/fablabs-ch/bar-o-matic/blob/master/hardware/bar-o-matic_bb.png
 *
 * Ensure to set the correct parameters according to the hardware you have choosen. All constant below marked with * have to be customized to avoid bad behavior.
 *
 * FabLabs-CH for swiss fablabs
 * Copyright (C) 2018  Christophe Cachin & Gaétan Collaud
 */
#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <BasicStepperDriver.h>
#include <HX711.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include "cocktail-serial.h";

//=== MAIN CONFIGURATION =================================================================================================================================

//Homing
#define PIN_HOME 53                            		//Switch pin for homing (endstop)
#define MAXPOSITION 1000							//Maximum carrier travel in millimeter. *Depending on machine size

//-Stepper
#define MOTOR_STEPS 200							//-Number of steps for choosen motor stepper. *Read the motor datasheet to set it properly
#define RPM 120
#define MICROSTEPS 16								//Define microstep. *Depends on your hardware configuration. 1, 8 or 16. 16 is maybe to fine for this machine has to be tested
#define BELTPITCH 2										//Distance between two teeth on the belt. *Read the belt datasheet for correct parameter
#define TEETHPULLEY 20								//Number of teeth on the pulley. *Read the pulley datasheet for correct parameter
const int STEPS_PER_MM = (MOTOR_STEPS * MICROSTEPS)/(BELT_PITCH*TEETHPULLEY); 	// Number of step to get 1mm

#define MOTOR_ACCEL_SPEED 2000				// Set acceleration speed
#define MOTOR_DECEL_SPEED 1000				// Set deceleration speed

#define PIN_DIR 3                                   		//Pin on Pololu 4988
#define PIN_STEP 2

//-Servo
#define NBSERVOS 10
#define SERVO_OPEN_DEGR 0						//Servo angle for open state. *set the correct angle to get correct flow
#define SERVO_CLOSE_DEGR 180					//Servo angle for close state. *set the correct angle to close the flow properly

//-Ledstrip
#define PIN_GLASS_LED  44                        	//Data IN circular neopixel
#define NBPIXELS_GLASS 16							//LED Quantity on circular neopixel
#define PIN_FRAME_LED 45                         	//Data IN neopixel strip
#define NBPIXELS_FRAME 40                       	//LED Quantity on neopixel strip

//-LoadCell
#define LOAD_CELL_DOUT  3
#define LOAD_CELL_CLK   2



BasicStepperDriver stepper(MOTOR_STEPS, PIN_DIR, PIN_STEP);
Servo servo[NBSERVOS];                              					//Servo object in an array
HX711 scale(LOAD_CELL_DOUT, LOAD_CELL_CLK);         //Initialize loadcell on I2C pins
Adafruit_NeoPixel pixels_glass = Adafruit_NeoPixel(NBPIXELS_GLASS, PIN_GLASS_LED, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_frame = Adafruit_NeoPixel(NBPIXELS_FRAME, PIN_FRAME_LED, NEO_GRB + NEO_KHZ800);
CocktailSerial cocktailSerial(&Serial);


int currentPosition =0;
int steps_to_do=0;
int endstop=0;
int servo_pins[10]={4,5,6,7,8,9,10,11,12,13};	    //Define servo pins in an array
float CALIBRATION_FACTOR=-10000000;            //Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
int targetWeight=0;											//Weight initialization
int currentWeight=0;
int infill_purcentage=0;
int pixelGlassToDisplay=0;
int pixelFrameToDisplay=0;






//=== CARRIER =================================================================================================================================
void homeFunction(){									// Initialize carrier position
    Serial.println("Home called");
	stepper.move(50*MICROSTEPS);

    int j=0;
    int endstop=digitalRead(PIN_HOME);

    if(endstop==LOW){            				    //While home switch is not activated move stepper back to it.
        j--;
        stepper.move(j);
    }
    currentPosition = 0;
    Serial.println("OK");                      	 		//Send position confirmation
}

void move_carrier(){									//Move carrier

	int targetPosition = (distMm);

	pixelFrameToDisplay=(targetPosition/MAXPOSITION)/NBPIXELS_FRAME;	//Calculate until which pixel the leds have to be turned on according to sent position.

    for(int i=0;i<pixelFrameToDisplay;i++){
        pixels_frame.setPixelColor(i, pixels_frame.Color(0,150,0));  	//Set green color
        pixels_frame.show();
    }
	
	steps_to_do=(targetPosition-currentPosition)*STEPS_PER_MM;

	stepper.move(steps_to_do);
	currentPosition=targetPosition;
	fill();
	Serial.println("OK");
}




//=== WEIGHT & FILL============================================================================================================================
void tareFunction(){ 								// Check glass tare
	Serial.println("Tare called");
	scale.tare();                                 		//Reset the scale to zero
	Serial.println("OK");                        	//Send tare confirmation
	cocktailSerial.run();
}

float get_weight(){                              	//Check glass weight and return it
    scale.set_scale(CALIBRATION_FACTOR);
    Serial.println(scale.get_units(), 5);
	cocktailSerial.run();
    return scale.get_units();
}

void fillFunction(int distMm, int weightGr, int nServo){		//Open Servo x while weight is not equal target weight including glass animation
	Serial.print("Fill called, dist=");
    Serial.print(distMm);
    Serial.print(", weight=");
    Serial.println(weightGr);
	Serial.print(", Servo=");
    Serial.println(nServo);
	
	servo[nServo].write(SERVO_CLOSE_DEGR);
	
	targetWeight=weightGr;
	currentWeight=get_weight();

	do{
		servo[nServo].write(SERVO_OPEN_DEGR);														//Fill glass
		pixelGlassToDisplay=NBPIXELS_GLASS*currentWeight/targetWeight;					//Calculate which pixel to display according to current weight
		pixels_glass.setPixelColor(pixelGlassToDisplay, pixels_glass.Color(50,90,255));	//Set dark blue color
		pixels_glass.show(); 																						//Show glass animation	
		cocktailSerial.run();
	}while(currentWeight<targetWeight);
	
	move_carrier(distMm);
	cocktailSerial.run();
}

void closeServos(){
	 for(int s=0; s<NBSERVOS; s++)
   {
      servo[s].write(SERVO_CLOSE_DEGR);
   }
	
}









void setup() {
	Serial.begin(115200);                       			//Start serial communication to 115200

    pinMode(PIN_HOME,INPUT);
    digitalWrite(PIN_HOME, HIGH);                   //Activate pullup home pin
  
	stepper.begin(RPM, MICROSTEPS);
	stepper.enable();
	stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL_SPEED, MOTOR_DECEL_SPEED);

	int i=0;
	int j=4;

	for(int i=0; i<NBSERVOS; i++){
        servo[i].attach(servo_pins[i]);
    }
	
	closeServos();
	tareFunction();
	
    cocktailSerial.registerFunctions((void*)homeFunction, (void*)tareFunction, (void*)fillFunction);
}


 
void loop() {
    cocktailSerial.run();
}
