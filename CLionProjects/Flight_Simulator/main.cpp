
#include "vector"

#include "Command.h"
#include "ReadData.h"
#include <fstream>
#include "iostream"
#include "cstring"

using namespace std;

int main(int argc, char* argv[]) {
    ReadData *read1 = new ReadData();
    string line="";
    ifstream myfile (argv[1]);
    string while1 = "while";
    string if1 = "if";
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line.empty()) {
                continue;
            }
            if(strstr(line.c_str(),while1.c_str()) || strstr(line.c_str(),if1.c_str())) {
                read1->lexerCndition(line, myfile);
            }
            else {
                read1->Lexer(line);
            }
        }
        myfile.close();
    }
    while(true);
    //return 0;
}




