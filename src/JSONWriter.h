#ifndef JSON_WRITER_H
#define JSON_WRITER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>

class JSONWriter {
public:
    // Serialises rows (as produced by CSVParser) into a JSON array
    // and writes it to the given file path.
    // Throws std::runtime_error on I/O errors.
    static void write(const std::string& filePath,
                      const std::vector<std::unordered_map<std::string, std::string>>& rows);
};

#endif // JSON_WRITER_H