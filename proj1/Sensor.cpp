//
// Created by Nathan Welch on 7/22/2017.
//

#include "Sensor.h"

Sensor::Sensor(int X, int Y) {
  x = X;
  y = Y;
  energy = ENERGY_START;
  status = false;
};

void Sensor::setEnergy(int e) {
  energy = e;
}

void Sensor::setSensor(bool stat) {
  status = stat;
}

void Sensor::outputSensor() {
  cout << "(" << x << ", " << y << ")    " << status << endl;
}