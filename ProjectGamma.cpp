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
	void mutate();
	void calc_distance(vector<city> cc);
};

class Agent {
public:
	double ax_start;
	double ay_start;
	double ax; //does the agent start at a city or at a random location?
	double ay;

	void init(double city_x, double city_y);
	void restart();
};



void city::init() {
	cx = BMMRAND;
	cx = cx * 100; //city x location in a 100x100 grid
	///cout << cx << ", ";
	cy = BMMRAND;
	cy = cy * 100; //city y location in a 100x100 grid
	///cout << cy << endl;

				   //make sure there are no cities out of bounds
	assert(cx <= 100);
	assert(cy <= 100);
}

void policy::init(int n_city) {
	vector<int> dummy;
	int n;
	//Create order from 0 to n_city
	for (int i = 1; i < n_city; i++) {
		dummy.push_back(i);
	}
	//assert(order.size() == n_city);
	//swap vector instances to get random order n_city number of times without duplicating cities
	for (int i = 0; i < n_city; i++) {
		if (i == 0) {
			order.push_back(0);
		}
		else {
			n = rand() % dummy.size();
			order.push_back(dummy[n]);
			dummy.erase(dummy.begin() + n);
		}

	}
	assert(order[0] == 0);
	assert(order.size() == n_city);

	///Cout order for Dubgging
	/* << "Order:";
	for (int i=0; i < n_city; i++)
	{
	cout << order[i] << "\t";
	}
	cout << endl;
	*/
}

/*
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
	/* << "Order:";
	for (int i=0; i < n_city; i++)
	{
		cout << order[i] << "\t";
	}
	cout << endl;
	/
}
*/

void policy::mutate() {
	int num_swap = 5;
	int rand1 = 0;
	int rand2 = 0;
	int temporary = 0;
	for (int i = 0; i < num_swap; i++) {
		rand1 = rand() % order.size();
		rand2 = rand() % order.size();
		//The first city always has to be 0
		while (rand1 == 0) { rand1 = rand() % order.size(); }
		while (rand2 == 0 || rand1 == rand2) { rand2 = rand() % order.size(); }
		//swap around the other cities
		///cout << "\t" << order[rand1] << ", " << order[rand2] << endl;
		temporary = order[rand1];
		order[rand1] = order[rand2];
		order[rand2] = temporary;
		///cout << "\t" << order[rand1] << ", " << order[rand2] << endl;
	}
	assert(order[0] == 0);
}

void policy::calc_distance(vector<city> cc) {
	//fitness = total distance to travel through all the cities
	double dummy = 0;
	assert(cc.size() == order.size());
	fitness = 0;
	for (int i = 0; i < cc.size() - 1; i++) {
		///printf("1: %d, %d\n2: %d, %d", cc[order[i]].cx, cc[order[i]].cy, cc[order[i + 1]].cx, cc[order[i + 1]].cy);
		dummy = sqrt(pow(cc[order[i + 1]].cx - cc[order[i]].cx,2)  + pow(cc[order[i + 1]].cy - cc[order[i]].cy,2));
		///cout << '\t' << dummy << endl;
		fitness += dummy;
	}
	///cout << "Fitness:" << fitness << endl;
}

void Agent::init(double city_x, double city_y) {
	ax_start = city_x;
	ay_start = city_y;
	///cout <<"city:" << city_x << "," << city_y << endl;
	///cout <<"agent:"<< ax_start << "," << ay_start << endl;
}

void Agent::restart() {
	ax = ax_start; //might be unnecessary...re-evaluate later
	ay = ay_start;
}

vector<policy> EA_replicate(vector<policy> pp,int num_poly,int n_city) {
	policy temp;
	int spot = 0;
	int n = pp.size();

	//cout << n << endl;

	while (pp.size() < num_poly) {
		spot = rand() % n;
		temp = pp.at(spot);
		temp.mutate();
		///Cout original and mutated policies for debugging
		/*
		cout << "Original:";
		for (int i = 0; i < n_city; i++) {
			cout << "\t" << pp[spot].order[i];
		}
		cout << endl;

		cout << "Mutate:";
		for (int i = 0; i < n_city; i++) {
			cout << "\t" << temp.order[i];
		}
		cout << endl;
		//*/

		pp.push_back(temp);
	}
	assert(pp.size() == num_poly);
	return pp;
}

