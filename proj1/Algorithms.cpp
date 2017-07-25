//
// Created by Nathan Welch on 7/22/2017.
//
#include "Algorithms.h"
#include "Point.h"



void allActive(vector<Sensor> St, int totalCoverage) {
  cout << "----" << endl; //marker for file read later on

  int round = 0;
  int totalResEnergy = 0;  //total residual energy
  vector<Sensor> activeSensors = St;

  while(activeSensors.size() > 0) { //while there are active sensors
    for(int i = 0; i < activeSensors.size(); i++) { //look at each of the sensors
      if(activeSensors[i].getEnergy() != 0) { //means sensor has power so take away one unit
        activeSensors[i].setEnergy(activeSensors[i].getEnergy() - 1);
      }
      if( activeSensors[i].getEnergy() == 0) { //if no power take out of set of alive sensors
        activeSensors.erase(activeSensors.begin()+ i);
        i--;  //because size decreased
      }
    } //end for

    totalResEnergy = calcEnergy(activeSensors);  //finds the total residual energy of the set of input sensors
    round++;
    output(round, activeSensors, activeSensors, totalResEnergy, totalCoverage);
  } //end while

  return;
}

void bottonUp(vector<Sensor> St, int totalCoverage) {
  cout << "----" << endl; //marker for file read later on

  int round = 0;
  int totalResEnergy = 0;  //total residual energy
  vector<Sensor> activeSensors, aliveSensors;
  aliveSensors = St;


  //activeSensors starts empty at each iteration and sensors are added into it after meeting required criteria
  while(aliveSensors.size() > 0) {
    activeSensors.clear();  //clears out activeSensors to start clean every time
    random_shuffle(aliveSensors.begin(), aliveSensors.end());      //random sort St sensors to make iterative process easier.

    for(int i = 0; i < aliveSensors.size(); i++) {
//      if( canBeAdded() ) {
//        //add sensor into activeSensors
//        //decrease power
//      }

    }


  }


}

//total sensors
//total energy
//total coverage
//for each round
  //sensors alive
  //sensors active
  //round
  //total residual energy
  //coverage at round -> use Montecarlo Approach

void output(int round, vector<Sensor> activeSensors, vector<Sensor> aliveSensors, int totalResEnergy, int totalCoverage) {
  cout << "Round: " << round <<
       "  % Alive: " << float(aliveSensors.size()/NUM_SENSORS)*100 <<
       "  % Active:  " << float(activeSensors.size()/NUM_SENSORS)*100;
  if(aliveSensors.size() == 0)
    cout << "  AvgResEnergy: 0";
  else
    cout << "  AvgResEnergy: " << float(totalResEnergy/activeSensors.size());
  cout << "  % Coverage: " << float(coverage(activeSensors)/totalCoverage)*100 << endl;
}

void printVect(vector<Sensor> S) {
  for(int i = 0; i < S.size(); i++)
    cout << i << ": (" << S[i].getX() << "," << S[i].getY() << ") -> " << S[i].getEnergy() << endl;
}

vector<Point> calcIP(vector<Sensor> sensorVect) {

  vector<Point> pointVect;
  double x1, x2;
  double y1, y2;
  double dx, dy, d;
  double x, y;
  Point s1, s2;

  //looks at the distance between each of the sensors. If they are within 2R of each other, the IP is calculated and
  //added into a vector of Points.
  for(int i = 0; i < sensorVect.size(); i++) {
    for(int j = i; j < sensorVect.size(); j++) {

      if(distBet(sensorVect[i], sensorVect[j]) == 10 && !sensorVect[i].getStatus() && i != j) {
        //there is only exactly one point where the circles intersect
        x1 = sensorVect[i].getX(), x2 = sensorVect[j].getX();
        y1 = sensorVect[i].getY(), y2 = sensorVect[j].getY();
        dx = x2 - x1;
        dy = y2 - y1;
        d = sqrt( dx*dx + dy*dy );
        x = (d*d) / (2*d);   //this line only works because the radius of the sensors are equal
        y = sqrt(RADIUS*RADIUS - x*x);
        dx /= d;
        dy /= d;

        s1.setCoord(x1+dx*x-dy*y, x1+dy*x+dx*y);
        pointVect.emplace_back(s1);
      }

      if(distBet(sensorVect[i], sensorVect[j]) < 2*RADIUS && !sensorVect[i].getStatus() && i != j) {  // IP in radius of s
        //calculates intersection point between two sensors
        x1 = sensorVect[i].getX(), x2 = sensorVect[j].getX();
        y1 = sensorVect[i].getY(), y2 = sensorVect[j].getY();
        dx = x2 - x1;
        dy = y2 - y1;
        d = sqrt( dx*dx + dy*dy );
        x = (d*d) / (2*d);   //this line only works because the radius of the sensors are equal
        y = sqrt(RADIUS*RADIUS - x*x);
        dx /= d;
        dy /= d;
        s1.setCoord(x1+dx*x-dy*y, y1+dy*x+dx*y);
        s2.setCoord(x1+dx*x+dy*y, y1+dy*x-dx*y);

        //add points into vector
        pointVect.emplace_back(s1);
        pointVect.emplace_back(s2);
      }
    } //second for loop
    sensorVect[i].setSensor(true);
  } //first for loop
  return pointVect;
}

double distBet(Sensor cur, Sensor prev) {
  double x = (cur.getX() - prev.getX());
  double y = (cur.getY() - prev.getY());
  return sqrt(x*x + y*y);
}

int calcEnergy(vector<Sensor> active) {
  int energy = 0;
  for(int i = 0; i < active.size(); i++) {
    energy += active[i].getEnergy();
  }
  return energy;
}

int coverage(vector<Sensor> active) {
  //coverage function (coverage provided by sensors in 'At')
  //use Montecarlo Approach when actually building
  //calculates the coverage of 'St' and 'At' at each iteration comparing the two

  int coverage;
  coverage = 2;
  return coverage;
}
