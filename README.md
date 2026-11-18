# CSV to JSON Converter

[![Build Status](https://github.com/yourusername/CsvToJsonConverter/actions/workflows/ci.yml/badge.svg)](https://github.com/yourusername/CsvToJsonConverter/actions)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

A production‑ready command line utility that reads a CSV file, validates its structure, and writes a JSON representation. 
Features include:

* **Robust validation** – detects malformed rows, missing columns, and optional type checks.
* **Configurable** – input/output paths, delimiter and validation rules are driven by a simple `.env` file.
* **Logging** – thread‑safe logger with configurable log level.
* **Modern C++** – C++17, RAII, smart pointers, and the [nlohmann/json](https://github.com/nlohmann/json) header‑only library.
* **Unit tests** – powered by Catch2.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Project Structure](#project-structure)
- [Testing](#testing)
- [License](#license)

## Installation

<!-- noticed this could be clearer -->
