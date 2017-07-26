//
// Created by Nathan Welch on 7/22/2017.
//

#ifndef PROJ1_POINT_H
#define PROJ1_POINT_H


class Point {
private:
  double x;
  double y;
  bool covered;

public:
  Point();
  Point(double x1, double y1);
  void outputPoint();
  void setCoord(double X, double Y);
  void setCovered(bool c);

  double getX() { return x; }
  double getY() { return y; }
  bool getCovered() { return covered; }


};
#endif //PROJ1_POINT_H
