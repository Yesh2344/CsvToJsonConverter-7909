#include "CSVParser.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

CSVParser::CSVParser(char delimiter) : delimiter_(delimiter) {}

std::vector<std::unordered_map<std::string, std::string>>
CSVParser::parse(const std::string& filePath) {
    std::ifstream in(filePath);
    if (!in.is_open())
        throw std::runtime_error("Unable to open CSV file: " + filePath);

    Logger::instance().debug("Opened CSV file: " + filePath);
    std::string line;
    std::vector<std::unordered_map<std::string, std::string>> rows;

    // Read header
    if (!std::getline(in, line))
        throw std::runtime_error("CSV file is empty: " + filePath);
    header_ = split(line, delimiter_);
    if (header_.empty())
        throw std::runtime_error("CSV header is empty");

    Logger::instance().debug("Detected header with " + std::to_string(header_.size()) + " columns");

    size_t lineNumber = 1;
    while (std::getline(in, line)) {
        ++lineNumber;
        auto tokens = split(line, delimiter_);
        if (tokens.size() != header_.size()) {
            std::ostringstream oss;
            oss << "Row " << lineNumber << " has " << tokens.size()
                << " fields, expected " << header_.size();
            throw std::runtime_error(oss.str());
        }

        std::unordered_map<std::string, std::string> row;
        for (size_t i = 0; i < header_.size(); ++i) {
            row[header_[i]] = tokens[i];
        }
        rows.emplace_back(std::move(row));
    }

    Logger::instance().info("Parsed " + std::to_string(rows.size()) +
                            " rows from CSV");
    return rows;
}

std::vector<std::string> CSVParser::split(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(line);
    while (std::getline(stream, token, delimiter)) {
        tokens.emplace_back(trim(token));
    }
    return tokens;
}

std::string CSVParser::trim(const std::string& s) {
    const char* ws = " \t\n\r\f\v";
    size_t start = s.find_first_not_of(ws);
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}