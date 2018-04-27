#include <iostream> 
#include "Layer.h"
#include <vector> 

Layer::Layer(int num_of_langs, int num_of_inputs, double alpha):
	num_of_langs(num_of_langs),
	num_of_inputs(num_of_inputs)
{
	for (int i = 0; i < num_of_langs; i++) 
		perceptrons.push_back(Perceptron(num_of_inputs, alpha));
}

int Layer::get_largest_perc_output(double * inputs)  
{
	int largest_ind = 0; 
	double  largest_val = 0; 

	for (int i = 0; i < num_of_langs; i++) 
	{
		double value = perceptrons.at(i).output(inputs);
		if ( value >= largest_val ) 
		{
			largest_val = value; 
			largest_ind = i; 
		}

	}
	return largest_ind;
	// shouldn't this return an int not double?
}

double Layer::train(double * inputs, double y) 
{
	//1/2(sum(d-y)^2)
	double error_rate = 0;
		for ( int i = 0; i < num_of_langs; i++) 
		{
			double d = (double)(i == y);
			double actual  = perceptrons.at(i).output(inputs);
			perceptrons.at(i).updateWeightsnThreshold(inputs, d, actual);
			error_rate += (d-actual) * (d-actual);

		}
		
	return error_rate/2;
}
