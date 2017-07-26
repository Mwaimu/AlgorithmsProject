//
// Created by Nathan Welch on 7/22/2017.
//

#ifndef PROJ1_ALGORITHMS_H
#define PROJ1_ALGORITHMS_H

#include "Sensor.h"

#include <vector>

//returns all live sensors (St) for each round
void allActive(vector<Sensor> S, int totalCoverage);
//starts from an empty set of active sensors. iteratively selects a sensor S among live sensors to be added into A.
//S is added iff the sensor covers some intersection point(s) that have not yet been covered by the sensors in A.
void bottomUp(vector<Sensor> S, vector<Point> pointVect ,int totalCoverage);
//starts with a fill set of active sensors. iteratively selects a random sensor 'S' among  live sensors to be take out
//of 'A'.  'S' is taken out iff it is redundant (can be taken out and not effect IPs)
void topDown(vector<Sensor> S, vector<Point> temp, int totalCoverage);

//outputs usage statistics -> round, % alive, % active, average residual energy, and % coverage
void output(int round, vector<Sensor> activeSensors, vector<Sensor> aliveSensors, int totalResEnergy, int totalCoverage);
//prints a vector
void printVect(vector<Sensor> S);

//calculates intersection points
vector<Point> calcIP(vector<Sensor> sensorVect);

//finds the distance between two points
double distBet(Sensor cur, Sensor prev);
double distBetSP(Sensor alive, Point point);

//calculates residual energies for a set of sensors
int calcEnergy(vector<Sensor> active);
//calculates % coverage for a set of sensors
int coverage(vector<Sensor> active);




#endif //PROJ1_ALGORITHMS_H
