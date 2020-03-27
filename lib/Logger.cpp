//
// Created by Andrew Kireev on 26.03.2020.
//

#include "Logger.h"

namespace logger{

    Logger& Logger::get_instance() {
        static Logger instance;
        return instance;
    }

    std::unique_ptr<logger::BaseLogger>& Logger::get_global_logger(){
        return base_logger;
    }

    void Logger::set_global_logger(std::unique_ptr<logger::BaseLogger>&& logger) {
        base_logger = std::move(logger);
    }

    Logger::Logger()
            : base_logger(std::make_unique<StdoutLogger>()) {}


}