//
// Created by Nathan Welch on 7/22/2017.
//

#ifndef PROJ1_POINT_H
#define PROJ1_POINT_H


class Point {
private:
  double x;
  double y;

public:
  Point();
  Point(double x1, double y1);
  void outputPoint();
  void setCoord(double X, double Y);


};
#endif //PROJ1_POINT_H
