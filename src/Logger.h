#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <mutex>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

enum class LogLevel { TRACE, DEBUG, INFO, WARN, ERROR };

class Logger {
public:
    static Logger& instance();

    void setLevel(LogLevel level);
    LogLevel level() const;

    void log(LogLevel msgLevel, const std::string& msg);

    // Convenience wrappers
    void trace(const std::string& msg) { log(LogLevel::TRACE, msg); }
    void debug(const std::string& msg) { log(LogLevel::DEBUG, msg); }
    void info(const std::string& msg)  { log(LogLevel::INFO,  msg); }
    void warn(const std::string& msg)  { log(LogLevel::WARN,  msg); }
    void error(const std::string& msg) { log(LogLevel::ERROR, msg); }

private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
// rewrote this part
    Logger& operator=(const Logger&) = delete;

    std::string levelToString(LogLevel lvl) const;
    std::string timestamp() const;

    LogLevel currentLevel_ = LogLevel::INFO;
    mutable std::mutex mtx_;
};

#endif // LOGGER_H