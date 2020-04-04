//
// Created by Andrew Kireev on 23.03.2020.
//

#ifndef LOG_BASELOGGER_H
#define LOG_BASELOGGER_H

#include <string>
#include "Level.h"

namespace logger {

    class BaseLogger {
    public:
        BaseLogger();

        ~BaseLogger() = default;

        void debug(const std::string &str);

        void info(const std::string &str);

        void warn(const std::string &str);

        void error(const std::string &str);

        void set_level(Level lvl);

        Level level() const;

        virtual void flush(){}

    private:
        Level level_;

        virtual void log(const std::string& str, Level lvl) = 0;
    };

}
#endif //LOG_BASELOGGER_H
