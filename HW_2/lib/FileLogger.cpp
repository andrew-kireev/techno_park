//
// Created by Andrew Kireev on 26.03.2020.
//

#include "FileLogger.h"
#include "Form.h"


namespace logger{

    FileLogger::FileLogger() : file_("Log.txt") {
        if (!file_) {
            throw std::runtime_error("file open error");
        }
    }


    FileLogger::FileLogger(const std::string& path) : file_(path) {
        if (!file_) {
            throw std::runtime_error("file open error");
        }
    }


    void FileLogger::flush()  {
        file_.flush();
    }


    void FileLogger::log(const std::string& str, Level lvl) {
        if (level() <= lvl) {
            file_ << Form(str, lvl) << std::endl;
        }
        flush();
    }


}
