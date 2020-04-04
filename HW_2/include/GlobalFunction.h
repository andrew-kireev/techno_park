//
// Created by Andrew Kireev on 24.03.2020.
//

#ifndef LOG_GLOBALFUNCTION_H
#define LOG_GLOBALFUNCTION_H

#include <memory>
#include <string>
#include "StderrLogger.h"
#include "StdoutLogger.h"
#include "FileLogger.h"
#include "Logger.h"


namespace logger {

    std::unique_ptr<BaseLogger> create_stdout_logger();

    std::unique_ptr<BaseLogger> create_stderr_logger();

    std::unique_ptr<BaseLogger>  create_file_logger(const std::string& path);

    void debug(const std::string& str);

    void info(const std::string& str);

    void warning(const std::string& str);

    void error(const std::string& str);

}

#endif //LOG_GLOBALFUNCTION_H
