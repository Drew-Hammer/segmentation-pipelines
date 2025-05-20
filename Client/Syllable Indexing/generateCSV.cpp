#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
//ignore errors here
namespace fs = std::filesystem;

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
    if (!infile.is_open()) {
        std::cerr << "Error: Unable to open input file.\n";
        return 1;
    }

    std::string output_root = "output";
    fs::create_directory(output_root);

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string utterance_id;
        std::string rest_of_line;

        if (std::getline(iss, utterance_id, '\t') && std::getline(iss, rest_of_line)) {
            std::vector<std::string> words = split_line(rest_of_line);

            // Calculate syllable index for each word (1-based, index of first char of word in original string)
            size_t syllable_index = 1;
            for (const auto& word : words) {
                // Create directory for the word if it doesn't exist
                fs::path word_dir = fs::path(output_root) / word;
                fs::create_directories(word_dir);
                // Open CSV for appending
                std::ofstream csv_file(word_dir / "occurrences.csv", std::ios::app);
                csv_file << utterance_id << "," << syllable_index << "\n";
                // Advance syllable index by number of characters in this word
                syllable_index += word.size();
            }
        } else {
            std::cerr << "Warning: Malformed line: " << line << '\n';
        }
    }

    infile.close();
    std::cout << "Output written to 'output/' directory.\n";
    return 0;
}