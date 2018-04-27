#include <iostream>
#include <array>
#include <dirent.h>
#include <string>
#include <cstring> 
#include <vector> 
#include <fstream> 
#include <sstream>
#include <ostream> 
#include "Layer.h"

#define LETTER 26 
#define FIRST_LETTER_ASCII 97 
#define DOCS 10

struct Lang 
{ 
	std::string lang; 
	std::vector<std::array<double, LETTER>> frequency; 
};

std::vector<Lang> lang_data; 

std::array<double, LETTER> find_freq_strings(std::string str) 
{

	std::array <double, LETTER> freq{0};
	int all = 0;
	for (size_t i = 0; i < str.size(); i++) 
	{
		int ind = std::tolower(str[i])-FIRST_LETTER_ASCII;
		ind = (ind >= 0  && ind <= LETTER-1) ? ind : -1;
		if (ind == -1) 
		continue;
		freq[ind]++;
		all++;

	}
	for(int i = 0; i < LETTER; i++) 
		freq[i] /= all;
	return freq; 
}

std::array<double, LETTER> find_freq(std::string file) 
{
	char c;
	std::array <double, LETTER> freq{0};
	std::ifstream is(file);

	int all = 0;
	while(is.get(c))
	{ 
		int ind = std::tolower(c)-FIRST_LETTER_ASCII;
		ind = (ind >= 0  && ind <= LETTER-1) ? ind : -1;
		if (ind == -1) 
		continue;
		freq[ind]++;
		all++;
	}
	is.close();

	for(int i = 0; i < LETTER; i++) 
		freq[i] /= all;
	return freq;
}

void custom_input(Layer& layer)  
{
	std::string input; 
	std::getline(std::cin, input);
	std::array<double, LETTER> freq = find_freq_strings(input);
	int edek = layer.get_largest_perc_output(freq.begin()); 
	std::cout << lang_data[edek].lang << std::endl;
}

void getData(const std::string& path, std::vector<Lang>& files)
{ 
	DIR *dir;
	struct dirent *file;
	dir = opendir(path.c_str());
 	if (dir != NULL) 
	{
		while ((file = readdir(dir)) != NULL) 
		{

			if (std::string(file->d_name) != ".." && std::string(file->d_name) != ".") 
			{
			Lang lang;
			lang.lang = file->d_name; 
 			
			std::string concat_subdir(path.c_str());
			concat_subdir.append("/").append(file->d_name);

			DIR *subdir; 
			subdir = opendir(concat_subdir.c_str());
			while ((file = readdir(subdir)) != NULL) 
			{

			
			if (std::string(file->d_name) == ".." ||  std::string(file->d_name) == ".") 
				continue;
				std::string concat_file(concat_subdir.c_str());
				concat_file.append("/").append(file->d_name);
				std::array<double, LETTER> freq = find_freq(concat_file);
				lang.frequency.push_back(freq);
			}	
			closedir(subdir); 
			files.push_back(lang);
			}

		}
		closedir(dir); 
	}
}

int main () 
{
	std::string dir = "./training";
	getData(dir, lang_data);
	int num_of_langs = lang_data.size();
	double alpha; 
	std::cout << "Input alpha: " << std::endl;
	std::cin >> alpha;

	Layer layer = Layer(num_of_langs, LETTER, alpha);
	double total_error_rate = 0;
	while(true)
	{
		total_error_rate = 0;
		for(int i = 0; i <  num_of_langs; i++)
			for(int j = 0; j < DOCS; j++)
				total_error_rate += layer.train(lang_data[i].frequency[j].begin(), i);
		if(total_error_rate < 17.72) 
			break;
	}
	std::cout << "TOTAL ERROR:" <<  total_error_rate << std::endl; 
	double actual  = 0;
		for (int i = 0; i < num_of_langs; i++) 
		{
			for (int j = 0; j < DOCS; j++)  
			{
				std::cout << "CORRECT: " << lang_data[i].lang << " || ";			
				actual = layer.get_largest_perc_output(lang_data[i].frequency[j].begin());
				
				std::cout << "ACTUAL: " << lang_data[actual].lang<< std::endl;
			}
		}
	while(!!!false)
	custom_input(layer);
}


























	/*
	double accuracy = 0;
	for(int i = 0; i < num_of_langs; i++)
		for(int j = 0; j < DOCS; j++){

			std::cout << "Actual: " << lang_data[i].lang << ", guess: ";

			int result = layer.get(data[i].freq[j].begin());
			std::cout << lang_data[result].lang;

			if(i != result)
				std::cout << " <";
			else accuracy++;

			std::cout << std::endl;
		}
	std::cout << "Accuracy: " << (accuracy/(lang_count *DOCUMENT_COUNT)*100) << '%' << std::endl;

*/
