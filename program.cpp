#include "program.h"

Program::Program(char *name) {
    strcpy(_name, name);
    char* fname = name;
    while(*fname != '/') fname ++; fname ++; // ./
    while(*fname != '/') fname ++; fname ++; // input/
    strcpy(_fname, fname);
}

char* Program::name() { return _name; }
char* Program::fname() { return _fname; }

All_program::All_program() {
    _ap.clear();
}

void All_program::init() {
    _ap.clear();
}

int All_program::program_num() { return _ap.size(); }

char* All_program::program_name(int T) {
    if(T > program_num()) {
        cerr << "Error : Try to attach an unexist program" << endl;
        return "";
    } 
    return _ap[T - 1].name();
}

char* All_program::file_name(int T) {
    if(T > program_num()) {
        cerr << "Error : Try to attach an unexist program" << endl;
        return "";
    } 
    return _ap[T - 1].fname();
}

void All_program::add_program(char *name) {
    _ap.push_back(Program(name));
}