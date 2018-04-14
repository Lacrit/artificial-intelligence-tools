#include <iostream>
#include <vector> 
#include <iomanip>
#include <fstream>
#include <sstream> 
#include <string>
#include "Perceptron.h"

#define NUM_OF_COOR 4

struct Case 
{
	bool classifier; 
	double inputs[NUM_OF_COOR];
};

std::vector<Case> train_data; 
std::vector<Case> test_data; 

Case parsing(std::string line){
	std::istringstream iss(line);
	std::string data;
	Case c;
	int i = 0;
	while(std::getline(iss, data, ',') && i < NUM_OF_COOR) 
		c.inputs[i++] = stod(data);
	std::getline(iss, data); 
		c.classifier = (data == "Iris-versicolor") ? 1: 0; 
	return c;	
}
	
void loadDataSet(std::string file, std::vector<Case>& v)
{
   	std::ifstream train_file(file);
	std::string line; 
	while (std::getline(train_file, line )) 
	    	v.push_back(parsing(line));
}

int main() 
{
	int k; 
	std::cout << "k: " << std::endl;
	std::cin >> k; 
	double alpha; 
	std::cout << "alpha: ";
	std::cin >> alpha;
	int all = 0, correct = 0; 
	Perceptron perc(NUM_OF_COOR, alpha);
	loadDataSet("training.txt", train_data);
		for ( int i = 0; i < k; i++ ) 
		{
		
			auto end = train_data.end(); 
			for (auto it = train_data.begin(); it != end; it++) 
			{
				bool y = perc.output(it->inputs);
				perc.updateWeightsnThreshold(it->inputs, it->classifier, y);
			}
		}

	loadDataSet("test.txt", test_data);
		auto end = test_data.end(); 
		for (auto it = test_data.begin(); it != end; it++) 
		{
				bool y = perc.output(it->inputs);
				if ( y == it->classifier ) 
					correct++; 
				all++;
				std::cout << "Identified " << y << ", Actual " << it->classifier << std::endl;
		}
				
				std::cout << "Accuracy " << ((double)correct/all)*100 << "%" << std::endl;
				return 0;
}

