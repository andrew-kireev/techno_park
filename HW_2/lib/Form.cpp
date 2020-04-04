//
// Created by Andrew Kireev on 27.03.2020.
//

#include "Form.h"

#include <utility>


namespace logger {

    Form::Form(std::string msg, logger::Level lvl) :msg_(std::move(msg)), lvl_(lvl){}

    Level Form::get_lvl() const {
        return lvl_;
    }

    std::string Form::get_msg() const {
        return msg_;
    }

}