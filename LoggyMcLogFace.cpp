//
// Created by squin, edited by boilermaker021 on 10/15/2022.
//

#include <cstring>
#include <sys/stat.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "LoggyMcLogFace.hpp"

LoggyMcLogFace::LoggyMcLogFace(const char* t_log_dir, const char* t_extention) {
    time_t t = time(NULL);
    char file_name[300] = {0};
    strncpy(m_directory, t_log_dir, 255);

    if (strlen(t_extention) <= 4) {
        strcpy(m_extention, t_extention);
    } else {
        strcpy(m_extention, ".log");
    }
    mkdir(m_directory, 0700);
    strcat(file_name, m_directory);
    strcat(file_name, "/");
    strcat(file_name, ctime(&t));
    strcat(file_name, m_extention);
    m_file.open(file_name, (std::ofstream::out));
    if (m_file.is_open()) {
        m_valid_functions |= LOG_READY;
    }
}

LoggyMcLogFace::~LoggyMcLogFace() {
    m_file.close();
}

void LoggyMcLogFace::addInterpreter(char t_letter, void (*t_function)(std::ofstream* , void *)) {
    if (t_letter <= 'z' && t_letter >= 'a') {
        m_functions[(t_letter - 'a')] = t_function;
        m_valid_functions |= (0x01 << (t_letter - 'a'));
    }
}

int32_t LoggyMcLogFace::log(const char* t_str, void** t_values, int32_t t_num_values) {
    if (m_valid_functions & LOG_READY) {
        int32_t pos = m_file.tellp();
        int32_t vars_used = 0;
        int32_t index = 0;
        time_t t;
        struct tm * t_struct;

        time(&t);
        t_struct = localtime(&t);
        m_file << '[' << t_struct->tm_hour << ':' << t_struct->tm_min << ':' << t_struct->tm_sec << "]- ";
        while (t_str[index] != '\0') {
            if (t_str[index] == '/') {
                if (t_str[index + 1] == '%') {
                    char fun = t_str[index + 2];
                    if (((fun - 'a') < 0) || ((fun - 'a') > 25)) {
                        m_file.seekp(pos);
                        return NOT_VALID_FUNCTION_VAR;
                    } else {
                        if (m_valid_functions & (0x01 << (fun - 'a'))) {
                            vars_used++;
                            if (vars_used > t_num_values) {
                                m_file.seekp(pos);
                                return MORE_VALUES_THEN_FUNCTION_CALLS;
                            }
                            index += 3;
                            m_functions[(fun - 'a')](&m_file, t_values[vars_used - 1]);
                            continue;
                        } else {
                            m_file.seekp(pos);
                            return FUNCTION_NEVER_DEFINED;
                        }
                    }
                }
            }
            m_file << t_str[index];
            index++;

        }
        if (t_num_values != vars_used) {
            m_file.seekp(pos);
            return LESS_VALUES_THEN_FUNCTION_CALLS;
        }
        m_file << "\n";
        return 0;
    }
    return LOG_NOT_READY_ERROR;
}

void pirnt(std::ofstream* a, void* in) {
    *a << *((int*) in);
}
/*


int main() {
    int u = 7;
    struct sockaddr_in a = {0};
    a.sin_addr.s_addr = htonl(0x88888888);

    void * ptr = &a;
    LoggyMcLogFace* thing = new LoggyMcLogFace("brungus", ".jr");
    thing->addInterpreter('a', read_ip);

    thing->log("hello there -/%a", &ptr, 1);

    delete thing;
}
*/