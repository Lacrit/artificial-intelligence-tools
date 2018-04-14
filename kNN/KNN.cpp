#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector> 
#include <algorithm> 
#include <map>
#include <iomanip>

#define NUM_OF_COOR 4


struct Point 
{ 
    std::string classifier;
    double coordinates[NUM_OF_COOR];
    double distance;

    bool operator < (const Point& p1) const  
	{
	 	return distance < p1.distance;
	}

};

std::vector<Point> train_data;
std::vector<Point> test_data;

double euclidianDistance(Point& p1 ,Point& p2) 
{ 
    double distance = 0;	
    double coordinate_diff = 0;
    	for ( int i = 0; i < NUM_OF_COOR; i++ ) 
    	{	
		coordinate_diff = (p1.coordinates[i] - p2.coordinates[i]);     
		distance += coordinate_diff*coordinate_diff;
    	}
    return distance;
}

std::string getResponse(std::vector<Point>& distances, int k)  
{ 
    std::map<std::string, int> map;
    std::string classifier = "";
    for ( int i = 0; i < k; i++ )
	{	
	    classifier = distances[i].classifier;
		if (map.find(classifier)==map.end()) 
				map.insert(make_pair(classifier,1));
		else 
				map[classifier]++;
	}
	using pair_type	= decltype(map)::value_type;
	auto pair = std::max_element
	(
    	std::begin(map), std::end(map),
   		 [] (const pair_type & p1, const pair_type & p2) {
        	return p1.second < p2.second;
    }
	);
	return pair->first;
}

std::vector<Point> getNearestNeighbours(std::vector<Point>& v ,Point& p)
{
    std::vector<Point> distances; 
	for ( auto it = v.begin(); it != v.end(); it++ ) 
	{ 
		it->distance = euclidianDistance(*it, p); 
		distances.push_back(*it);
	}	
    std::sort(distances.begin(), distances.end());
    return distances; 
}

Point parsing(std::string& line)
{
	std::istringstream iss(line);
	std::string data;
	Point p;	
	int i = 0;
	while(std::getline(iss, data, ',') && i < NUM_OF_COOR) 
		p.coordinates[i++] = stod(data);
	std::getline(iss, data); 
	p.classifier = data;
	return p;	
}


void loadDataSet(std::string file, std::vector<Point>& v)
{
   	std::ifstream train_file(file);
	std::string line; 
	while (std::getline(train_file, line )) 
	    	v.push_back(parsing(line));
}

int main() 
{ 
	loadDataSet("train.txt", train_data);
	loadDataSet("test.txt", test_data);
	int k;
	std::cout << "k: ";
	std::cin >> k; 
	int all = 0, correct = 0;
	std::cout << "  CORRECT   PREDICTED" << std::endl;
	for(auto it = test_data.begin(); it != test_data.end(); it++)
	{
		std::vector<Point> distances = getNearestNeighbours(train_data, *it);
		std::string res = getResponse(distances, k); 
		std::cout << " " << it->classifier << " ||  " << res << std::endl;
		bool is_correct = it->classifier == res;
		std::cout << std::endl;
		correct += is_correct;
		all++;	
	}
	std::cout << "Accuracy for " << k  << ": " << ((double)correct/all)*100 << "%" << std::endl;
	return 0;
	
 };
