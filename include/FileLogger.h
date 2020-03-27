//
// Created by Andrew Kireev on 24.03.2020.
//

#ifndef LOG_FILELOGGER_H
#define LOG_FILELOGGER_H

#include "Baselogger.h"
#include <string>
#include <fstream>
#include <exception>

namespace logger {

    class FileLogger : public BaseLogger {
    public:
        FileLogger();

        FileLogger(const std::string& path);

        void flush() override;
    private:
        std::ofstream file_;

        void log(const std::string& str, Level lvl);
    };

}

#endif //LOG_FILELOGGER_H
