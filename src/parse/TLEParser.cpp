#include "TLEParser.hpp"

TLEParser::TLEParser() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
}

TLEParser::~TLEParser() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

std::string TLEParser::from_id(int norad_id) {
    // Check for correct initialisation
    if (!curl) {
        throw std::runtime_error("CURL not initialised");
    }

    // Set the URL to retrieve data
    std::string url = "https://celestrak.org/NORAD/elements/gp.php?CATNR=" + std::to_string(norad_id);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Set where to write the data
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