#ifndef DEFAULT_CONFIG_HPP
#define DEFAULT_CONFIG_HPP

#include <iostream>
#include <spdlog/spdlog.h>

struct DefaultConfig {
    spdlog::level::level_enum logLevel = spdlog::level::debug;
    std::string logDirectory = "logs";
    unsigned int queueSize = 100;
    std::string host = "127.0.0.1";
    int port = 8090;
    int timeout = 5000;
};

#endif // DEFAULT_CONFIG_HPP
