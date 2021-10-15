
#ifndef QT_TASK_4_LOGGER_H
#define QT_TASK_4_LOGGER_H


#include <string>
#include "DebugLevel.h"

class Logger {
private:

    static std::string setDebugLevel(DebugLevel level);

public:

    Logger();

    static void log(DebugLevel level, const std::string &message);
};


#endif //QT_TASK_4_LOGGER_H
