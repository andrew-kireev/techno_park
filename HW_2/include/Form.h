//
// Created by Andrew Kireev on 27.03.2020.
//

#ifndef LOG_FORM_H
#define LOG_FORM_H

#include <string>
#include <iostream>
#include "Level.h"



#define RED     "\033[31m"
#define RESET   "\033[0m"
#define BOLDBLACK   "\033[1m\033[30m"
#define YELLOW  "\033[33m"      /* Bold Green */
#define BOLDCYAN    "\033[1m\033[36m"

namespace logger {

    class Form {
    public:
        Form(std::string msg, Level lvl);

        friend std::ostream& operator<<(std::ostream& str, const Form& fr) {
            if (fr.get_lvl() == Level::ERROR) {
                std::cout << RED << "ERROR: " << RESET << fr.get_msg() << std::endl;
            } else if (fr.get_lvl() == Level::DEBUG) {
                std::cout << BOLDBLACK << "DEBUG: " << RESET << fr.get_msg() << std::endl;
            } else if (fr.get_lvl() == Level::WARN) {
                std::cout << YELLOW << "WARN: " << RESET << fr.get_msg() << std::endl;
            } else if (fr.get_lvl() == Level::INFO) {
                std::cout << BOLDCYAN << "INFO: " << RESET << fr.get_msg() << std::endl;
            }
            return str;
        }

        Level get_lvl() const;

        std::string get_msg() const;


    private:
        std::string msg_;
        Level lvl_;
    };

}

#endif //LOG_FORM_H
