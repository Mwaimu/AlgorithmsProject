//
// Created by Nathan Welch on 7/22/2017.
//

#ifndef PROJ1_SENSOR_H
#define PROJ1_SENSOR_H

#include <vector>
#include <iostream>
#include <algorithm>  //random shuffle
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#include "Point.h"


const int ENERGY_START = 5;
const int RADIUS = 5;
const float NUM_SENSORS = 10.0;  //number of sensors deployed -> 'N'
const int WIDTH = 50;


class Sensor {
public:
  Sensor(int X, int Y);

  int getX() { return x; }
  int getY() { return y; }
  int getEnergy() { return energy; }
  bool getActive() { return active; }

  void setEnergy(int e);
  void setActive(bool stat);

  void outputSensor();

private:
  int x, y;  //position
  int energy;  //energy level
  bool active;  //true -> has been looked over
};


#endif //PROJ1_SENSOR_H
