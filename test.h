#ifndef _SE_TEST_
#define _SE_TEST_
#include "program.h"

class Test {
    public:
        Test() {}
        void compile_all(All_program& Programs) {
            char cmd[500];
            int l = Programs.program_num();
            for(int i = 1; i <= l; i ++) {
                sprintf(cmd, "g++ %s -o ./test/%d.out", Programs.program_name(i), i);
                system(cmd);
            }
        }
        int test_pair(int Ti, int Tj) {
            char cmd[500];
            bool gg = 0;
            for(int i = 1; i <= 20; i ++) {
                sprintf(cmd, "timeout 2s ./test/%d.out < ./test/%d.in > ./test/left%d.ans", Ti, i, i);
                system(cmd);
                sprintf(cmd, "timeout 2s ./test/%d.out < ./test/%d.in > ./test/right%d.ans", Tj, i, i);
                system(cmd);
                sprintf(cmd, "diff ./test/left%d.ans ./test/right%d.ans > ./test/log.txt", i, i);
                if(system(cmd)) gg = 1;
                sprintf(cmd, "rm ./test/left%d.ans", i);
                system(cmd);
                sprintf(cmd, "rm ./test/right%d.ans", i);
                system(cmd);
                if(gg) return 0;
            }
            return 1;
        }
} ;

#endif