//Britny Mors
//ME 493 - Autonomy
//Project Gamma - Traveling Salesman Evolutionary Algorithm


#include <iostream>
#include <assert.h>
#include <vector>
#include <random>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <fstream>

using namespace std;

#define BMMRAND (double)rand()/RAND_MAX;

class city {
public:
	double cx;
	double cy;

	void init();
};

class policy {
public:
	double fitness;
	vector<int> order;

	void init();
	void calc_distance();
};

class Agent {
	double ax_start;
	double ay_start;
	double ax; //does the agent start at a city or at a random location?
	double ay;

	void init();
};


class Evolutionary_Alorithm {
public:
	void EA_init();
	void EA_replicate();
	void EA_evaluate();
	void EA_downselect();
};

void city::init() {
	cx = BMMRAND;
	cx = cx * 100; //city x location in a 100x100 grid
	cy = BMMRAND;
	cy = cy * 100; //city y location in a 100x100 grid

				   //make sure there are no cities out of bounds
	assert(cx <= 100);
	assert(cy <= 100);
}

void policy::init() {

}

int main() {
	srand(time(NULL));
	//Define how many cities to travel too
	int num_city = 5;
	vector<city> cities;
	//Create Cities
	for (int i = 0; i < num_city; i++) {
		city C;
		C.init();
		cities.push_back(C);
	}
	assert(cities.size() == num_city);
	//Create 50 Random Policies 



	return 0;
}
