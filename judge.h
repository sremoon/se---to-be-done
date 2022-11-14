#ifndef _SE_JUDGE_
#define _SE_JUDGE_
#include "program.h"
#include "test.h"

class Machine_Judge {
    private:
    public:
        Machine_Judge() {}
        void Judge(Test &tt, All_program &Programs) {
            tt.compile_all(Programs);
            int l = Programs.program_num();
            system("mkdir output");
            FILE *equal = fopen("./output/equal.csv", "a");
            FILE *inequal = fopen("./output/inequal.csv", "a");
            FILE *abnormal = fopen("./output/abnormal.csv", "a");
            bool eq = 0;
            bool ineq = 0;
            for(int i = 1; i <= l; i ++) for(int j = i + 1; j <= l; j ++) {
                char cmd[500];
                sprintf(cmd, "%s,%s\n", Programs.file_name(i), Programs.file_name(j));
                if(tt.test_pair(i, j) == 1) fputs(cmd, equal);
                else fputs(cmd, inequal);
            }
            fclose(equal);
            fclose(inequal);
            fclose(abnormal);
        }
} ;

#endif