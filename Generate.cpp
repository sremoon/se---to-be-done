#include <bits/stdc++.h>
using namespace std;

// name is the relative address of the input_format
// T is the testcase we generate
void Generate_test(char* input_file, int T) {
    int nT = 0;
    char buf[25555];
    while(T --) {
        FILE* format, test;
        if((format = fopen(input_file, "r")) == NULL) {
            cerr << "Generate_test : Input_format does not exists" << endl;
            return;
        }
        char test_name[500];
        sprintf(test_name, "/test/%d.in", nT);
        test = fopen(test_name, "w");
        // You should garantee single line does not overload 25000 charecters
        while(fgets(buf, 25000, (FILE*)format)) {
        }
    }
}