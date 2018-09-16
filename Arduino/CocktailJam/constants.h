#ifndef CONSTANTS_H
#define CONSTANTS_H

// === MAIN CONFIGURATION =================================================================================================================================

// Homing
//#define PIN_HOME 53      // Switch pin for homing (endstop)
#define PIN_HOME 12      // Switch pin for homing (endstop)
#define MAXPOSITION 1000 // Maximum carrier travel in millimeter. *Depending on machine size

// Stepper


#define MOTOR_STEPS 200                                                             // Number of steps for choosen motor stepper. *Read the motor datasheet to set it properly
#define RPM 120
#define MICROSTEPS 4                                                             // Define microstep. *Depends on your hardware configuration. 1, 8 or 16. 16 is maybe to fine for this machine has to be tested
#define BELT_PITCH 2                                                              // Distance between two teeth on the belt. *Read the belt datasheet for correct parameter
#define TEETHPULLEY 20                                                            // Number of teeth on the pulley. *Read the pulley datasheet for correct parameter
const int STEPS_PER_MM = (MOTOR_STEPS * MICROSTEPS) / (BELT_PITCH * TEETHPULLEY); // Number of step to get 1mm
const float STEPS_PER_MM_REVERSE = 1.0/STEPS_PER_MM;

#define MOTOR_RPM 100
#define MOTOR_ACCEL_SPEED 1000 // Set acceleration speed
#define MOTOR_DECEL_SPEED 1000 // Set deceleration speed

// Pin on Pololu 4988
#define PIN_STEPPER_ENABLED A1
#define PIN_STEPPER_DIR A3
#define PIN_STEPPER_STEP A2

// Servo
#define NBSERVOS 6

// Ledstrip
#define PIN_GLASS_LED 44  // Data IN circular neopixel
#define NBPIXELS_GLASS 16 // LED Quantity on circular neopixel
#define PIN_FRAME_LED 45  // Data IN neopixel strip
#define NBPIXELS_FRAME 40 // LED Quantity on neopixel strip

// LoadCell
#define LOAD_CELL_DOUT A4
#define LOAD_CELL_CLK A5

//Pump
#define PIN_PUMP 9
#define PIN_PRESSURE_SENSOR A0

#endif
