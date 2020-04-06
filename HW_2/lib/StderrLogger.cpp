//
// Created by Andrew Kireev on 26.03.2020.
//

#include "StderrLogger.h"
#include "Form.h"

namespace logger{

    void StderrLogger::flush(){
        std::cerr.flush();
    }

    void StderrLogger::log(const std::string &str, Level lvl) {
        if (level() <= lvl) {
            std::cerr << Form(str, lvl) << std::endl;
        }
        flush();
    }

}