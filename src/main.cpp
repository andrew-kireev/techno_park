//
// Created by Andrew Kireev on 10.03.2020.
//
#include "process.h"
#include <iostream>


int main (int argc, char * argv[])
{

    process::Process pr("");
    const char data[6] = {'p', 'r', 'i', 'v', 'e', 't'};
    char new_data[6];



    pr.write(data,6 );
    pr.read(new_data, 6);
    for(int i = 0; i < 6; ++i){
        std::cout << new_data[i];
    }

    return 0;
}
