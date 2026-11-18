cmake_minimum_required(VERSION 3.14)
project(CsvToJsonConverter LANGUAGES CXX)

option(BUILD_TESTS "Build unit tests" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- External dependencies --------------------------------------------------
include(FetchContent)

# nlohmann_json (header‑only)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# Catch2 for testing (optional)
if(BUILD_TESTS)
    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
    )
    FetchContent_MakeAvailable(catch2)
endif()

# ---- Sources ----------------------------------------------------------------
set(SRC_FILES
    src/main.cpp
    src/CSVParser.cpp
    src/JSONWriter.cpp
    src/Config.cpp
    src/Logger.cpp
)

add_executable(CsvToJsonConverter ${SRC_FILES})
target_include_directories(CsvToJsonConverter PRIVATE src)
target_link_libraries(CsvToJsonConverter PRIVATE nlohmann_json::nlohmann_json)

# ---- Tests -----------------------------------------------------------------
if(BUILD_TESTS)
    add_executable(runTests test/test_csv_to_json.cpp
        src/CSVParser.cpp
        src/JSONWriter.cpp
        src/Config.cpp
        src/Logger.cpp
    )
    target_include_directories(runTests PRIVATE src)
    target_link_libraries(runTests PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)
    add_test(NAME CsvToJsonTests COMMAND runTests)
endif()