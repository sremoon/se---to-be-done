#include "judge.h"
#include "test.h"
#include "input.h"

Input input;
Test test;
All_program programs;
Machine_Judge machine_judge;

int main() {
    
    input.init();
    input.Read_OJ_program((char *)"./input", programs);
    input.Generate_test((char *)"./input/stdin_format.txt", 100);

    printf("---------> %s\n", programs.file_name(2));

    machine_judge.Judge(test, programs);

    system("rm -rf ./test");
    return 0;
}