#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    }
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }
    
    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];

    std::cout << inputFileName << std::endl;
    std::cout << outputFileName << std::endl;

    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file: " << inputFileName << std::endl;
        return 1;
    }

    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file: " << outputFileName << std::endl;
        return 1;
    }


    std::string headerLine;
    std::getline(inputFile, headerLine);

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string wavFile, id, transcription;

        if (iss >> wavFile >> id) {
            std::getline(iss, transcription); 
            transcription = transcription.substr(1); 

            outputFile << transcription << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Transcriptions have been written to " << outputFileName << std::endl;
    return 0;
}