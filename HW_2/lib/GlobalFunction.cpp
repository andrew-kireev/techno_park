//
// Created by Andrew Kireev on 26.03.2020.
//

#include "GlobalFunction.h"

namespace logger {


    std::unique_ptr<BaseLogger> create_stdout_logger() {
        return std::make_unique<StdoutLogger>();
    }

    std::unique_ptr<BaseLogger> create_stderr_logger() {
        return std::make_unique<StderrLogger>();
    }

    std::unique_ptr<BaseLogger>  create_file_logger(const std::string& path) {
        return std::make_unique<FileLogger>(path);
    }

    void debug(const std::string& str){
        std::unique_ptr<BaseLogger>& log = Logger::get_instance().get_global_logger();
        log->debug(str);
        log->flush();
    }

    void info(const std::string& str){
        std::unique_ptr<BaseLogger>& log = Logger::get_instance().get_global_logger();
        log->info(str);
        log->flush();
    }

    void warning(const std::string& str){
        std::unique_ptr<BaseLogger>& log = Logger::get_instance().get_global_logger();
        log->warn(str);
        log->flush();
    }

    void error(const std::string& str){
        std::unique_ptr<BaseLogger>& log = Logger::get_instance().get_global_logger();
        log->error(str);
        log->flush();
    }


}