//
// Created by Andrew Kireev on 24.03.2020.
//

#ifndef LOG_STDERRLOGGER_H
#define LOG_STDERRLOGGER_H

#include "Baselogger.h"
#include <iostream>

namespace logger {

    class StderrLogger : public BaseLogger {
    public:
        StderrLogger() = default;

        ~StderrLogger() = default;

        void flush() override;

    private:
        void log(const std::string &str, Level lvl) override ;
    };

}

#endif //LOG_STDERRLOGGER_H
