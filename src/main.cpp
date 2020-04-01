//
// Created by Andrew Kireev on 10.03.2020.
//
#include "process.h"
#include <iostream>
#include <string>


int main (int argc, char * argv[])
{
    try {
        process::Process pr("/bin/cat");
        std::string in = "privet";
        std::string out;

        pr.writeExact(in.data(), in.size());
        out.resize(in.size());
        pr.readExact(out.data(), out.size());
        std::cout << out << std::endl;



        if (argc < 2) {
            throw std::runtime_error("Недостаточное количество аргуметнов");
        }
        process::Process proc(argv[1]);       //  "/bin/cat"
        while (!in.empty() || in == "^D") {
            in.clear();
            std::cin >> in;
            out.resize(in.size());
            proc.writeExact(in.data(), in.size());
            ssize_t byte = 0;
            ssize_t to_read = in.size();
            while (to_read != 0 && (byte = proc.read(out.data(), 4096)) > 0 && proc.isReadable()) {
                std::cout << out << std::endl;
                out.clear();
                to_read = in.size() - byte;
            }
        }
    }catch (std::runtime_error& er) {
        std::cerr << er.what() << std::endl;
    }
    return 0;
}
