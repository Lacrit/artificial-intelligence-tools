#include <iostream> 
#include <vector> 
#include <random> 
#include <array> 
#include <fstream>
#include <sstream>

#define NUM_OF_COORDS 4

struct Point 
{
	std::string label; 
	std::array<double, NUM_OF_COORDS> coords;
	int id;
};

typedef std::array<double, NUM_OF_COORDS> darray;
std::vector<Point> data; 
std::vector<darray> clust_vector;
std::vector<size_t> count;

double eucl_dist(darray& f, darray& s) 
{
	double res = 0;
	double tmp = 0;
	for (size_t i = 0; i< NUM_OF_COORDS; i++) 
	{
		tmp = f[i] - s[i];
		res += tmp*tmp;
	}
	return res;
}

Point parsing(std::string& line)
{
	std::istringstream iss(line);
	std::string data;
	Point p;	
	int i = 0;
	while(std::getline(iss, data, ',') && i < NUM_OF_COORDS) 
		p.coords[i++] = stod(data);
	std::getline(iss, data); 
	p.label = data;
	return p;	
}

void read_data(std::string file, std::vector<Point>& data)  
{
   	std::ifstream train_file(file);
	std::string line; 
	while (std::getline(train_file, line )) 
	    	data.push_back(parsing(line));

}

void k_means(std::vector<Point>& data, size_t k, size_t num_of_iter)
{
	//~~~~~~randomize~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	static std::random_device seed; //Will be used to obtain a seed for the random number engine
	static std::mt19937 rand_num_gen(seed()); //Standard mersenne_twister_engine seeded with seed()
	std::uniform_int_distribution<> ind(0, k-1);
	// pick random points from the dataset as the initial centroids
	for (auto it = data.begin(); it != data.end(); it++)
	{
		it->id = ind(rand_num_gen);
	}
	//~~~~~~main~loop~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	bool assigned = true;
	for (size_t iter = 0; (iter < num_of_iter) && assigned; iter++)
	{

		assigned = false;
		
		std::cout << "Iteration: " << iter << std::endl;

		//~~reset~the~data~~~~~~~~~~~~~~~~~~~~~
		clust_vector.clear();
		count.clear();
		for (size_t i = 0; i < k; i++) 
		{ 
			clust_vector.push_back(std::array<double, NUM_OF_COORDS>());
			count.push_back(0);
		}

		//~~sum~up~and~find~the~point~for~each~cluster~~~~~~~~~~~~~~~~~~~~~~~~~
		for (auto it = data.begin(); it != data.end(); it++) 
		{
			for (int i = 0; i < NUM_OF_COORDS; i++) 
				clust_vector[it->id][i] += it->coords[i];
			count[it->id]++;
		} 


		//~~divide~sums~by~counts~to~get~new~centroids~~~~~~~~~~~~~~~~~~~~~~~~~
		for (size_t cluster = 0; cluster < k; cluster++) 
		{
			for (size_t j = 0; j < NUM_OF_COORDS; j++) 
			{
			// turn 0/0 into 0/1 to avoid zero division
			count[cluster] == 0 ? count[cluster] = std::max<size_t>(1, count[cluster]) : count[cluster];
			clust_vector[cluster][j] /= count[cluster];
			}

		}


		//~~find~closest~centroid~~~~~~~~~~~~~~~~~~~~~~~
		for (auto it = data.begin(); it != data.end(); it++) 
		{
			int old_id = it->id;
			double best_dist = std::numeric_limits<double>::max(); 
			double best_cluster = 0;
			for (size_t cluster = 0; cluster < k; cluster++) 
			{
				const double dist = eucl_dist(it->coords, clust_vector[cluster]);
				if (dist < best_dist) 
				{
					best_dist = dist; 
					best_cluster = cluster; 
				}
			}
			it->id = best_cluster;
			if (old_id != it->id )
			{
				assigned = true;
std::cout << old_id << " -> " << it->id << std::endl;
			}
		}
	}
}

int main() 
{
	size_t k, n;
	read_data("test.txt", data);
	std::cout << "Enter number of clusters k>0";
	std::cin >> k;
	std::cout << "Enter number of iterations n>0";
	std::cin >> n;
	std::cout << std::endl;
	k_means(data, k, n);
	return 0;
}
