#include <iostream>
using namespace std;

long long read_int(char* &now) {
    long long ret = 0;
    while(*now > '9' || *now < '0') now ++;
    while(*now >= '0' && *now <= '9') ret = ret * 10 + *now - '0', now ++;
    return ret;
}

long long rnd(long long a, long long b) {
    if(a > b) {
        swap(a, b);
        cerr << "Input_format Wrong with b > a" << endl;
        return 0;
    }
    long long w = rand() % (b - a + 1) * rand() % (b - a + 1);
    return w + a;
}

// input_file is the relative address of the input_format
// T is the testcase we generate
void Generate_test(char* input_file, int T) {
    srand(time(0));
    int nT = 0;
    char buf[1005], test_name[50], number_buf[50];
    if(T > 0) system("mkdir test");
    while(T --) {
        FILE* format, *test;
        if((format = fopen(input_file, "r")) == NULL) {
            cerr << "Generate_test : Input_format(" << input_file << ") does not exists" << endl;
            return;
        }
        sprintf(test_name, "./test/%d.in", ++ nT);
        cout << test_name << endl;
        test = fopen(test_name, "w");
        // You should garantee single line does not overload 25000 charecters
        while(fgets(buf, 1000, (FILE*)format)) {
            char* now = buf;
            bool not_blank = 0;
            while(1) {
                while(*now == ' ' || *now == '\r' || *now == '\n') now ++;
                if(*now == '\0') { 
                    if(not_blank) fputc('\n', test); 
                    break; 
                }
                not_blank = 1;
                if(*now == 'i') {
                    long long a = read_int(now);
                    long long b = read_int(now);
                    long long w = rnd(a, b);
                    sprintf(number_buf, "%lld ", w);
                    fputs(number_buf, test);
                    
                    while(*now != ')') now ++; 
                }
                else if(*now == 'c') {
                    int b = rnd(0, 1), c;
                    if(b == 0) c = rnd(0, 25) + 'a';
                    else c = rnd(0, 25) + 'A';
                    fputc(c, test); fputc(' ', test); 
                    while(*now != 'r') now ++;
                }
                else if(*now == 's') {
                    long long a = read_int(now);
                    long long b = read_int(now);
                    long long l = rnd(a, b);
                    while(l --) { 
                        int b = rnd(0, 1), c;
                        if(b == 0) c = rnd(0, 25) + 'a';
                        else c = rnd(0, 25) + 'A';
                        fputc(c, test); 
                    }
                    fputc(' ', test); 
                    while(*now != ')') now ++;
                }
                else {
                    cerr << "Input_format Wrong !" << endl;
                    fclose(format);
                    fclose(test);
                    return;
                }
                now ++;
            }
        }
        fclose(format);
        fclose(test);
    }
}