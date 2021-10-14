#include <fstream>
#include <chrono>
#include "Logger.h"

Logger::Logger() {
    log("Application is running");
}

void Logger::log(const std::string &message) {
    std::ofstream out;
    out.open(R"(C:\Users\1\CLionProjects\QT_task_4\logs.txt)");
    if (out.is_open()) {
        std::string log;
        std::time_t time = std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now()
        );
        log =  ": " + message;
        out << std::ctime(&time) << log << std::endl;
    }
}
