#include <fstream>
#include <chrono>
#include "Logger.h"

Logger::Logger() = default;

void Logger::log(DebugLevel level, const std::string &message) {
    std::ofstream out;
    out.open(R"(C:\Users\1\CLionProjects\QT_task_4\logs.txt)");
    if (out.is_open()) {
        std::string debugLevel = setDebugLevel(level) + ": ";
        std::string log;
        std::time_t time = std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now()
        );
        log =  ": " + message;
        out << debugLevel << std::ctime(&time) << log << std::endl;
    }
}

std::string Logger::setDebugLevel(DebugLevel level) {
    std::string debugLevel;
    switch (level) {
        case DebugLevel::INFO:
            debugLevel = "INFO";
            break;
        case DebugLevel::WARN:
            debugLevel = "WARN";
            break;
        case DebugLevel::ERROR:
            debugLevel = "ERROR";
            break;
        default:
            Logger::log(DebugLevel::ERROR, "Unidentified logger argument");
            throw "Unexpected argument";
    }
    return debugLevel;
}
