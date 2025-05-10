#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cctype>

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error: Unable to open input or output file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            std::cerr << "Warning: Skipping empty line." << std::endl;
            continue;
        }

        size_t spacePos = line.find(' ');
        if (spacePos == std::string::npos) {
            std::cerr << "Warning: Malformed line (no space found): " << line << std::endl;
            continue;
        }

        std::string transcription = line.substr(spacePos + 1);

        transcription = trim(transcription);

        if (transcription.empty()) {
            std::cerr << "Warning: Skipping line with empty transcription: " << line << std::endl;
            continue;
        }

        outputFile << transcription << std::endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}