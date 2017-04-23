#ifndef FOLDER_ALGORITHM_H
#define FOLDER_ALGORITHM_H

#include "Sensor.h"



//our solution to the problem using a greedy method
void greedySolution(vector<Sensor>& S);

//checks if the sensor 's' is needed in the solutions set or not
bool isRedundantMK3(Sensor s, vector<Sensor>& A_t, vector<Sensor>& S_t);

//checks the distance between two sensors
double distBet(Sensor cur, Sensor prev);

//solution is all sensors that are alive. Used as comparison
void allActive(vector<Sensor> S);

//starts with an empty set, solution is sensors added into that are not redundant
void bottomUp(vector<Sensor> S);

//starts with full set, solution is sensors taken away that are redundant
void topDown(vector<Sensor> S);

//function that checks if two sensors are equal
bool isEqual(Sensor first, Sensor second);

//
float percentCoverageActiveSensors(vector<Sensor>& active_sensors, const int numTestPoints);

//
float avgResidualEnergy(vector<Sensor>& S_t);

//
float percentActiveSensors(const int S, const int A_t);

//
float percentAliveSensors(const int S, const int S_t);

//prints out all the elements of a vector
void printVect(vector<Sensor>& S);

#endif //FOLDER_ALGORITHM_H

