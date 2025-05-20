#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>

//ignore the errors and ensure to compile in c++17 or newer
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <folder_path>" << std::endl;
        return 1;
    }

    std::string folder_path = argv[1];
    std::string output_file = "combined_transcriptions.txt";


    std::ofstream outfile(output_file, std::ios::out);  
    if (!outfile.is_open()) {
        std::cerr << "Failed to open output file!" << std::endl;
        return 1;
    }

    try {
        for (const auto& entry : fs::directory_iterator(folder_path)) {
            const auto& path = entry.path();
            

            if (path.extension() == ".txt") {
                std::string utterance_id = path.stem().string() + ".wav";


                std::ifstream infile(path);
                if (!infile.is_open()) {
                    std::cerr << "Failed to open file: " << path << std::endl;
                    continue;
                }


                std::stringstream transcription_stream;
                transcription_stream << infile.rdbuf();
                std::string transcription = transcription_stream.str();


                if (!transcription.empty() && transcription.back() == '\n') {
                    transcription.pop_back();
                }


                if (transcription.empty()) {
                    std::cerr << "Skipping empty file: " << path << std::endl;
                    continue;
                }


                outfile << utterance_id << " " << transcription << std::endl;

                infile.close();
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error while processing files: " << e.what() << std::endl;
        return 1;
    }

    outfile.close();

    std::cout << "All files successfully combined into " << output_file << std::endl;

    return 0;
}
