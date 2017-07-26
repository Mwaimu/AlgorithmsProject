//
// Created by Nathan Welch on 7/22/2017.
//

#include "Point.h"

#include <iostream>
using namespace std;

Point::Point() {
  covered = 0;
}

Point::Point(double x1, double y1) {
  x = x1;
  y = y1;
}

void Point::outputPoint() {
  cout << "    (" << x << ", " << y << ")  " << covered << endl;
}

void Point::setCoord(double X, double Y) {
  x = X;
  y = Y;
}

void Point::setCovered(bool c) {
  covered = c;
}