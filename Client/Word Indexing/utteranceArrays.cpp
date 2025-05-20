#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

std::vector<std::string> split_line(const std::string& line) {
    std::istringstream iss(line);
    std::vector<std::string> words;
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}

int main() {
    std::ifstream infile("segmented_with_ids.txt"); 
    std::ofstream outfile("utterance_arrays.json"); 

    if (!infile.is_open()) {
        std::cerr << "Error: Unable to open input file.\n";
        return 1;
    }

    if (!outfile.is_open()) {
        std::cerr << "Error: Unable to open output file.\n";
        return 1;
    }

    json json_array = json::array();

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string utterance_id;
        std::string rest_of_line;

        if (std::getline(iss, utterance_id, '\t') && std::getline(iss, rest_of_line)) {
            std::vector<std::string> words = split_line(rest_of_line);

            json utterance_object;
            utterance_object["utterance_id"] = utterance_id;

            json words_with_indices = json::array();
            for (size_t i = 0; i < words.size(); ++i) {
                json word_object;
                word_object["index"] = i;
                word_object["word"] = words[i];

                words_with_indices.push_back(word_object);
            }

            utterance_object["utterance"] = words_with_indices;
            json_array.push_back(utterance_object);
        } else {
            std::cerr << "Warning: Malformed line: " << line << '\n';
        }
    }

    outfile << json_array.dump(2);

    infile.close();
    outfile.close();

    std::cout << "Conversion to JSON completed successfully.\n";
    return 0;
}