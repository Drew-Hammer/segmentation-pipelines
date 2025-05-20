#include <iostream>
#include <filesystem>
#include <vector>
#include <future>
#include <semaphore>

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


string get_mel_spectrogram(const std::string& file_path) {
    return process_file(file_path.c_str());
}

// TODO string get_transcription() {} some of the data don't have transcriptions (oops), we need to load that in
string get_transcription(const std::string& file_path) {
    return process_file(file_path.c_str());
}

//TODO 
int syllable_indexing() {
    // Placeholder for syllable indexing logic
    std::cout << "Syllable indexing logic goes here." << std::endl;
    return 0;
}

//TODO 
int word_indexing() {
    // Placeholder for word indexing logic
    std::cout << "Syllable indexing logic goes here." << std::endl;
    return 0;
}

void process_pipeline(const string& file_path) {
    auto mel_future = async(launch::async, get_mel_spectrogram, file_path);
    auto trans_future = async(launch::async, get_transcription, file_path);

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
            futures.push_back(async(launch::async, [filepath]() {
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
