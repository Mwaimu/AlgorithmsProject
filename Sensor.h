//
// Created by Nathan Welch on 4/5/2017.
//

#ifndef FOLDER_SENSOR_H
#define FOLDER_SENSOR_H

#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;


class Sensor {
public:

  //copy constructor for vectors
//  I have one made from a different class I'll pull it up later


  Sensor(); //constructor

	int getPower() { return power; }
	int getX() { return x; }
	int getY() { return y; }

	void setPower(const int p);
	void setX(const int x1);
	void setY(const int y1);


private:
	int x;
	int y;
	int power;
};


#endif //FOLDER_SENSOR_H
