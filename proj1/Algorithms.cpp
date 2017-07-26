//
// Created by Nathan Welch on 7/22/2017.
//
#include "Algorithms.h"
#include "Point.h"

//total sensors
//total energy
//total coverage
//for each round
//sensors alive
//sensors active
//round
//total residual energy
//coverage at round -> use Montecarlo Approach


void allActive(vector<Sensor> S, int totalCoverage) {
  cout << "----" << endl; //marker for file read later on

  int round = 0;
  int totalResEnergy = 0;  //total residual energy
  vector<Sensor> activeSensors = S;

  while(!activeSensors.empty()) { //while there are active sensors
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
}

void bottomUp(vector<Sensor> S, vector<Point> temp,int totalCoverage) {
  cout << "----" << endl; //marker for file read later on

  int round = 0;
  int totalResEnergy;  //total residual energy
  vector<Sensor> activeSensors, aliveSensors;
  vector<Point> pointVect;
  random_device rd;
  mt19937 g(rd());
  aliveSensors.operator=(S);
  pointVect.operator=(temp);

  activeSensors = {}; //starts empty, sensors added in

  //activeSensors starts empty at each iteration and sensors are added into it after meeting required criteria
  while(!aliveSensors.empty()) {
    totalResEnergy = 0;  //total residual energy
    round++;
    activeSensors.clear();  //clears out activeSensors to start clean every time
    for(int i = 0; i < pointVect.size(); i++) {
      pointVect[i].setCovered(false);
    }

    shuffle(aliveSensors.begin(), aliveSensors.end(), g);      //random sort St sensors to make iterative process easier.

    for(int i = 0; i < aliveSensors.size(); i++) {  //select "random" sensor to check
      for(int j = 0; j < pointVect.size(); j++) {

        //if 'alive' covers a point (that hasn't been covered yet) then add it to active sensors
        if((!pointVect[j].getCovered()) && distBetSP(aliveSensors[i], pointVect[j]) <= RADIUS) {
          //if the point is inside the radius and has not been looked at yet
          pointVect[j].setCovered(true);  //set the point to has been checked

          //see if the sensor has been added. If not, add it.
          if(!aliveSensors[i].getActive()) {
            aliveSensors[i].setActive(true);  //set sensor to be active
            activeSensors.emplace_back(aliveSensors[i]);  //add the live sensor to the set of active sensors
          }
        } //not covered, don't add
      } //end for alive
    } //end for point

    //if alive sensors have no energy, take off list
    for(int i = 0; i < aliveSensors.size(); i++) {
      if(aliveSensors[i].getActive()) {  //takes one energy away from all the active sensors
        aliveSensors[i].setEnergy(aliveSensors[i].getEnergy() - 1);
      }
      if(aliveSensors[i].getEnergy() == 0) {  //if a sensor has no energy it is removed
        aliveSensors.erase(aliveSensors.begin() + i);
      }
      totalResEnergy += aliveSensors[i].getEnergy();

    }

    //output data to be collected later
    output(round, activeSensors, aliveSensors, totalResEnergy, totalCoverage);

    //reset active sensors in alive vector
    for(int i = 0; i < aliveSensors.size(); i++) {
      aliveSensors[i].setActive(false);
    }

    } //end while !alive

}

void topDown(vector<Sensor> S, vector<Point> temp, int totalCoverage) {
  cout << "----" << endl; //marker for file read later on

  int round = 0;
  int totalResEnergy;  //total residual energy
  vector<Sensor> activeSensors, aliveSensors;
  vector<Point> pointVect;
  random_device rd;
  mt19937 g(rd());
  aliveSensors.operator=(S);
  pointVect.operator=(temp);


  while(!aliveSensors.empty()) {
    round++;
    activeSensors.operator=(aliveSensors); //starts full, then get deleted from

    shuffle(aliveSensors.begin(), aliveSensors.end(), g); //random sort aliveSensors sensors to make random iterative process easier.

    for(int i = 0; i < pointVect.size(); i++) { //resets covered values of the points
      pointVect[i].setCovered(false);
    }

    for(int i = 0; i < aliveSensors.size(); i++) {  //select "random" sensor to check
      for(int j = 0; j < pointVect.size(); j++) {

        //instead of checking if points are covered, we need to see if there are any points that aren't

        //look at the firstSensor
          //if all the points inside firstSensor radius are covered by another sensor
            //take out firstSensor
        //repeat


        //for sensors_i
          //for sensors_j
            //for points
              //are all points in sensor_i covered by sensors_j
                //"setCover" points in sensor_i
                //remove sensor_i from activeSensors




        } //not covered, don't add
      } //end for alive
    } //end for point




  }

}

void output(int round, vector<Sensor> activeSensors, vector<Sensor> aliveSensors, int totalResEnergy, int totalCoverage) {
  cout << "Round: " << round <<
       "  Alive: " << aliveSensors.size()/NUM_SENSORS*100 << "%" <<
       "  Active:  " << activeSensors.size()/NUM_SENSORS*100 << "%";
  if(aliveSensors.empty())
    cout << "  AvgResEnergy: 0";
  else
    cout << "  AvgResEnergy: " << float(totalResEnergy)/aliveSensors.size();
  cout << "  Coverage: " << float(coverage(activeSensors))/totalCoverage*100 << "%   ";
  cout << aliveSensors.size() << endl;

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

      if(distBet(sensorVect[i], sensorVect[j]) == 10 && !sensorVect[i].getActive() && i != j) {
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

      if(distBet(sensorVect[i], sensorVect[j]) < 2*RADIUS && !sensorVect[i].getActive() && i != j) {  // IP in radius of s
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
    sensorVect[i].setActive(true);
  } //first for loop
  return pointVect;
}

double distBet(Sensor cur, Sensor prev) {
  double x = (cur.getX() - prev.getX());
  double y = (cur.getY() - prev.getY());
  return sqrt(x*x + y*y);
}

double distBetSP(Sensor alive, Point point) {
  double x = (alive.getX() - point.getX());
  double y = (alive.getY() - point.getY());
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
  //calculates the coverage of 'St' and 'At' at each iteration comparing the two

  //use Montecarlo Approach when actually building
  int coverage;
  coverage = 2;
  return coverage;
}
