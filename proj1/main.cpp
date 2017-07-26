// Nathan Welch
// Algorithms 2500 MST Spring 2017
// Project 1
/* Description: Greedy Algorithm for Selective Activation in Wireless Sensor Networks
 *    'S' sensors are randomly deployed in Area of Interest. Each sensor has position(x, y), and energy level(e) which
 *    is initially set at 300 for each sensor. Each sensor has a sensing radius(R) and covers a disk or radius R
 *    centered at the sensor. Number of deployed sensors is 'N'
 *
 *    The set of alive sensors is determined periodically, at each round(t) by executing a selective algorithm that
 *    returns a set(At). Let 'St' be the set of sensors that are alive at round t, for each sensor 'S' in 'St' e > 0.
 *    The set 'At' returned by the algorithm is a subset of 'St' that includes all live sensors. Let Cov(At) be the
 *    coverage provided by the sensors in 'At', which is the union of sensing ranges of all sensors in 'At'. The
 *    algorithm must return a set 'At' such that it provides the same coverage as 'St' -> Cov(At) = Cov(St).
 *
 *    An active sensor consumes one unit of energy per each round. We say a sensor is alive at round 't' if its residual
 *    energy is greater than 0. We say a sensor is active at round 't' if the selective algorithm decides to keep it
 *    active (has been chosen by the algorithm). An active sensor has to be alive.
 *
 *
 *
 */

#include "Algorithms.h"

using namespace std;

int main() {
  srand(time(NULL));

  int totalCoverage = 0;
  vector<Point> pointVect;

  vector<Sensor> S, St;
//  for(int i = 0; i < NUM_SENSORS; i++) {
//    S.push_back(Sensor(i, i));
//  }

  int randX;
  int randY;
  for(int i = 0; i < NUM_SENSORS; i++) {
    randX = rand() % 14;
    randY = rand() % 14;
    S.emplace_back(Sensor(randX, randY));
  }

  St = S;

//  cout << "Size of St: " << St.size() << "  energy: " << ENERGY_START << endl;

  //figure out the coverage and IPs of original set S
  totalCoverage = coverage(S);
  //calculates the IP's of the given sensors
  pointVect = calcIP(St);

//  cout << "All Active   ";
//  allActive(S, totalCoverage);
//  cout << "Bottom Up    ";
//  bottomUp(S, pointVect, totalCoverage);

  cout << "Top Down     ";
  topDown(S, pointVect, totalCoverage);


  return 0;
}


