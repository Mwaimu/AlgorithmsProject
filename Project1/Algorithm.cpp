#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>

#include <algorithm>  //random shuffle

#include "Sensor.h"
#include "Algorithm.h"

using namespace std;




int main() {
  srand(time(NULL));

// ------- variable declarations ------- //
  int numSensors;
  vector<Sensor> S; //initialize empty vector

//	cout << "enter number of nodes to generate:  ";
//	cin >> numSensors;
//
//	//makes "numSensors" Sensors and puts them into a vector
//	for(int i = 0; i < numSensors; i++) {
//		Sensor newSensor;
//		S.push_back(newSensor);
//	}

	Sensor newSensor(1,2);
	S.push_back(newSensor);
	Sensor s1(1,7);
	S.push_back(s1);
	Sensor s2(1,18);
	S.push_back(s2);
	Sensor s3(5,2);
	S.push_back(s3);
	Sensor s4(12,3);
	S.push_back(s4);

//  cout << "Greedy Solution" << endl;
//  greedySolution(S);
//
//	cout << "All Active" << endl;
//	allActive(S);
//
//	cout << "Bottom Up" << endl;
//	bottomUp(S);

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
		A_t = set of sensors returned by algorithm at round t /active sensors
		S_t = set of sensors alive at round t
		/* 	so we have to come up with an algorithm that for each iteration will
		 		output a subset of A that has the same coverage as all of the alive
				sensors also have to keep track of the number of rounds this lasts
		**
*/
  vector<Sensor> S_t;  //set of sensors alive at round t
  vector<Sensor> A_t;  //set of sensors returned by algorithm at round t
  S_t = S;	//all sensors are alive in the beginning

  //print vector function
  printVect(S);

  int rounds = 0;
  while(S_t.size() != 0) {
    rounds++;
    cout << " Round: " << rounds << endl;
    A_t.clear();  //solution set for each iteration output every round, gets deleted so new elements can be added
    for(int i = 0; i < S_t.size(); i++) {
      if (S_t.size() == 1 ){
        A_t.push_back(S_t[i]);  //add S_t[i] to A_t
        S_t[i].setPower(S_t[i].getPower() - 1);
      }
      else if( !isRedundantMK3(S_t[i], A_t, S_t) ) { //if not redundant add to solution
        A_t.push_back(S_t[i]);  //add S_t[i] to A_t
        S_t[i].setPower(S_t[i].getPower() - 1);
      }
      else {
      }
      if(S_t[i].getPower() == 0 )	{ //only gets taken out of S_t if power is depleted
        cout << "segfault    i:" << i << "  round: " << rounds << endl;
        S_t.erase(S_t.begin() + i );  //take S_t[i] out of S_t
        i--; //makes sure no sensors are skipped when taking a sensor out
      }
    }
    printVect(S_t);
  }
}

bool isRedundantMK3(Sensor s, vector<Sensor>& A_t, vector<Sensor>& S_t){
//Has to have at least 2 sensors in A_t
/* ------- Definitions ------- //
	IP = intersection Point
	q = sensors in A_t
  A_t = set of non-redundant sensors (to be output)/active sensors
	s = current sensor looking at from S_t
  qSensors = sensors within 2R of s
*/
  if(S_t.size() == 1 ) {
    return false;
  }
  int twoR = 2 * R;
  vector<Sensor> qSensors;
  vector<Sensor> ipTest;
  qSensors.clear();
  //keep track of sensors that are within 2R of s
  for(int i = 0; i < A_t.size(); i++) {
    if(distBet(A_t[i], s) < twoR) {
      qSensors.push_back(A_t[i]);  //put A_t[i] in qSensors
    }
  }
  /*has to be at least 2 sensors for s to be redundant.
   *if there's only one, there aren't any to cover IPs
   */
  if(qSensors.size() < 2) {
    qSensors.clear();
    ipTest.clear();
    return false; // is needed
  }
  //for each qSensor...
  for(int i = 0; i < qSensors.size() - 1; i++) {
    for(int j = i; j < qSensors.size(); j++) {
      if(i == j) {
      }
      //if the distBet is < 2R 2 IPs are created
      else if(distBet( qSensors[i], qSensors[j] ) < twoR) {
        double x1 = qSensors[i].getX(), x2 = qSensors[j].getX();
        double y1 = qSensors[i].getY(), y2 = qSensors[j].getY();
        double dx = x2 - x1;
        double dy = y2 - y1;
        double d = sqrt( dx*dx + dy*dy );
        double x = (d*d - R*R + R*R) / (2*d);
        double y = sqrt(R*R - x*x);
        dx /= d;
        dy /= d;
        Sensor s1(x1+dx*x-dy*y, y1+dy*x+dx*y);
        Sensor s2(x1+dx*x+dy*y, y1+dy*x-dx*y);
        if(distBet(s1, s) < R) {  // IP in radius of s
          ipTest.push_back(s1);  //put IP in testArray
        }
        if(distBet(s2, s) < R) {
          ipTest.push_back(s2);  //put IP in testArray
        }
      }
    }
  }
  for(int i = 0; i < ipTest.size(); i++) { //for each IP point -> i
    int count = 0; //resets count
    for (int j = 0; j < A_t.size(); j++) { //for each IP look at all the sensors that are needed, if the distance between the IP and a sensor that's alive is < R
      if( distBet( A_t[j], ipTest[i] ) < R  ) //means s is still redundant because some sensor A[j] is covering IP
        count++;
    } //for each q
    if(count == 0)  //means IP NEVER covered
      return false; //means needed -> b/c there's one point never covered
  } //for each IP
  return true; //got all the way through all points being covered -> redundant
}

