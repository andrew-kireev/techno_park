//
// Created by Andrew Kireev on 10.03.2020.
//


#include "/Users/andrewkireev/CLionProjects/Process/include/process.h"

Process::Process(const std::string& path) : is_readable(true){
    if(pipe(pipefd_1)!=0) {
        perror("Pipe_1");
    }
    if(pipe(pipefd_2)!=0) {
        perror("Pipe_2");
    }
    pid = fork();
    switch(pid) {
        case -1:
            perror("fork\n");
            break;
        case 0: {
            child_pid = getpid();
            dup2(pipefd_1[1],1);
            ::close(pipefd_1[1]);
            ::close(pipefd_1[0]);
            dup2(pipefd_2[0],0);
            ::close(pipefd_2[0]);
            ::close(pipefd_2[1]);
            fprintf(stderr, "Child PID: %i\n", getpid());
            execl(path.c_str(),"1");
            break;
        }
        default:{
            //parent

            dup2(pipefd_2[1], 1);
            ::close(pipefd_2[1]);
            ::close(pipefd_2[0]);
            dup2(pipefd_1[0], 0);
            ::close(pipefd_1[1]);
            ::close(pipefd_1[0]);
            fprintf(stderr,"Parent PID: %i\n",getpid());
            break;
        }

    }
}
Process::~Process(){
    kill(child_pid, SIGCHLD);
    waitpid(child_pid, 0 ,WUNTRACED);
}

size_t Process::write(const void* data, size_t len){
    size_t writenByts = ::write(STDOUT_FILENO, data, len);
    fflush(stdout);
    return writenByts;
}
void Process::writeExact(const void* data, size_t len){
    ::write(STDOUT_FILENO,data, len);
    fflush(stdout);
}
size_t Process::read(void* data, size_t len) {
    return ::read(STDIN_FILENO,data,len);
}
void Process::readExact(void* data, size_t len) {
    ::read(STDOUT_FILENO, data, len);
}
bool Process::isReadable() const{
    return is_readable;
}
void Process::closeStdin(){
    is_readable = false;
    ::close(STDIN_FILENO);
}

void Process::close(){
    ::close(STDOUT_FILENO);
    ::close(STDIN_FILENO);
}



