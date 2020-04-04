#include <iostream>


#include "Connection.h"

int main() {
    server::Connection con("192.168.2.246", 1226);
    std::string data(" ");
    while (!data.empty() || (data == "^D" && con.is_opened()))
    {
        data.clear();
        std::cin >> data;

        std::cout << "Отправлено: " << data << std::endl;
        con.send_size(data.size());
        con.writeExact(data.data(), data.size());

        size_t size;

        con.recv_size(size);
        con.readExact(data.data(), size);

        std::cout << "Получено: " << data << std::endl;
    }


    return 0;
}
