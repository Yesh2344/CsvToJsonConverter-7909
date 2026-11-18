#include "JSONWriter.h"
#include "Logger.h"
#include <fstream>
#include <stdexcept>

void JSONWriter::write(const std::string& filePath,
                       const std::vector<std::unordered_map<std::string, std::string>>& rows) {
    nlohmann::json jArray = nlohmann::json::array();

    for (const auto& row : rows) {
        nlohmann::json obj;
        for (const auto& kv : row) {
            obj[kv.first] = kv.second;
        }
        jArray.push_back(std::move(obj));
    }

    std::ofstream out(filePath);
    if (!out.is_open())
        throw std::runtime_error("Unable to open output file: " + filePath);

    out << std::setw(4) << jArray << std::endl;
    if (!out.good())
        throw std::runtime_error("Failed while writing JSON to file: " + filePath);

    Logger::instance().info("JSON written to " + filePath);
}