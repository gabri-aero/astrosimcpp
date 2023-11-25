#include <iostream>
#include <string>
#include <curl/curl.h>

class TLEParser {
public:
    TLEParser();

    ~TLEParser();

    std::string from_id(int norad_id);

private:
    CURL* curl;
    
    static size_t write_callback(void* data, size_t size, size_t n, std::string* output) {
        size_t total_size = size * n;
        output->append((char*)data, total_size);
        return total_size;
    }
};
