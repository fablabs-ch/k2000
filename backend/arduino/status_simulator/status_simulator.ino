

#include "constants.h"
#include "terminal.h"
#include "status.h"
#include "scale.h"
#include "HX711.h"



HX711 hx711(PIN_HX711_DATA, PIN_HX711_SCK);

Scale scale(&hx711);
Terminal terminal(&Serial);
Status status(&terminal, &scale);



void homeCommand(){
	status.setDistMm(0);
	Serial.println("Home received");
}

void tareCommand(){
	scale.tare();
	Serial.println("Tare received");
}
void moveCommand(int dist){
	status.setDistMm(dist);
	Serial.print("Move received: ");
	Serial.println(dist);
}


void setup() {
	Serial.begin(115200);
	Serial.println("start");

	terminal.ptrHomeCommand = homeCommand;
	terminal.ptrTareCommand = tareCommand;
	terminal.ptrMoveCommand = moveCommand;
}

void loop() {
	unsigned long nowMs = millis();
	terminal.run();
	scale.run(nowMs);
	status.run(nowMs);
}
