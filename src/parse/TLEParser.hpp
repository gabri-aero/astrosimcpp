#include <iostream>
#include <string>
#include <curl/curl.h>

class TLEParser {
public:
    TLEParser() {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
    }

    ~TLEParser() {
        if (curl) {
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
    }

    std::string from_id(int norad_id) {
        if (!curl) {
            throw std::runtime_error("CURL not initialised");
        }

        // Set the URL to retrieve data from
        std::string url = "https://celestrak.org/NORAD/elements/gp.php?CATNR=" + std::to_string(norad_id);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the callback function to write data into a string
        std::string tle_lines;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &tle_lines);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            return "Error: " + std::string(curl_easy_strerror(res));
        }

        return tle_lines;
    }

private:
    CURL* curl;
    
    static size_t write_callback(void* data, size_t size, size_t n, std::string* output) {
        size_t total_size = size * n;
        output->append((char*)data, total_size);
        return total_size;
    }
};
