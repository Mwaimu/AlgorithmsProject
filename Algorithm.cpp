#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

#include <algorithm>  //random shuffle

#include "Sensor.h"
#include "Algorithm.h"

using namespace std;

//------- Global Variables -------//
const int R = 5; //sensor radius
const int LENGTH = 50; //length of the area that the sensors go in



int main() {
	srand(time(NULL));

// ------- variable declarations ------- //
	int numSensors;
	vector<Sensor> S; //initialize empty vector

	cout << "enter number of nodes to generate: ";
		cin >> numSensors;

		//makes "numSensors" Sensors and puts them into a vector
		for(int i = 0; i < numSensors; i++) {
			Sensor newSensor;
			S.push_back(newSensor);
		}

  cout << "Greedy Solution" << endl;
  greedySolution(S);

  cout << "All Active" << endl;
  allActive(S);

  cout << "Bottom Up" << endl;
  bottomUp(S);

  cout << "Top Down" << endl;
  topDown(S);



	return 0;
}

void greedySolution(vector<Sensor>& S) {  //will return A_t
// ------- Definitions ------- //
/*	s / A[i] = specific sensor
		S = set of sensors
		R = sensing radius
		n = number of sensors
		A_t = set of sensors returned by algorithm at round t
		S_t = set of sensors alive at round t
		/* 	so we have to come up with an algorithm that for each iteration will
		 		output a subset of A that has the same coverage as all of the alive
				sensors also have to keep track of the number of rounds this lasts
		**
*/
  int twoR = 2 * R;

	vector<Sensor> S_t;  //set of sensors alive at round t
	vector<Sensor> A_t;  //set of sensors returned by algorithm at round t


	S_t = S; //all sensors are alive in the beginning
	int rounds = 0;
	while(S_t.size() != 0) {
		rounds++;

		A_t.clear();  //solution set for each iteration to be output for every round, gets deleted so new elements can be added into it
		for(int i = 0; i < S_t.size(); i++) {
			if(S_t[i].getPower() == 0 ) //only gets taken out of S_t if power is depleted
				S_t.erase(S_t.begin() + (i - 1) );  //take S_t[i] out of S_t
					//starts at beginning and goes to the ith place in the vector and takes out that place

			else if (S_t.size() == 1 ){
				A_t.push_back(S_t[i]);  //add S_t[i] to A_t
				S_t[i].setPower(S_t[i].getPower() - 1);
			}

			else if( !isRedundantMK3(S_t[i], A_t, S_t) )  //if not redundant add to solution
				A_t.push_back(S_t[i]);  //add S_t[i] to A_t
				S_t[i].setPower(S_t[i].getPower() - 1);

		//else is redundant, don't add to A_t, basically skip to the next sensor
		}
	}
}

bool isRedundantMK3(Sensor s, vector<Sensor>& A_t, vector<Sensor>& S_t){
//Has to have at least 2 sensors in A_t
/* ------- Definitions ------- //
	IP = intersection Point
	q = sensors in A_t
  A_t = set of non-redundant sensors (to be output)
	s = current sensor looking at from S_t
*/
	if (S_t.size() == 1 ) {
		return false;
	}

  int twoR = 2 * R;

	vector<Sensor> qSensors;
	vector<Sensor> ipTest;

	for(int i = 0; i < A_t.size(); i++) {
		if(distBet(A_t[i], s) < twoR)
			qSensors.push_back(A_t[i]);  //put A_t[i] in qSensors
	}

	for(int i = 0; i < qSensors.size() - 2; i++) {
		for(int j = i + 1; j < qSensors.size(); i++) {   //THINK ABOUT THIS
			if(i == j)
				i = i;  //skip, because same sensor
			else if(distBet( qSensors[i], qSensors[j] ) < twoR) {
				i = i;
				makes IP
				//find location using Q[i] & distance tracker from wateringgrass prob
			if(distBet(IP, s) < R)  // IP in radius of s
				qSensors.push_back(A_t[i]);  //put IP in testArray
			}
		}
	}

	for(int i = 0; i < ipTest.size(); i++) { //for each IP point -> i
		int count = 0; //resets count

		for (int j = 0; j < A_t.size(); j++) { //for each sensor in A_t -> j
			if( distBet( A_t[j], ipTest[i] ) < R  )//means IP still redundant
				count++;
		} //for each q
		if( count == 0)  //means IP NEVER covered
			return false; //means needed -> b/c there's one point never covered
	} //for each IP
	return true; //got all the way through all points being covered -> redundant
}

