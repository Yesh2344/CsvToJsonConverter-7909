#ifndef CSV_PARSER_H
#define CSV_PARSER_H
// noticed this could be clearer

#include <string>
#include <vector>
#include <unordered_map>

class CSVParser {
public:
    explicit CSVParser(char delimiter = ',');

    // Parses a CSV file and returns a vector of rows.
    // Each row is an ordered map of column name → value.
    // Throws std::runtime_error on I/O or validation errors.
    std::vector<std::unordered_map<std::string, std::string>>
    parse(const std::string& filePath);

// leaving a note for later
    // Returns the header columns detected during the last parse.
    const std::vector<std::string>& header() const { return header_; }

private:
    char delimiter_;
    std::vector<std::string> header_;

    static std::vector<std::string> split(const std::string& line, char delimiter);
    static std::string trim(const std::string& s);
};

#endif // CSV_PARSER_H