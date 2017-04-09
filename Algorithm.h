//
// Created by Nathan Welch on 4/5/2017.
//

#ifndef FOLDER_ALGORITHM_H
#define FOLDER_ALGORITHM_H

#include "Sensor.h"



//our solution to the problem using a greedy method
void greedySolution(vector<Sensor>& S);

//checks if the sensor 's' is needed in the solutions set or not
bool isRedundantMK3(Sensor s, vector<Sensor>& A_t, vector<Sensor>& S_t);

//checks the distance between two sensors
int distBet(Sensor cur, Sensor prev);

//solution is all sensors that are alive. Used as comparison
void allActive(vector<Sensor> S);

//starts with an empty set, solution is sensors added into that are not redundant
void bottomUp(vector<Sensor> S);

//starts with full set, solution is sensors taken away that are redundant
void topDown(vector<Sensor> S);

//function that checks if two sensors are equal
  //possible use in bottom up when "remove from S_t"
//could we implement this to also check for the indices??
bool isEqual(Sensor first, Sensor second);

//prints out the sensors from the vector parameter
void printVect(vector<Sensor> vect);


#endif //FOLDER_ALGORITHM_H
