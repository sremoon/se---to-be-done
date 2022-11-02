#include "program.h"
#include "test.h"

class Machine_Judge {
    private:
    public:
        void Judge(Test &tt, All_program &Programs) {
            tt.compile_all(Programs);
            int l = Programs.program_num();
            system("mkdir output");
            FILE *equal = fopen("/output/equal.csv", "w");
            FILE *inequal = fopen("/output/inequal.csv", "w");
            FILE *abnormal = fopen("/output/abnormal.csv", "w");
            for(int i = 1; i <= l; i ++) for(int j = i + 1; j <= l; j ++) {
                char cmd[500];
                sprintf(cmd, "%s,%s\n", Programs.program_name(i), Programs.program_name(j));
                if(tt.test_pair(i, j) == 1) fputs(cmd, equal);
                else fputs(cmd, inequal);
            }
            fclose(equal);
            fclose(inequal);
            fclose(abnormal);
        }
} ;