//
// Created by Andrew Kireev on 10.03.2020.
//

#ifndef PROCESS_PROCESS_H
#define PROCESS_PROCESS_H

#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

class Process
{
public:
    explicit Process(const std::string& path);
    ~Process();
    size_t write(const void* data, size_t len);
    void writeExact(const void* data, size_t len);
    size_t read(void* data, size_t len);
    void readExact(void* data, size_t len);

    bool isReadable() const;
    void closeStdin();

    void close();
private:
    pid_t pid, child_pid;
    bool is_readable;
    int pipefd_1[2];
    int pipefd_2[2];
};


#endif //PROCESS_PROCESS_H
