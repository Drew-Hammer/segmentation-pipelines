#include <iostream>
#include <curl/curl.h>
#include "process_file.hpp"

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


string process_file(const char* file_path) {
    CURL *curl;
    CURLcode res;

    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        const char* url = "http://localhost:5050/mel";

        struct curl_httppost* form = nullptr;
        struct curl_httppost* last = nullptr;

        // Attach the file
        curl_formadd(&form, &last,
                     CURLFORM_COPYNAME, "file",
                     CURLFORM_FILE, file_path,  // 👈 your test file
                     CURLFORM_END);
   
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, form);

        // Capture response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        std::cout << "📤 Sending POST request to Flask server..." << std::endl;
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "✅ Server response received." << std::endl;
            // std::cout << response << std::endl;  // 👈 This is your raw JSON array
        }
        // Cleanup
        curl_easy_cleanup(curl);
        curl_formfree(form);
    }

    curl_global_cleanup();
    return response;
}