vector<policy> EA_evaluate(vector<policy> pp,vector<city> cc) {
	//fitness = total distance to travel through all the cities
	for (int j = 0; j < pp.size(); j++) {
		pp.at(j).calc_distance(cc);
	}
	return pp;
}

vector<policy> EA_downselect(vector<policy> pp,int size) {
	vector<policy> winners;
	int spot1 = 0;
	int spot2 = 0;
	///int counter = 0;
	///cout << "size=" << size << endl;
	while (winners.size() < size) {
		spot1 = rand() % size;
		spot2 = rand() % size;
		///cout << "spot1before=" << spot1 << endl;
		///cout << "spot2before=" << spot2 << endl;
		while (spot1 == spot2) { spot1 = rand() % size;}
		///cout << "spot1 " << spot1 << "\t spot2 " << spot2 << endl;
		if (pp[spot1].fitness <= pp[spot2].fitness) { 
			winners.push_back(pp[spot1]); 
			///cout << "Spot 1 wins\tFit1=" << pp[spot1].fitness << "\tFit2=" << pp[spot2].fitness << endl;
		}
		else if (pp[spot2].fitness <= pp[spot1].fitness) { 
			winners.push_back(pp[spot2]); 
			///cout << "Spot 2 wins\tFit1=" << pp[spot1].fitness << "\tFit2=" << pp[spot2].fitness << endl;
		}
		else {
			///cout << "no win" << "\tFit1=" << pp[spot1].fitness << "\tFit2=" << pp[spot2].fitness << endl; //this is where the problem is. The program is not finding a winner
		}
		///counter++;
	}
	///cout << "counter:" << counter << endl;
	assert(winners.size() == size);
	return winners;
}

int main() {
	srand(time(NULL));

	//Define how many cities to travel too
	int num_city = 10; //10 cities, 25 cities, 50
	vector<city> cities;
	assert(cities.size() == 0);
	
	//Create Cities
	for (int i = 0; i < num_city; i++) {
		city C;
		C.init();
		cities.push_back(C);
	}
	assert(cities.size() == num_city);

	//initialize agent at city 0 location
	Agent A;
	A.init(cities[0].cx, cities[0].cy);
	//double check agent is initialized properly
	///cout << "city2:" << cities[0].cx << "," << cities[0].cy << endl;
	assert(A.ax_start == cities[0].cx); 
	assert(A.ay_start == cities[0].cy);

	//Define number of policies
	int num_poly = 50;
	vector<policy> policies;

	//Create 50 Random Policies 
	for (int i = 0; i < num_poly; i++) {
		policy P;
		P.init(num_city);
		P.calc_distance(cities);
		policies.push_back(P);
	}

	for (int i = 0; i < num_poly; i++) {
		for (int j = 0; j < num_city; j++) {
			cout << policies[i].order[j] << ", ";
		}
		cout << "\n";
	}
	assert(policies.size() == num_poly); // make sure the correct amount of policies were created
	
	//Implement Evolutionary Algorithm
	int run = 300; //how many times to run EA
	int total_poly = num_poly * 2; //double the number of original policies
	//cout << "total_poly=" << total_poly << endl;
	for (int i = 0; i < run; i++) {
		policies = EA_replicate(policies, total_poly,num_city);
		policies = EA_evaluate(policies, cities);
		policies = EA_downselect(policies, num_poly);
		assert(policies.size() == num_poly);
	}

	/*for (int k = 0; k < num_poly; k++) {
		for (int j = 0; j < num_city; j++) {
			cout << policies[k].order[j] << ", ";
		}
		cout << "fitness=" << policies[k].fitness << "\n";
	}*/
	
	ofstream myfile;
	myfile.open("cities.csv");
	for (int i = 0; i < cities.size(); i++) {
		myfile << cities[i].cx << "," << cities[i].cy << "," << endl;
	}
	myfile.close();

	ofstream newfile;
	newfile.open("path.csv");
	for (int i = 0; i < num_city; i++) {
		newfile << policies[1].order[i] << endl;
	}
	newfile.close();
	assert(policies.size() == num_poly); //double check policy size
	return 0;
}