//finds the distance between two points
double distBet(Sensor cur, Sensor prev) {
  double x = (cur.getX() - prev.getX());
  double y = (cur.getY() - prev.getY());
  return sqrt(x*x + y*y);
}

//OTHER APPROACHES:

//1
void allActive(vector<Sensor> S) { //for (each round t) decrement energy when tested for duration
  vector<Sensor> A_t = S;//the solution is all sensors in A
  int round = 0;
  while(A_t.size() != 0) {
    round++;
    cout << "Round: " << round << endl;
    for(int i = 0; i < A_t.size(); i++){
      //for all elements in A_t
      if(A_t[i].getPower() != 0) //if still power
        A_t[i].setPower(A_t[i].getPower() - 1); //decrease power
      if(A_t[i].getPower() == 0) {
        //remove from A_t
        A_t.erase(A_t.begin() + i);  //take S_t[i] out of S_t
        i--;
      }
    }
    printVect(A_t);
  }
  return;
}

//2
void bottomUp(vector<Sensor> S) {
/*Random-bottom-up: This algorithm starts from an empty set of active sensors A.
It iteratively selects a sensor s among those that are alive to be added to A.
The sensor s is added to A only if the sensor covers some intersection points
that are currently not covered by the sensor in A.
*/
  int round = 0;
  vector<Sensor> S_t = S;
  vector<Sensor> A_t;
  while (S_t.size() != 0) // while there are live sensors
  {
    round++;
    cout << "Round: " << round << endl;
    A_t.clear();  //solution set for each iteration to be output for every round, gets deleted so new elements can be added into it
    random_shuffle(S_t.begin(), S_t.end());//puts sensors in a random order
    for (int i = 0; i < S_t.size(); i++){
      if( S_t[i].getPower() == 0) {
        cout << "No Power" << endl;
        S_t.erase(S_t.begin() + i);  //remove from S_t, no power
      }
      else if( !isRedundantMK3(S_t[i], A_t, S_t) ) {
        A_t.push_back(S_t[i]); //add S_t[i] to A_t
        S_t[i].setPower(S_t[i].getPower() - 1);
//        i--;
      }
    }
    printVect(A_t);
  }
}

//void topDown(vector<Sensor> S) {
///*	This algorithm starts from a set of active sensors A equal to the set of
//		alive sensors S_t. It iteratively picks at random a sensor s in A.
//		The sensor is removed from A if it is redundant (w.r.t. the sensors in A).
//
// ------- Definitions -------
//	S_t = set of sensors that are alive
//	A_t = set of sensors to output for that round/active sensors
//	A[i].randCheck = bool inside each sensor that checks if that sensor has been
//	checked n = number in A
//*/
//  vector<Sensor> S_t;//set of sensors that are alive
//  vector<Sensor> A_t;//set of sensors to output for that round
//  S_t = S; //start off with a full set
//  int round = 0;
////  float perAlive = 0;
////  float perActive = 0;
//
//  cout << "S_t: :" << endl;
//  printVect(S_t);
//  while(S_t.size() != 0){
//    A_t = S_t; //reset A_t to everything alive
//
//
//    round++;
//    cout << "Round: " << round << endl;
//
//    random_shuffle(A_t.begin(), A_t.end());//puts sensors in a random order
//
//    for(int i = 0; i < A_t.size(); i++) {
//
//      if(A_t[i].getPower() == 0){  //if no power
//        //compare against everything in S_t to find match
//        for(int j = 0; j < S_t.size(); j++) {
//          //when match is found, delete
//          if( isEqual(A_t[i], S_t[j]) ) {
//            cout << "removed from S_t" << endl;
//            S_t.erase(S_t.begin() + j);// remove A_t[i] from S_t
//          }
//        }
//      }
//        //it has power left
//      else if( isRedundantMK3(A_t[i], A_t, S_t) ) {
//        cout << i << " is redundant" << endl;
//        //and is redundant, remove it from A_t
//        A_t.erase(A_t.begin() + i);// remove A_t[i] from A_t
//      }
//        //happens when still needed
//      else {
//        for(int j = 0; j < S_t.size(); j++) {
//          //when match is found, delete
//          if( isEqual(A_t[i], S_t[j]) ) {
//            S_t[i].setPower(S_t[i].getPower() - 1);
//          }
//        }
//        A_t[i].setPower(A_t[i].getPower() - 1); //only needed if we output the power along with each sensor
//      }
//    }
//    printVect(A_t);
//  }
////  perAlive = percentAliveSensors(S.size(), A_t.size());
////  perActive = percentActiveSensors(S.size(), S_t.size());
//  return;
//}

