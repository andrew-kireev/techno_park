#include <iostream>


#include "../include/Connection.h"

int main() {
    server::Connection con("342.0.0.1", 1211);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
