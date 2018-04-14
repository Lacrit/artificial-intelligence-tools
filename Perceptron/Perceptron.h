#include <iostream> 

class Perceptron
{
	public: 
		Perceptron(int num_of_coords, double alpha);
		~Perceptron();
		bool output(double* inputs) ;
		void updateWeightsnThreshold(double* inputs, bool d, bool y); 

		int num_of_coords;
		double* weights;
		double threshold;
		double alpha;

};
