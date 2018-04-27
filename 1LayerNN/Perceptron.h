#include <iostream> 
#include <vector>

class Perceptron
{
		int num_of_coords;
		std::vector<double> weights;
		double threshold;
		double alpha;

	public: 
		Perceptron(int num_of_coords, double alpha);
		double output(double* inputs) ;
		void updateWeightsnThreshold(double* inputs, double d, double y);
		void normalize_weights(); 

};
