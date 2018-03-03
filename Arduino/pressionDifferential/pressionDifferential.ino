#include <Arduino.h>
#include <Wire.h>
//#include <Adafruit_ADS1115.h>
#include <Adafruit_ADS1X15-master\Adafruit_ADS1015.h>


Adafruit_ADS1115 ads1115;	// construct an ads1115 at address 0x49

void setup(void)
{
	ads1115.begin();  // Initialize ads1115

	Serial.begin(115200);
	Serial.println("Hello!");

	Serial.println("Getting single-ended readings from AIN0..3");
	Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV)");
}


void loop()
{

	int16_t adc0;

	adc0 = analogRead(A0);

	double erreurV = -0.17;

	double vout = (double)adc0 * 0.004883 + erreurV;

	double pressure = (vout / 5.0 - 0.04) / 0.009;

	Serial.print("AD0 : "); Serial.println(adc0);
	Serial.print("Pression Kpa: "); Serial.println(pressure);
	Serial.print("Pression mbar: "); Serial.println(pressure * 10);
	Serial.print("Vout : "); Serial.println(vout,4);
	
	Serial.println(" ");

	delay(1000);

}
