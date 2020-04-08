//
// Created by Andrew Kireev on 10.03.2020.
//

#include "process.h"
#include <unistd.h>
#include <csignal>
#include <cstring>
#include <iostream>
#include <sys/wait.h>


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
            throw std::runtime_error("Ошибка создания pipe2");
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
            if (execl(path.c_str(), path.c_str(), NULL) < 0) {
                throw std::runtime_error("Ошибка подмена прогораммы");
            }
        } else{
            //parent
            std::cout << "Parent PID: " << getpid() << std::endl;
            stdin_ = pipefd_1[0];
            stdout_ = pipefd_2[1];
            in_is_readable = true;
        }
    }




    Process::~Process() noexcept{
        try {
            close();
            kill(pid, SIGTERM);
            waitpid(pid, nullptr, 0);
        } catch (std::runtime_error& er){
            std::cerr << "Ошибка закрытия дескриптора" << er.what() << std::endl;
        }
    }

    std::size_t Process::write(const void *data, std::size_t len) {
        ssize_t bytes = ::write(stdout_, data, len);
        if(bytes < 0){
            throw std::runtime_error("Write не смог ничего написать");
        }
        return bytes;
    }

    void Process::writeExact(const void *data, size_t len) {
        size_t wr = 0, last_it = 0;
        while (wr != len) {
            wr += write(static_cast<const char*>(data) + wr, len - wr);
            if (wr == last_it) {
                throw std::runtime_error("Полученно недостаточное количество байт для записи");
            }
            last_it = wr;
        }
    }

    std::size_t Process::read(void *data, std::size_t len) {
        if (in_is_readable == false){
            throw std::runtime_error("Дескриптор вывода закрыт");
        }

        ssize_t bytes = ::read(stdin_, data, len);
        if (bytes == 0) {
            in_is_readable = false;
        } else if (bytes < 0) {
            throw std::runtime_error("Метод ничего не смог прочитать");
        }
        return static_cast<std::size_t>(bytes);
    }

    void Process::readExact(void *data, size_t len) {
        if (in_is_readable == false){
            throw std::runtime_error("Дескриптор вывода закрыт");
        }

        size_t read = 0, last_it = 0;
        size_t num;
        while (read != len) {
            num = ::read(stdin_, static_cast<char *>(data) + read, len - read);
            read += num;
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
        if(::close(stdin_) < 0){
            throw std::runtime_error("Ошибка закрытия дескриптора");
        }
        stdin_ = -1;
        in_is_readable = false;
    }

    void Process::close() {
        if(::close(stdout_) < 0){
            throw std::runtime_error("Ошибка закрытия дескриптора");
        }
        closeStdin();
        stdout_ = -1;
    }
}

