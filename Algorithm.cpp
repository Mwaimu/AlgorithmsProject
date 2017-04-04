#include <iostream>
using namespace std;

//------- Global Variables -------//
const int R = 5; //sensor radius

int main() {

	return 0;
}

greedySolution( S ) {  //will return A_t
// ------- Definitions ------- //
/*	s / A[i] = spcific sensor
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

	S_t = S; //all sensors are alive in the beginning
	rounds = 0;
	while there are live sensors {
		rounds++;
		A_t = null;//solution set for each iteration, output for every round
		for (all sensors that are in S_t) {
			if(S_t[i].energy == 0 ) //only gets taken out of S_t if power is depleted
				take S_t[i] out of S_t

			else if (S_t.size == 1 ){
				add S_t[i] to A_t
				S_t[i].power--
			}

			else( !isRedundantMK3() )  //if not redundant add to solution
				add S_t[i] to A_t
				S_t[i].power-- //subtract power

			//else is redundant, don't add to A_t, basically skip to the next sensor
		}
	}
}

bool isRedundantMK3(s, A_t){
//Has to have at least 2 sensors in A_t
/* ------- Definitions ------- //
	IP = intersection Point
	q = sensors in A_t
  A_t = set of non-redundant sensors (to be output)
	s = current sensor looking at from S_t
*/

	for( all sensors in A_t) {
		if( distBet(A_t[i], s) < 2R) //if q is in range of s
			put A_t[i] in QsensorsArray	//put sensor in array
	}

	for( i = 0 -> QsensorsArray.size-2) {
		for( j = i+1 ) {
			if(i == j)
				//skip, because same sensor
			else if(distBet( Q[i], Q[j] ) < 2R) {
				makes IP
					//find location using Q[i] & distance tracker from wateringgrass prob
				if( IP in radius of s)
					put IP in testArray  //array to be thrown into rest of redundancy
			}
		}
	}

	for( each IP point in testArray ) {
		count = 0; //resets count
		for ( each q ) { //for each sensor in A_t
			if( distBet( q, IP ) < R  )//means IP still redundant
			 	count++;
		} //for each q
		if( count == 0)  //means IP NEVER covered
			return false; //means needed -> b/c there's one point never covered
	} //for each IP
	return true; //got all the way through all points being covered -> redundant
}

//finds the distance between two points
int distBet(sensor cur, sensor prev) {
	//might have to cast these (inside sqrt) as a float just to make sure
	//there are no rounding errors beforehand
	return absVal( sqrt( (cur.x - prev.x)^2 + (cur.y - prev.y)^2 ) );
	//this also needs to be ABSOLUTE VALUE
}


//OTHER APPROACHES:

//1
allActive(S){ //for (each round t) decrement energy when tested for duration
	A_t = S;//the solution is all sensors in A
	round = 0;
	for (all the sensors in A)
		A_t[i].power--
		round++
	return A_t;
}

//2
bottomUp(S){
/*Random-bottom-up: This algorithm starts from an empty set of active sensors A.
It iteratively selects a sensor s among those that are alive to be added to A.
The sensor s is added to A only if the sensor covers some intersection points
that are currently not covered by the sensor in A.
*/

	S_t = S;
	while (S_t != NULL) // while there are live sensors
	{
		A = NULL
		arrRand[n] = random[0 -> n-1] //array of random numberes 0-n-1 all included

		for (i = each item in S_t)
			j = arrRand[i] // j = rand num @ iteration i of arrRand
		if (if S_t[j].power == 0)
			remove from S_t // if no power remove
		else if (S_t.size == 1 ){
			add S_t[i] to A_t
			S_t[i].power--
		}
		else
			if (S_t !isRedundantMK3){
				S_t.power--
				A = A (union) S_t[i]
			}
	}
}

//3
topDown(S) {
/*	This algorithm starts from a set of active sensors A equal to the set of
		alive sensors S_t. It iteratively picks at random a sensor s in A.
		The sensor is removed from A if it is redundant (w.r.t. the sensors in A).

 ------- Definitions ------- //
	S_t = set of sensors that are alive
	A = set of sensors to output for that round
	A[i].randCheck = bool inside each sensor that checks if that sensor has been
	checked n = number in A
*/
	S_t = S //start off with a full set
	while( S_t is not null ) {
		A = S_t  //copy constructor probably
		//creates an array that has all numbers 0 through n-1 in random order
		arrRand[n] = random[0 -> n];

		for(i = each item in A) {
			j = arrRand[i];	//makes j the random number in the Ith location of arrj
			if(A[j].power == 0)  //if no power, remove A[j] from S_t
				remove A[j] from S_t;
			else {
				if(A[j] is redundant)
					remove from A
				else
					A[j].power--;
			}
		}
	}
}
//end
