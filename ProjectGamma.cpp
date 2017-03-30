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

	void init(int n_city);
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

void policy::init(int n_city) {
	//Create order from 0 to n_city
	for (int i = 0; i < n_city; i++) {
		order.push_back(i);
	}
	assert(order.size() == n_city);
	//swap vector instances to get random order n_city number of times without duplicating cities
	int rand1=0;
	int rand2 = 0;
	for (int i = 0; i < n_city; i++) {
		rand1 = rand() % n_city;
		rand2 = rand() % n_city;
		//The first city always has to be 0
		while (rand1 == 0){ rand1 = rand() % n_city; }
		while (rand2 == 0) { rand2 = rand() % n_city; }
		//swap around the other cities
		swap(order[rand1], order[rand2]);
	}
	assert(order[0] == 0);
	assert(order.size() == n_city);

	///Cout order for Dubgging
	/*cout << "Order:";
	for (int i=0; i < n_city; i++)
	{
		cout << order[i] << "\t";
	}
	cout << endl;
	*/
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

	//Define number of policies
	int num_poly = 50;
	vector<policy> policies;

	//Create 50 Random Policies 
	for (int i = 0; i < num_poly; i++) {
		policy P;
		P.init(num_city);
		policies.push_back(P);
	}
	assert(policies.size() == num_poly);


	return 0;
}
