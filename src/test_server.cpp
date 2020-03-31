//
// Created by Andrew Kireev on 30.03.2020.
//
#include <iostream>

#include "../include/Server.h"

int main() {
    server::Server sr("342.0.0.1", 1211);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
