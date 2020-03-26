//
// Created by Andrew Kireev on 10.03.2020.
//


#include "process.h"
#include <unistd.h>
#include <csignal>
#include <cstring>
#include <iostream>


namespace process{

    Process::Process(const std::string &path) {
        int pipefd_1[2];
        int pipefd_2[2];
         if(pipe(pipefd_1) == -1){
                throw std::runtime_error("Ошибка создания pipe1");
         }

        if(pipe(pipefd_2) == -1){
            ::close(pipefd_1[0]);
            ::close(pipefd_1[1]);
            throw std::runtime_error(std::strerror(errno));
        }

        if((pid = fork()) == -1){
            throw std::runtime_error("Ошибка создания дочнрнего процесса");
        } else if(pid == 0) {
            std::cout << "Child PID: " << getpid() << std::endl;
            dup2(pipefd_1[1], STDOUT_FILENO);
            ::close(pipefd_1[1]);
            ::close(pipefd_1[0]);           //Возможно нужно удалить
            dup2(pipefd_2[0], STDIN_FILENO);
            ::close(pipefd_2[1]);
            ::close(pipefd_2[0]);
            in_is_readable = true;
            if(execl(path.c_str(), path.c_str(), NULL) < 0){
                std::cerr << ("Ошибка подмены программы") << std::endl;
            }
        } else{
            //parent
            std::cout << "Parent PID: " << getpid() << std::endl;
            stdin_ = pipefd_1[0];
            stdout_ = pipefd_2[1];
            in_is_readable = true;
        }
    }


    Process::~Process(){
        close();
        kill(pid, SIGCHLD);
        waitpid(pid, nullptr, WUNTRACED);
    }

    std::size_t Process::write(const void *data, std::size_t len) {
        ssize_t bytes = ::write(stdout_, data, len);
        return static_cast<size_t>(bytes);
    }

    void Process::writeExact(const void *data, size_t len) {
        ssize_t wr = 0, last_it = 0;
        while (wr != len) {
            wr += static_cast<std::size_t>(write(static_cast<const char*>(data) + wr, len - wr));
            if (wr == last_it) {
                throw std::runtime_error("Полученно недостаточное количество байт для записи");
            }
            last_it = wr;
        }
        fflush(stdout);
    }

    std::size_t Process::read(void *data, std::size_t len) {
        if (in_is_readable == false){
            throw std::runtime_error("Дескриптор вывода закрыт");
        }

        ssize_t bytes = ::read(stdin_, data, len);
        if (bytes == 0) {
            in_is_readable = false;
        } else if (bytes < 0) {
            std::cerr << "Метод ничего не смог прочитать" << std::endl;
        }
        return static_cast<std::size_t>(bytes);
    }

    void Process::readExact(void *data, size_t len) {
        if (in_is_readable == false){
            throw std::runtime_error("Дескриптор вывода закрыт");
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
        return in_is_readable;
    }

    void Process::closeStdin() {
        in_is_readable = false;
        ::close(stdin_);
    }

    void Process::close() {
        ::close(stdout_);
        ::close(stdin_);
        in_is_readable = false;
    }
}

