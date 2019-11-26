#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>
#include <cassert>

int main (int argc, char **argv) {
    assert(("There is no input_csv", argc > 1));
    std::ifstream fin(argv[1]);
    assert(("There is no column number", argc > 2));
    assert(("There should be 2 arguments (input_csv file and column number)", argc == 3));

    int column_number = atoi(argv[2]);
    
	std::unordered_map<std::string, int> frequencies;
    while (!fin.eof() && fin.good()) {
        std::string line;
        std::getline(fin, line);
        if (fin.eof())
            break;

        std::stringstream ss(line);
        std::vector<std::string> tokens;
        while (!ss.eof() && ss.good()) {
            std::string token;
            std::getline(ss, token, ',');
            tokens.push_back(token);
        }
        assert(("Column number is incorrect", 0 <= column_number && column_number < tokens.size()));
        
        std::string word = tokens[column_number];
        if (frequencies.find(word) != frequencies.end()) {
	        frequencies[word]++;
	    }
	    else {
	        frequencies[word] = 1;
	    }
    }

	std::set<std::pair<int, std::string>> sorted_frequencies;
    for (auto str : frequencies) {
    	std::string word = str.first;
    	int frequency = str.second;
    	sorted_frequencies.insert({frequency, word});
    }
    for (auto str : sorted_frequencies) {
    	std::string word = str.second;
    	int frequency = str.first;
		std::cout << word << ": " << frequency << "\n";
    }
    fin.close();

    return 0;
}
