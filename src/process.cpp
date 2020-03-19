//
// Created by Andrew Kireev on 10.03.2020.
//


#include "../include/process.h"
#include <unistd.h>
#include <signal.h>
#include <iostream>

namespace process{

    Process::Process(const std::string &path) {
        int pipefd_1[2];
        int pipefd_2[2];
        pipe(pipefd_1);
        pipe(pipefd_2);
        pid = fork();
        if (pid == -1) {
            throw "Ошибка создания дочернего процесса";
        } else if(pid == 0) {
            dup2(pipefd_1[1], STDOUT_FILENO);
            stdout_ = pipefd_1[1];
            ::close(pipefd_1[1]);
            dup2(pipefd_2[0], STDIN_FILENO);
            stdin_ = pipefd_2[0];
            ::close(pipefd_2[1]);
            in_is_readable = true;
            out_is_readable = true;
            fprintf(stderr, "Child PID: %i\n", getpid());
            execl(path.c_str(), path.c_str(), NULL);
        } else{
            //parent
            stdin_ = pipefd_1[0];
            stdout_ = pipefd_2[1];
            in_is_readable = true;
            out_is_readable = true;
            fprintf(stderr, "Parent PID: %i\n", getpid());
        }
    }


    Process::~Process() {
        close();
        kill(pid, SIGCHLD);
        waitpid(pid, 0, WUNTRACED);
    }

    std::size_t Process::write(const void *data, std::size_t len) {
        if (out_is_readable == false){
            throw "Дескриптор ввода закрыт";
        }

        ssize_t bytes = ::write(stdout_, data, len);
//        if (static_cast<ssize_t>(bytes) < 0) {
//            std::cerr << "Метод ничего не смог написать" << std::endl;
//        }
        return static_cast<size_t>(bytes);
    }

    void Process::writeExact(const void *data, size_t len) {
        if (out_is_readable == false){
            throw "Дескриптор ввода закрыт";
        }

        ssize_t wr = 0, last_it = 0;
        while (wr != len) {
            wr += static_cast<std::size_t>(::write(stdout_, static_cast<const char*>(data) + wr, len - wr));
            if (wr == last_it) {
                throw std::runtime_error("Полученно недостаточное количество байт для записи");
            }
            last_it = wr;
        }
        fflush(stdout);
    }

    std::size_t Process::read(void *data, std::size_t len) {
        if (in_is_readable == false){
            throw "Дескриптор вывода закрыт";
        }

        ssize_t bytes = ::read(stdin_, data, len);
        if (!(bytes > 0)) {
            std::cerr << "Метод ничего не смог прочитать" << std::endl;
        }
        return static_cast<std::size_t>(bytes);
    }

    void Process::readExact(void *data, size_t len) {
        if (in_is_readable == false){
            throw "Дескриптор вывода закрыт";
        }

        std::size_t read = 0, last_it = 0;
        while (read != len) {
            read += static_cast<std::size_t>(::read(stdin_, static_cast<char *>(data) + read, len - read));
            if (read == last_it) {
                throw std::runtime_error("Полученно недостаточное количество байт для чтения");
            }
            last_it = read;
        }
    }

    bool Process::isReadable() const {
        return in_is_readable && out_is_readable;
    }

    void Process::closeStdin() {
        in_is_readable = false;
        ::close(stdin_);
    }

    void Process::close() {
        ::close(stdout_);
        ::close(stdin_);
        in_is_readable = false;
        out_is_readable = false;
    }
}

