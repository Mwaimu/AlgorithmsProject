#ifndef FOLDER_SENSOR_H
#define FOLDER_SENSOR_H

#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

//------- Global Variables -------//
const int R = 5; //sensor radius
const int LENGTH = 20; //length of the area that the sensors go in

class Sensor {
public:
  Sensor(); //constructor
  Sensor(double x1, double y1);

  int getPower() { return power; }
  double getX() { return x; }
  double getY() { return y; }

  void setPower(const int p);
  void setX(const double x1);
  void setY(const double y1);

private:
  double x;
  double y;
  int power;
};

#endif //FOLDER_SENSOR_H