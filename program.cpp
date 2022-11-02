#include "program.h"

Program::Program(char *name) {
    strcpy(_name, name);
}

char* Program::name() { return _name; }

All_program::All_program() {
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

void All_program::add_program(char *name) {
    _ap.push_back(Program(name));
}