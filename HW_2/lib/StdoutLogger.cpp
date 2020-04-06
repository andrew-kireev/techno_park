//
// Created by Andrew Kireev on 26.03.2020.
//

#include "StdoutLogger.h"
#include "Form.h"


namespace logger{

    void StdoutLogger::flush() {
        std::cout.flush();
    }

    void StdoutLogger::log(const std::string &str, Level lvl) {
        if (level() <= lvl) {
            std::cout << Form(str, lvl) << std::endl;
        }
        flush();
    }
}
