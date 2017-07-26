//
// Created by Nathan Welch on 7/22/2017.
//

#include "Sensor.h"

Sensor::Sensor(int X, int Y) {
  x = X;
  y = Y;
  energy = ENERGY_START;
  active = false;
};

void Sensor::setEnergy(int e) {
  energy = e;
}

void Sensor::setActive(bool stat) {
  active = stat;
}

void Sensor::outputSensor() {
  cout << "(" << x << ", " << y << ")    " << active << endl;
}