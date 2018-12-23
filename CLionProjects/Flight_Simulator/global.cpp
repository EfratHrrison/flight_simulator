//
// Created by efrat on 20/12/18.
//

#include "global.h"
#include "iostream"
using namespace std;

void global::inserSymbTbl(string var, double value) {
    symbolTable.insert(pair<string, double>(var,value));
}

void global::updateSymTbl(string var, double value) {
    symbolTable.find(var)->second=value;
}

void global::setXMLTable(vector<string> number) {
   for (int i = 0; i < vars.size(); ++i) {
       xmlTable[vars[i]]=stod(number[i]);

       string var=getVarBindTbl(vars[i]);
       inserSymbTbl(var,stod(number[i]));
    }
    for (map<string, double>::iterator it = xmlTable.begin(); it != xmlTable.end(); ++it) {
        cout << it->second << endl;
    }
}

string global::getVarBindTbl(string path){
    return bindTable.find(path)->second;
}

string global::OPgetVarBindTbl(string var){
for (map<string, string>::iterator it = bindTable.begin(); it != bindTable.end(); ++it)
    if (it->second==var) {
        string path=it->first;
        path.erase(0,2);
        path.erase(path.length()-1);
        return path+' ';
    }
}

void global::insertBindTbl(string var, string path) {
    bindTable.insert(pair<string,string>(var,path));
    for (map<string, string>::iterator it1 = bindTable.begin(); it1 != bindTable.end(); ++it1) {
        cout << it1->first << endl;
        cout << it1->second << endl;
    }
}

void global::updateBindTbl(string var, string path) {
    bindTable.find(var)->second=path;
}

map<string,double> global::getSymTbl(){
    return symbolTable;
}

//map<string,string> global::getBindTbl(){
//    return bindTable;
//}

//void global::initSymTbl(){
//
//}