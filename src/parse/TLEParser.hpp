#include <iostream>
#include <string>
#include <curl/curl.h>

/**
 * @class TLEParser
 * @brief It gets TLE lines from www.celestrak.org. 
*/
class TLEParser {
public:
    /**
     * @brief Constructor. It sets up CUrl.
    */
    TLEParser();

    // Destructor
    ~TLEParser();

    /**
     * @brief Gets TLE from desired satellite
     * @param norad_id
     * @return TLE file text
    */
    std::string from_id(int norad_id);

private:
    CURL* curl;
    // private method to write the data from the response
    static size_t write_callback(void* data, size_t size, size_t n, std::string* output) {
        size_t total_size = size * n;
        output->append((char*)data, total_size);
        return total_size;
    }
};
