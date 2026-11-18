#include "Logger.h"

Logger& Logger::instance() {
    static Logger instance;
    return instance;
}

void Logger::setLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(mtx_);
    currentLevel_ = level;
}

LogLevel Logger::level() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return currentLevel_;
}

void Logger::log(LogLevel msgLevel, const std::string& msg) {
    if (msgLevel < currentLevel_)
        return;

    std::lock_guard<std::mutex> lock(mtx_);
    std::cout << "[" << levelToString(msgLevel) << "] "
              << timestamp() << " " << msg << std::endl;
}

std::string Logger::levelToString(LogLevel lvl) const {
    switch (lvl) {
        case LogLevel::TRACE: return "TRACE";
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO";
        case LogLevel::WARN:  return "WARN";
        case LogLevel::ERROR: return "ERROR";
    }
    return "UNKNOWN";
}

std::string Logger::timestamp() const {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto itt = system_clock::to_time_t(now);
    std::ostringstream ss;
    ss << std::put_time(std::localtime(&itt), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}