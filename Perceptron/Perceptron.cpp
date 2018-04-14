#include "Perceptron.h"

Perceptron::Perceptron(int num_of_coords, double alpha):
	num_of_coords(num_of_coords),
	weights(new double[num_of_coords]),
	threshold(1),
	alpha(alpha)
{
	for (int i = 0; i < num_of_coords; i++) 
		weights[i] = 0.1;
}

Perceptron::~Perceptron() 
{
	delete[] weights; 
}

bool Perceptron::output(double *inputs) 
{
	int sum = 0.0; 
		for (int i = 0; i < num_of_coords; i++) 
			sum += weights[i] * inputs[i];
	return sum >= threshold;
}

void Perceptron::updateWeightsnThreshold(double* inputs, bool d, bool y) 
{
	for (int i = 0; i < num_of_coords; i++)
		weights[i] += (d-y) * inputs[i] * alpha;
	threshold -= (d-y) * alpha;
}
