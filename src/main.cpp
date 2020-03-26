//
// Created by Andrew Kireev on 10.03.2020.
//
#include "process.h"
#include <iostream>
#include <string>


int main (int argc, char * argv[])
{

    process::Process pr("/bin/pwd");
    const char *data = "privet";
    char new_data[100];

    pr.writeExact(data,3 );
    pr.readExact(new_data, 50);
    std::string str = new_data;

    std::cout << str << std::endl;

    return 0;
}
