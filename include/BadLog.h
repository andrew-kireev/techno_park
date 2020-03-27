//
// Created by Andrew Kireev on 23.03.2020.
//

#ifndef LOG_BADLOG_H
#define LOG_BADLOG_H

#include <exception>
#include <string>

namespace logger {

    class BadLog : std::exception{
    public:
        BadLog(std::string& msg) : str(std::move(msg)){}
        const char* what() const noexcept {
            return str.c_str();
        }
    private:
        std::string str;
    };

}

#endif //LOG_BADLOG_H