//finds the distance between two points
int distBet(Sensor cur, Sensor prev) {
	//might have to cast these (inside sqrt) as a float just to make sure
	//there are no rounding errors beforehand
	return abs( sqrt( (cur.getX() - prev.getX())^2 + (cur.getY() - prev.getY())^2 ) );
	//this also needs to be ABSOLUTE VALUE
}


//OTHER APPROACHES:

//1
void allActive(vector<Sensor> S){ //for (each round t) decrement energy when tested for duration
	vector<Sensor> A_t = S;//the solution is all sensors in A
	int round = 0;
  while(A_t.size() != 0) {
    for(int i = 0; i < A_t.size(); i++) //for all elements in A_t
      if(A_t[i].getPower() != 0) //if still power
        A_t[i].setPower(A_t[i].getPower() - 1); //decrease power
      else
        //remove from A_t

    round++;
    cout << "Round: " << round << endl;
    printVect(A_t);  //prints what's in A_t
  }
	return;
}

//2
void bottomUp(vector<Sensor> S){
/*Random-bottom-up: This algorithm starts from an empty set of active sensors A.
It iteratively selects a sensor s among those that are alive to be added to A.
The sensor s is added to A only if the sensor covers some intersection points
that are currently not covered by the sensor in A.
*/

  vector<Sensor> S_t = S;
  vector<Sensor> A_t;
	while (S_t.size() != 0) // while there are live sensors
	{
    A_t.clear();  //solution set for each iteration to be output for every round, gets deleted so new elements can be added into it
    random_shuffle(A_t.begin(), A_t.end());//puts sensors in a random order

		for (int i = 0; i < A_t.size(); i++){
      //			j = arrRand[i] // j = rand num @ iteration i of arrRand
      if( A_t[i].getPower() == 0) {
        i=i; //just to skip stiff


/*  this won't work because we are trying to erase a Sensor from S_t with the index of an A_t sensor that has been
    randomized rendering the index given to the erase function (erasing from S_t) not the actual one that we want to
    get rid of.

    so basically we are going to have to write a function to make sure that when we delete and or add something that we have the right sensor
      something that will find the sensor out of S_t to be deleted??
*/
        remove from S_t // if no power remove
      }
      else if( !isRedundantMK3(A_t[i], A_t, S_t) ) {
        A_t.push_back(S_t[i]); //add S_t[i] to A_t
        S_t[i].setPower(S_t[i].getPower() - 1);
      }
    }

	}
}

void topDown(vector<Sensor> S) {
/*	This algorithm starts from a set of active sensors A equal to the set of
		alive sensors S_t. It iteratively picks at random a sensor s in A.
		The sensor is removed from A if it is redundant (w.r.t. the sensors in A).

 ------- Definitions ------- //
	S_t = set of sensors that are alive
	A_t = set of sensors to output for that round
	A[i].randCheck = bool inside each sensor that checks if that sensor has been
	checked n = number in A
*/
	vector<Sensor> S_t;//set of sensors that are alive
	vector<Sensor> A_t;//set of sensors to output for that round
	S_t = S; //start off with a full set

	while(S_t.size() != 0){
		A_t = S_t; //copy constructor S_t with A_t??

		random_shuffle(A_t.begin(), A_t.end());//puts sensors in a random order

//???  Should this be S_t.size()  ????
		int z = S.size();

		for(int i = 0; i < z; i++) {
			if(A_t[i].getPower() == 0){  //if no power
				for(int j = 0; j < z; j++){
					if( isEqual(A_t[i], S_t[j]) ){

//????? this won't work because we are trying to erase a Sensor from S_t with the index of an A_t sensor that has been
//????? randomized rendering the index given to the erase function not the actual one that we want to get rid of.
						S_t.erase(S_t.begin() + j);// remove A[i] from S_t
					}
				}

			}
			else {
				if( isRedundantMK3(A_t[i], A_t, S_t) )
//?????? I don't understand what's going on here
          z = S.size();
					//remove from A_t
        else
				  A_t[i].setPower(A_t[i].getPower() - 1);
			}
		}
	}
}

bool isEqual(Sensor first, Sensor second) {
  if(first.getX() == second.getX() && first.getY() == second.getY() && first.getPower() == second.getPower())
    return true;
  else
    return false;
}
//end
