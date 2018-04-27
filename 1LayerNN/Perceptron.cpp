#include  <math.h> 
#include  "Perceptron.h"

Perceptron::Perceptron(int num_of_coords, double alpha):
	num_of_coords(num_of_coords), 
	weights(std::vector<double>()),
	threshold(1),
	alpha(alpha)
{
	for (int i = 0; i < num_of_coords; i++)	
		weights.push_back(1);
	normalize_weights();
}

void Perceptron::normalize_weights()
{
	size_t size = weights.size(); 
	double length = 0; 
	for ( size_t i = 0; i < size; i++ )
		length += weights.at(i) * weights.at(i);
	length = std::sqrt(length); 
	for ( size_t i = 0; i < size; i++ ) 
		weights.at(i) /= length; 

}
//sigmoid 
double Perceptron::output(double *inputs) 
{
	double net = 0;
		for ( int i = 0; i < num_of_coords; i++ )
			net += inputs[i]*weights[i];
	return 1/(1+std::exp(-net));
}

void Perceptron::updateWeightsnThreshold(double* inputs, double d, double y) 
{
	for ( int i = 0; i < num_of_coords; i++ ) 
		weights.at(i) += alpha*(d-y)*y*(1-y)*inputs[i];
	
	normalize_weights();
	
}
