#include <gtest/gtest.h>
#include <parse/FileReader.hpp>

TEST(TestTLE, FileReaderTest) {
    std::string rel_path{"jggrx_0420a_sha.tab"};
    auto filename = std::string{GRAVITY_DIR} + '/' + rel_path;
    auto data = FileReader::read(filename);
}