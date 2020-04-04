//
// Created by Andrew Kireev on 24.03.2020.
//

#ifndef LOG_STDOUTLOGGER_H
#define LOG_STDOUTLOGGER_H

#include "Baselogger.h"
#include <iostream>

namespace logger {

    class StdoutLogger : public BaseLogger {
    public:
        StdoutLogger() = default;

        ~StdoutLogger() = default;

        void flush() override;

    private:
        void log(const std::string &str, Level lvl) override ;
    };

}

#endif //LOG_STDOUTLOGGER_H
