//
// Created by Andrew Kireev on 26.03.2020.
//

#include "Baselogger.h"

namespace logger {

    BaseLogger::BaseLogger() : level_(Level::DEBUG) {}

    void BaseLogger::debug(const std::string& str) {
        log(str, Level::DEBUG);
    }

    void BaseLogger::info(const std::string& str) {
        log(str, Level::INFO);
    }

    void BaseLogger::warn(const std::string& str) {
        log(str, Level::WARN);
    }

    void BaseLogger::error(const std::string& str) {
        log(str, Level::ERROR);
    }

    void BaseLogger::set_level(Level lvl) {
        level_ = lvl;
    }

    Level BaseLogger::level() const {
        return level_;
    }

}