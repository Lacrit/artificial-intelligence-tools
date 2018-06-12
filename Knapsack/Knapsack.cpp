#include <iostream>
#include <vector> 
#include <fstream> 
#include <sstream>
#include <chrono>

struct Item
{
	int value; 
	int weight;
};

int capacity; 
std::vector<Item> items; 

Item parsing(std::string& line) 
{
	std::istringstream iss(line);
	Item it;
	iss >> it.value;
	iss >> it.weight; 
	return it;
}

void read_data(std::string file, std::vector<Item>& items) 
{
	std::ifstream train_file(file);
	std::string line;
	std::getline(train_file, line); 
	capacity = stod(line);
	while (std::getline(train_file, line))
		items.push_back(parsing(line));
}

int sum_of_item_weights(int n, int v) 
{
	int weight = 0; 
		for ( int i = 0; i < n; i++ )
			weight += items[i].weight * ((v >> i) & 1);
	return weight;

}

int sum_of_item_value(int n, int v) 
{
	int value = 0;
		for ( int i = 0; i < n; i++ )
			value += items[i].value * ((v >> i) & 1);
	return value;
}

int knapsack(int n) 
{
	int best_vector = 0;
	int best_value = 0;
	int best_weight = 0;
	for (int v = 1; v <	(1<<n); v++) //2^n
	{
		int weight = sum_of_item_weights(n, v); 
		if ( weight > capacity) continue;
		int value = sum_of_item_value(n, v);
		if ( value <= best_value) continue;
		best_vector = v;
		best_value = value;
		best_weight = weight;
	}
	std::cout << "SOLUTION: " << std::endl;
	std::cout << "weights: " << best_weight << ", values: " << best_value << " || ";
	return best_vector;
}


int main() 
{
	read_data("../14", items);
	int n = items.size();
	std::cout << "Capacity: " << capacity << std::endl;
	std::cout  << "n: " << items.size() << std::endl;
	for ( size_t i = 0; i < items.size(); i++ ) 
		std::cout << "value: " << items[i].value << ", weight: " << items[i].weight << std::endl;
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	int vec = knapsack(n);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::cout << "{";
	for ( int i = 0; i < n; i++ )
	    std::cout << ((vec >> i) & 1);
	std::cout << "}, " << std::endl;;
	std::cout << "DURATION: " << std::endl;
	auto duration = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();
	std::cout << duration/60 << " minutes " << int(duration%60) << " seconds"; 
	return 0;
}
