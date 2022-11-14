#include "judge.h"
#include "test.h"
#include "input.h"
#include <sys/types.h>
#include <dirent.h>

Input input;
Test test;
All_program programs;
Machine_Judge machine_judge;

static void get_filenames(string path, vector<string> &fs) {
    DIR* pDir;
    dirent* ptr;
    pDir = opendir((char *)path.c_str());
    while((ptr = readdir(pDir))) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            fs.push_back(path + "/" + ptr->d_name);
    }
    closedir(pDir);
}

int main() {

    vector<string> fs;
    get_filenames("./input", fs);
    system("rm -rf ./output");

    for(auto x : fs) {  
        input.init();

        programs.init();
        input.Read_OJ_program((char *)x.c_str(), programs);
        
        string addr = x + "/stdin_format.txt";
        input.Generate_test((char *)addr.c_str(), 20);

        machine_judge.Judge(test, programs);
        system("rm -rf ./test");
    }

    return 0;
}