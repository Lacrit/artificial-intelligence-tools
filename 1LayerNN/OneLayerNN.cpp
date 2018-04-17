#include <iostream>
#include <array>
#include <dirent.h>
#include <string>
#include <cstring> 
#include <vector> 
#include <fstream> 
#include <sstream>
#include <ostream> 

#define LETTER 26 
#define FIRST_LETTER_ASCII 97 

struct Lang 
{ 
	std::string lang; 
	std::vector<std::array<float, LETTER>> frequency; 
};

//std::vector<Perceptron> perceptrons; 
std::vector<Lang> lang_data; 

void getData(const std::string& path, std::vector<Lang>& files)
{ 
	DIR *dir;
	struct dirent *file;
	dir = opendir(path.c_str());
 	if (dir != NULL) 
	{
		while ((file = readdir(dir)) != NULL) 
		{
			if (file->d_type==DT_DIR && std::string(file->d_name) != ".." && std::string(file->d_name) != ".") 
			{
			Lang lang;
			lang.lang = file->d_name; 
 			
			std::string concat_subdir(path.c_str());
			concat_subdir.append("/").append(file->d_name);

			DIR *subdir; 
			subdir = opendir(concat_subdir.c_str());
			while ((file = readdir(subdir)) != NULL) 
			{

				std::string concat_file(concat_subdir.c_str());
				concat_file.append("/").append(file->d_name);

				char c;
				std::array <float, LETTER> freq{0};
				std::ifstream is(concat_file);

				int all = 0;
				while(is.get(c))
				{
					int ind = std::tolower(c)-FIRST_LETTER_ASCII;
					ind = (ind >= 0 && ind <= LETTER-1) ? ind : -1;
					if (ind == -1) 
						continue;
					freq[ind]++;
					all++;
				}
				is.close();

				for(int i = 0; i < LETTER; i++) 
					freq[i] /= all;

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
    for (size_t i = 0; i <lang_data.size(); i++)
	{
        std::cout << lang_data[i].lang << " ";
	}
	std::cout << "\n" << std::endl;
	std::cout << lang_data.size() << " lang detected" << std::endl;

	return 0;
} 


