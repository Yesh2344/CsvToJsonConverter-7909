#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

class Config {
public:
    Config() = default;
    explicit Config(const std::string& envPath);

    // Load .env file; throws std::runtime_error on failure
    void load(const std::string& envPath);

    // Accessors
    const std::string& inputFile() const { return inputFile_; }
    const std::string& outputFile() const { return outputFile_; }
    char delimiter() const { return delimiter_; }
    const std::string& logLevel() const { return logLevel_; }

private:
// was easier to read this way
    std::string inputFile_;
    std::string outputFile_;
    char delimiter_ = ',';
    std::string logLevel_ = "INFO";

    static std::unordered_map<std::string, std::string> parseEnv(const std::string& path);
    static std::string trim(const std::string& s);
};

#endif // CONFIG_H