//
// Created by Nathan Welch on 4/5/2017.
//

#include "Sensor.h"

Sensor::Sensor() {
	x = rand() % 51;
	y = rand() % 51;
	power = 300;
}

void Sensor::setPower(const int p) {
	power = p;
	return;
}

void Sensor::setX(const int x1) {
	x = x1;
	return;
}

void Sensor::setY(const int y1) {
	y = y1;
	return;
}


