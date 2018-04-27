#include <iostream> 
#include <vector> 
#include "Perceptron.h"

class Layer  
{
	std::vector<Perceptron> perceptrons;
	int num_of_langs;
	int num_of_inputs;

public: 
	Layer(int num_of_langs, int num_of_inputs, double alpha);
	int get_largest_perc_output(double * inputs); 
	double train(double * inputs, double y); // y - correct output

};
