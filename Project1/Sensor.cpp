#include "Sensor.h"

Sensor::Sensor() {
  x = rand() % LENGTH + 1;
  y = rand() % LENGTH + 1;
  power = 300;
}

Sensor::Sensor(double x1, double y1) {
  x = x1;
  y = y1;
  power = 300;
}

void Sensor::setPower(const int p) {
  power = p;
  return;
}

void Sensor::setX(const double x1) {
  x = x1;
  return;
}

void Sensor::setY(const double y1) {
  y = y1;
  return;
}