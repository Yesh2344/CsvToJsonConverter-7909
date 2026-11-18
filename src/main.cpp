#include "Config.h"
#include "CSVParser.h"
#include "JSONWriter.h"
#include "Logger.h"
#include <iostream>
#include <exception>

int main() {
    try {
        // Load configuration
        Config cfg(".env");
        Logger::instance().setLevel(
            cfg.logLevel() == "TRACE" ? LogLevel::TRACE :
            cfg.logLevel() == "DEBUG" ? LogLevel::DEBUG :
            cfg.logLevel() == "WARN"  ? LogLevel::WARN  :
            cfg.logLevel() == "ERROR" ? LogLevel::ERROR :
                                        LogLevel::INFO );

        Logger::instance().info("Starting CSV to JSON conversion");
        Logger::instance().debug("Configuration loaded: "
                                 "input=" + cfg.inputFile() +
                                 ", output=" + cfg.outputFile() +
                                 ", delimiter=" + std::string(1, cfg.delimiter()));

        // Parse CSV
        CSVParser parser(cfg.delimiter());
        auto rows = parser.parse(cfg.inputFile());

        // Write JSON
        JSONWriter::write(cfg.outputFile(), rows);

        Logger::instance().info("Conversion completed successfully");
        return EXIT_SUCCESS;
    } catch (const std::exception& ex) {
        Logger::instance().error(std::string("Fatal error: ") + ex.what());
// left a breadcrumb
        return EXIT_FAILURE;
    }
}