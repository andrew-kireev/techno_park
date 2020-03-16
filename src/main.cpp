//
// Created by Andrew Kireev on 10.03.2020.
//
#include "/Users/andrewkireev/CLionProjects/Process/include/process.h"

int main (int argc, char * argv[])
{
    {
        char echo[] = "/home/CLionProjects/echo/echo";
        Process process(echo);
        char buf1[128];
        process.write("Privet", 6);
        int r = process.read(buf1, 6);
        fprintf(stderr, "получил %i bytes: %s\n", r, buf1);
    }
    return 0;
}
