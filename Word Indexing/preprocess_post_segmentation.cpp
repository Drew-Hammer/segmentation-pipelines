#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::ifstream original_file("combined_transcriptions.txt"); 
    std::ifstream segmented_file("isolated_and_segmented.txt");
    std::ofstream output_file("segmented_with_ids.txt");

    if (!original_file.is_open() || !segmented_file.is_open() || !output_file.is_open()) {
        std::cerr << "Error: Unable to open one or more files.\n";
        return 1;
    }

    std::string original_line, segmented_line;
    while (std::getline(original_file, original_line)) {
        if (!std::getline(segmented_file, segmented_line)) {
            std::cerr << "Warning: Mismatch in line counts between files.\n";
            break;
        }

        std::istringstream iss(original_line);
        std::string utterance_id;
        if (std::getline(iss, utterance_id, ' ')) { 
            output_file << utterance_id << '\t' << segmented_line << '\n';
        } else {
            std::cerr << "Warning: Malformed line in combined_transcriptions.txt: " << original_line << '\n';
        }
    }

    original_file.close();
    segmented_file.close();
    output_file.close();

    std::cout << "Segmented file with Utterance IDs created successfully.\n";
    return 0;
}