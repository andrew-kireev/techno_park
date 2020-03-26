//
// Created by Andrew Kireev on 10.03.2020.
//

#ifndef PROCESS_PROCESS_H
#define PROCESS_PROCESS_H


#include <string>

namespace process{

    class Process {
    public:
        explicit Process(const std::string &path);

        ~Process();

        size_t write(const void *data, size_t len);

        void writeExact(const void *data, size_t len);

        size_t read(void *data, size_t len);

        void readExact(void *data, size_t len);

        bool isReadable() const;

        void closeStdin();

        void close();

    private:
        pid_t pid;
        int stdin_, stdout_;
        bool in_is_readable;
    };
}
#endif //PROCESS_PROCESS_H
