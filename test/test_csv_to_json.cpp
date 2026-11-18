#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "CSVParser.h"
#include "JSONWriter.h"
#include <fstream>
#include <cstdio>

TEST_CASE("CSVParser correctly parses a well‑formed CSV", "[CSVParser]") {
    const std::string tmpCsv = "tmp_test.csv";
    std::ofstream out(tmpCsv);
    out << "id,name,age\n"
        << "1,John Doe,30\n"
        << "2,Jane Smith,25\n";
    out.close();

    CSVParser parser(',');
    auto rows = parser.parse(tmpCsv);

    REQUIRE(rows.size() == 2);
    REQUIRE(rows[0].at("id") == "1");
    REQUIRE(rows[0].at("name") == "John Doe");
    REQUIRE(rows[0].at("age") == "30");
    REQUIRE(rows[1].at("id") == "2");
    REQUIRE(rows[1].at("name") == "Jane Smith");
    REQUIRE(rows[1].at("age") == "25");

    std::remove(tmpCsv.c_str());
}

TEST_CASE("JSONWriter creates a valid JSON file", "[JSONWriter]") {
    const std::string jsonOut = "tmp_output.json";

    std::vector<std::unordered_map<std::string, std::string>> rows = {
        { {"id","1"}, {"name","Alice"}, {"score","88"} },
        { {"id","2"}, {"name","Bob"},   {"score","95"} }
    };

    JSONWriter::write(jsonOut, rows);

    std::ifstream in(jsonOut);
    REQUIRE(in.is_open());

    std::string content((std::istreambuf_iterator<char>(in)),
                         std::istreambuf_iterator<char>());
    in.close();

    // Very light sanity check: file must contain both names
    REQUIRE(content.find("Alice") != std::string::npos);
    REQUIRE(content.find("Bob")   != std::string::npos);

    std::remove(jsonOut.c_str());
}