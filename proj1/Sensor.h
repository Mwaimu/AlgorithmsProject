//
// Created by Nathan Welch on 7/22/2017.
//

#ifndef PROJ1_SENSOR_H
#define PROJ1_SENSOR_H

#include <vector>
#include <iostream>
#include <algorithm>  //random shuffle
#include <cmath>
using namespace std;

#include "Point.h"


const int ENERGY_START = 5;
const int RADIUS = 5;
const int NUM_SENSORS = 4;  //number of sensors deployed -> 'N'
const int WIDTH = 50;


class Sensor {
public:
  Sensor(int X, int Y);

  int getX() { return x; }
  int getY() { return y; }
  int getEnergy() { return energy; }
  bool getStatus() { return status; }

  void setEnergy(int e);
  void setSensor(bool stat);

  void outputSensor();

private:
  int x, y;  //position
  int energy;  //energy level
  bool status;  //true -> has been looked over
};


#endif //PROJ1_SENSOR_H
