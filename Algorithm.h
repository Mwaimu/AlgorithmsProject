//
// Created by Nathan Welch on 4/5/2017.
//

#ifndef FOLDER_ALGORITHM_H
#define FOLDER_ALGORITHM_H

#include "Sensor.h"


void greedySolution(vector<Sensor>& S);

bool isRedundantMK3(Sensor s, vector<Sensor>& A_t);

int distBet(Sensor cur, Sensor prev);

void allActive(vector<Sensor> S);

#endif //FOLDER_ALGORITHM_H
