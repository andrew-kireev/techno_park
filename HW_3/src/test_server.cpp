//
// Created by Andrew Kireev on 30.03.2020.
//
#include <iostream>
#include <exception.h>

#include "Server.h"

int main() {
    server::Server sr("192.168.2.246", 1231);
    sr.set_max_connection(3);
    server::Connection con(sr.accept());
    con.set_timeout(10);
    std::string data;
    while (con.is_opened())
    {
        try {
            size_t size;
            con.recv_size(size);
            data.resize(size);
            con.readExact(data.data(), size);
            con.send_size(size);
            con.writeExact(data.data(), size);
        } catch (server::TcpException& er){
            std::cerr << er.what() << std::endl;
            break;
        }

        std::cout << "Получено: " << data << std::endl;
    }

    return 0;
}
