#ifndef _SE_PROGRAM_
#define _SE_PROGRAM_

#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

class Program {
    private:
        char _name[102]; // the name
    public:
        Program(char* name) {};
        char* name();
};

class All_program {
    private:
        vector<Program> _ap;
    public:
        All_program() {};
        int program_num() {};
        char* program_name(int T) {};
        void add_program(char *name) {}; 
} ;

#endif