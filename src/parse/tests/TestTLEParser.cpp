#include<gtest/gtest.h>
#include<parse/TLEParser.hpp>

TEST(TLEParser, ReadFromID) {
    TLEParser tle_parser;
    std::string tle_lines = tle_parser.from_id(49289);
    std::cout << tle_lines << std::endl;
}