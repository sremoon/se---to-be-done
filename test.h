#include "program.h"

class Test {
    public:
        void compile_all(All_program& Programs) {
            char cmd[500];
            int l = Programs.program_num();
            for(int i = 1; i <= l; i ++) {
                sprintf(cmd, "g++ %s -O2 -o test/%d.out", Programs.program_name(i), i);
                system(cmd);
            }
        }
        int test_pair(int Ti, int Tj) {
            char cmd[500];
            bool gg = 0;
            for(int i = 1; i <= 100; i ++) {
                sprintf(cmd, "timeout 2s ./%d.out < %d.in > /test/left%d.ans", Ti, i, i);
                system(cmd);
                sprintf(cmd, "timeout 2s ./%d.out < %d.in > /test/right%d.ans", Tj, i, i);
                system(cmd);
                sprintf(cmd, "diff /test/left%d.ans /test/right%d.ans", i, i);
                if(system(cmd)) gg = 1;
                sprintf(cmd, "rm /test/left%d.ans");
                system(cmd);
                sprintf(cmd, "rm /test/right%d.ans");
                system(cmd);
                if(gg) return 0;
            }
            for(int i = 1; i <= 100; i ++) {
                sprintf(cmd, "timeout 2s ./%d.out < %d.in > right%d.ans", Ti, i, i);
                system(cmd);
            }
            return 1;
        }
} ;