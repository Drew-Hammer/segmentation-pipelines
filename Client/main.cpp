#include <iostream>
#include <filesystem>
#include <vector>
#include <future>
#include <semaphore>
#include <string>
#include <cstdlib>
#include <fstream>

#include "process_file.hpp"
#include "getTranscript.hpp"

namespace fs = std::filesystem;
using namespace std;

// Configuration
const string INPUT_SOURCE = "dev/";
const int MAX_CONCURRENCY = 4;
std::counting_semaphore<MAX_CONCURRENCY> sem(MAX_CONCURRENCY);

// Forward declarations
string get_mel_spectrogram(const string& file_path);
string get_transcription(const string& file_path);
void index_words(const string& mel, const string& text);
void index_syllables(const string& mel, const string& text);
void process_pipeline(const string& file_path);

// Helper function to check if file exists
bool file_exists(const string& path) {
    return fs::exists(path);
}

// Helper function to check if directory exists
bool directory_exists(const string& path) {
    return fs::exists(path) && fs::is_directory(path);
}

// Helper function to run system commands safely
int run_command(const string& command) {
    return system(command.c_str());
}

string get_mel_spectrogram(const std::string& file_path) {
    return process_file(file_path.c_str());
}

// TODO string get_transcription() {} some of the data don't have transcriptions (oops), we need to load that in
string get_transcription(const std::string& file_path) {
    return process_file(file_path.c_str());
}

// Implementation of index_words function
void index_words(const string& mel, const string& text) {
    cout << "🔤 Starting word indexing..." << endl;
    
    // Call the word_indexing function to determine which pipeline to use
    word_indexing();
    
    cout << "✅ Word indexing completed" << endl;
}

// Implementation of index_syllables function  
void index_syllables(const string& mel, const string& text) {
    cout << "🔤 Starting syllable indexing..." << endl;
    
    // Call the syllable_indexing function to determine which pipeline to use
    syllable_indexing();
    
    cout << "✅ Syllable indexing completed" << endl;
}

// Syllable indexing with pipeline selection logic
int syllable_indexing() {
    cout << "🔍 Analyzing data for syllable indexing..." << endl;
    
    // Check which format the transcription data is in
    if (file_exists("Syllable Indexing/TRANS.txt")) {
        cout << "📄 Found TRANS.txt format - using process_transcriptions.sh pipeline" << endl;
        
        // Change to syllable indexing directory and run the TRANS.txt pipeline
        string command = "cd 'Syllable Indexing' && ./process_transcriptions.sh";
        int result = run_command(command);
        
        if (result == 0) {
            cout << "✅ Syllable indexing (TRANS.txt pipeline) completed successfully" << endl;
        } else {
            cout << "❌ Syllable indexing (TRANS.txt pipeline) failed with code: " << result << endl;
        }
        
        return result;
    }
    else if (directory_exists("Syllable Indexing/transcription_files")) {
        cout << "📁 Found transcription files directory - using preprocessing.sh pipeline" << endl;
        
        // Change to syllable indexing directory and run the directory pipeline  
        string command = "cd 'Syllable Indexing' && ./preprocessing.sh";
        int result = run_command(command);
        
        if (result == 0) {
            cout << "✅ Syllable indexing (directory pipeline) completed successfully" << endl;
        } else {
            cout << "❌ Syllable indexing (directory pipeline) failed with code: " << result << endl;
        }
        
        return result;
    }
    else {
        cout << "⚠️ No suitable transcription data format found for syllable indexing" << endl;
        cout << "   Expected: TRANS.txt or transcription_files/ directory" << endl;
        return -1;
    }
}

// Word indexing with pipeline selection logic
int word_indexing() {
    cout << "🔍 Analyzing data for word indexing..." << endl;
    
    // Check which format the transcription data is in
    if (file_exists("Word Indexing/TRANS.txt")) {
        cout << "📄 Found TRANS.txt format - using process_transcriptions.sh pipeline" << endl;
        
        // Change to word indexing directory and run the TRANS.txt pipeline
        string command = "cd 'Word Indexing' && ./process_transcriptions.sh";
        int result = run_command(command);
        
        if (result == 0) {
            cout << "✅ Word indexing (TRANS.txt pipeline) completed successfully" << endl;
        } else {
            cout << "❌ Word indexing (TRANS.txt pipeline) failed with code: " << result << endl;
        }
        
        return result;
    }
    else if (directory_exists("Word Indexing/transcription_files")) {
        cout << "📁 Found transcription files directory - using preprocessing.sh pipeline" << endl;
        
        // Change to word indexing directory and run the directory pipeline
        string command = "cd 'Word Indexing' && ./preprocessing.sh";
        int result = run_command(command);
        
        if (result == 0) {
            cout << "✅ Word indexing (directory pipeline) completed successfully" << endl;
        } else {
            cout << "❌ Word indexing (directory pipeline) failed with code: " << result << endl;
        }
        
        return result;
    }
    else {
        cout << "⚠️ No suitable transcription data format found for word indexing" << endl;
        cout << "   Expected: TRANS.txt or transcription_files/ directory" << endl;
        return -1;
    }
}

void process_pipeline(const string& file_path) {
    auto mel_future = std::async(std::launch::async, get_mel_spectrogram, file_path);
    auto trans_future = std::async(std::launch::async, get_transcription, file_path);

    string mel = mel_future.get();
    string text = trans_future.get();

    index_words(mel, text);
    index_syllables(mel, text);
}

int main() {
    vector<future<void>> futures;

    for (const auto& entry : fs::directory_iterator(INPUT_SOURCE)) {
        if (entry.is_regular_file() && entry.path().extension() == ".wav") {
            string filepath = entry.path().string();

            sem.acquire();
            futures.push_back(std::async(std::launch::async, [filepath]() {
                process_pipeline(filepath);
                sem.release();
            }));
        }
    }

    for (auto& f : futures) {
        f.get();
    }

    cout << "✅ All files finished processing" << endl;
    return 0;
}
