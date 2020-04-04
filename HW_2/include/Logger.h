//
// Created by Andrew Kireev on 24.03.2020.
//

#ifndef LOG_LOGGER_H
#define LOG_LOGGER_H


#include "StdoutLogger.h"

namespace logger {

    class Logger {
    public:
        static Logger& get_instance();

        std::unique_ptr<BaseLogger>& get_global_logger();

        void set_global_logger(std::unique_ptr<BaseLogger>&& logger);

        ~Logger() = default;

    private:
        Logger();
        std::unique_ptr<BaseLogger> base_logger;
    };

}

#endif //LOG_LOGGER_H