void topDown(vector<Sensor> S) {
  vector<Sensor> S_t;//set of sensors that are alive
  vector<Sensor> A_t;//set of sensors to output for that round
  S_t = S; //start off with a full set
  int round = 0;
  cout << "S_t: :" << endl;
  printVect(S_t);
  while(S_t.size() != 0){
    A_t = S_t; //reset A_t to everything alive
    round++;
    cout << "Round: " << round << endl;
    random_shuffle(A_t.begin(), A_t.end());//puts sensors in a random order



    for(int i = 0; i < A_t.size(); i++) {
      //if dead
      if(A_t[i].getPower() == 0) {
        //find in S_t
        for(int j = 0; j < S_t.size(); j ++) {
          //when found match, delete
          if( isEqual(A_t[i], S_t[j])) {
            cout << "removed from S_t" << endl;
            S_t.erase(S_t.begin() + j);// remove A_t[i] from S_t
          }
        }
      }
      // means has power
      else {
        //if it's needed
        if( !isRedundantMK3(A_t[i], A_t, S_t) ) {
          cout << i << ": (" << S[i].getX() << "," << S[i].getY() << ") -> "  ": " << " is redundant" << endl;

        }


        //it's redundant
        else {
          cout << i << ": (" << S[i].getX() << "," << S[i].getY() << ") -> "  ": " << " is redundant" << endl;



        }
      }
    }




    printVect(A_t);
  }
  return;
}






bool isEqual(Sensor first, Sensor second) {
  if(first.getX() == second.getX() && first.getY() == second.getY() && first.getPower() == second.getPower())
    return true;
  else
    return false;
}

/*------------------------------------------------------------------------------
	Function Description: This function accepts a vector of active sensors and the number
    	     		        of randomly distributed test points you'd like to generate.
        	       		  It returns the percentage of the point that are covered by the
            	  		  given active sensor field
------------------------------------------------------------------------------*/

float percentCoverageActiveSensors(vector<Sensor>& active_sensors, const int numTestPoints){
  vector<Sensor> test_points;
  vector<Sensor>::iterator iter;
  float percent_coverage=0;
  int numTestPointsCovered=0;

  //--Create a field of test sensors (test points)
  while(test_points.size() <= numTestPoints){
    Sensor t;
    test_points.push_back(t);
  }

  //--Two loops to test each test sensor to see if it is covered. If it is,
  //--break from the inner loop and try the next test sensor.
  for(iter = test_points.begin(); iter != test_points.end(); iter++){
    for(int k = 0; k < active_sensors.size(); k++){
      if(distBet(*iter, active_sensors[k]) <= R){
        numTestPointsCovered++;
        break;
      }
    }
  }

  percent_coverage = static_cast<float>(numTestPointsCovered) / static_cast<float>(numTestPoints);
  return percent_coverage;
}

float avgResidualEnergy(vector<Sensor>& S_t){
  float total_power=0, avg_power=0;
  vector<Sensor>::iterator iter;
  for(iter = S_t.begin(); iter != S_t.end(); iter++){
    total_power += iter->getPower();
  }
  avg_power = total_power / S_t.size();
  return avg_power;
}

float percentActiveSensors(const int S, const int A_t){
  float percent_active = ( (A_t / S)*100);
  return percent_active;
}

float percentAliveSensors(const int S, const int S_t){
  float percent_alive = ( (S_t / S )*100);
  return percent_alive;
}

void printVect(vector<Sensor>& S) {
  for(int i = 0; i < S.size(); i++)
    cout << i << ": (" << S[i].getX() << "," << S[i].getY() << ") -> " << S[i].getPower() << endl;
}
