//
// Created by efrat on 20/12/18.
//

#include "global.h"

using namespace std;
void global::inserSymbTbl(string var, double value) {
    symbolTable.insert(pair<string, double>(var,value));
}

void global::updateSymTbl(string var, double value) {
    symbolTable.find(var)->second=value;
}
void global::setSymbleTable() {
//    vector <string> vars;
//    for (int i = 0; i < vars.size(); ++i) {
//        symbolTable.insert(pair<string, double>(vars[i], 0));
//    }
}

void global::insertBindTbl(string var, string path) {
    bindTable.insert(pair<string,string>(var,path));
}

void global::updateBindTbl(string var, string path) {
    bindTable.find(var)->second=path;
}

map<string,double> global::getSymTbl(){
    return symbolTable;
}

map<string,string> global::getBindTbl(){
    return bindTable;
}

//void global::initSymTbl(){
//
//}