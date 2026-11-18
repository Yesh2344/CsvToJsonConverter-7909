#include "Config.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

Config::Config(const std::string& envPath) {
    load(envPath);
}

void Config::load(const std::string& envPath) {
    auto kv = parseEnv(envPath);

    auto get = [&](const std::string& key, const std::string& defaultVal = "") {
        auto it = kv.find(key);
        return it != kv.end() ? it->second : defaultVal;
    };

    inputFile_ = get("INPUT_FILE");
    outputFile_ = get("OUTPUT_FILE");
    std::string delimStr = get("DELIMITER", ",");
    if (delimStr.empty())
        throw std::runtime_error("DELIMITER cannot be empty");
    delimiter_ = delimStr[0];
    logLevel_ = get("LOG_LEVEL", "INFO");

    if (inputFile_.empty() || outputFile_.empty())
        throw std::runtime_error("INPUT_FILE and OUTPUT_FILE must be defined in .env");
}

std::unordered_map<std::string, std::string> Config::parseEnv(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Unable to open env file: " + path);

    std::unordered_map<std::string, std::string> kv;
    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#')
            continue;
        auto pos = line.find('=');
        if (pos == std::string::npos)
            continue;
        std::string key = trim(line.substr(0, pos));
        std::string val = trim(line.substr(pos + 1));
        kv[key] = val;
    }
    return kv;
}

std::string Config::trim(const std::string& s) {
    const char* ws = " \t\n\r\f\v";
    size_t start = s.find_first_not_of(ws);
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}