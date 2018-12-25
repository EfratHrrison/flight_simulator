//
// Created by efrat on 20/12/18.
//

#include "global.h"
#include "iostream"

using namespace std;

void global::inserSymbTbl(string var, double value) {
    symbolTable.insert(pair<string, double>(var,value));
}

double global::getValueSymbTbl(string var) {
  // pthread_mutex_lock(&mutexXml);
    for (auto item: symbolTable) {
        if (item.first == var) {
         //  pthread_mutex_unlock(&mutexXml);
            return item.second;
        }
    }
    //pthread_mutex_unlock(&mutexXml);
}

bool global::isVar(string var) {
  //  pthread_mutex_lock(&mutexXml);
    for (auto item: symbolTable) {

        if (item.first == var) {
           // pthread_mutex_unlock(&mutexXml);
            return true;
        }
    }
   //pthread_mutex_unlock(&mutexXml);
    return false;
}
// לבדוק את זה
void global::updateSymTbl() {
    //pthread_mutex_lock(&mutexXml);
    for (auto item : xmlTable) {
        for (auto item1 : bindTable) {
            if (item.first==item1.second) {
                inserSymbTbl(item1.first,item.second);
            }
        }
    }
    //pthread_mutex_unlock(&mutexXml);
}

void global::setXMLTable(vector<double> number) {
   for (int i = 0; i < 23; ++i) {
       xmlTable[vars[i]]=number[i];
    }
    updateSymTbl();
}

void global::insertVarBind(string var, string newVar) {
   // pthread_mutex_lock(&mutexXml);
    for (auto item : bindTable) {
       if (item.first== var) {
           insertBindTbl(newVar,item.second);
       }
    }
    for (auto item1 : symbolTable) {
        if (item1.first==var) {
            inserSymbTbl(newVar,item1.second);
        }
    }
  //  pthread_mutex_unlock(&mutexXml);
}

string global::OPgetVarBindTbl(string var) {
    for (auto item : bindTable) {
        if (item.first == var) {
            string path = item.second;
            path = removeSubstrs(path,"\"");
            int i=0;
            for (auto c:path){
                if (c=='/') {
                    path.erase(0,i+1);
                    break;
                }
                i++;
            }
            return path + ' ';
        }
    }
}

string global::removeSubstrs(string s, string p) {
    string::size_type n = p.length();
    for (string::size_type i = s.find(p);
         i != string::npos;
         i = s.find(p)) {
        s.erase(i, n);
    }
    return s;
}

void global::insertBindTbl(string var, string path) {
   // pthread_mutex_lock(&mutexXml);
    bindTable.insert(pair<string, string>(var,path));
    //pthread_mutex_unlock(&mutexXml);
}