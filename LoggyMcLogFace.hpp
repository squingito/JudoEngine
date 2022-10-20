//
// Created by squin on 10/15/2022.
//

#ifndef JUDO_ENGINE_LOGGYMCLOGFACE_HPP
#define JUDO_ENGINE_LOGGYMCLOGFACE_HPP

#include <cstdint>
#include <fstream>
#include <ostream>
#include <time.h>

#define LOG_READY 0x80000000
#define LOG_NOT_READY_ERROR -4
#define NOT_VALID_FUNCTION_VAR -5
#define FUNCTION_NEVER_DEFINED -6
#define MORE_VALUES_THEN_FUNCTION_CALLS -7
#define LESS_VALUES_THEN_FUNCTION_CALLS -8

class LoggyMcLogFace {
public:
    LoggyMcLogFace(char*, char* t_extention);
    ~LoggyMcLogFace();
    void addInterpreter(char, void (*t_function)(std::ofstream*, void*));
    int32_t log(char*, void**, int32_t);

private:
    std::ofstream m_file;
    char m_directory[256] = {0};
    int32_t m_valid_functions;
    void (*m_functions[26])(std::ofstream*, void*);
    char m_extention[4] = {0};

};


#endif //JUDO_ENGINE_LOGGYMCLOGFACE_HPP
