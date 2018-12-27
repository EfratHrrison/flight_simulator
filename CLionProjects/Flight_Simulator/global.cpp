//
// Created by efrat on 20/12/18.
//

#include "global.h"
#include "iostream"

using namespace std;

void global::inserSymbTbl(string var, double value) {
    pthread_mutex_lock(&mutex);
    symbolTable.insert(pair<string, double>(var, value));
    pthread_mutex_unlock(&mutex);
}

void global::inserSymbTbl1(string var, double value) {
    symbolTable.insert(pair<string, double>(var, value));
}

double global::getValueSymbTbl(string var) {
    pthread_mutex_lock(&mutex);
    for (auto item: bindTable) {
        if (item.first == var) {
            for (auto item1 :xmlTable) {
                if (item.second == item1.first) {
                    pthread_mutex_unlock(&mutex);
                    return item1.second;
                }
            }
        }
    }
    for (auto item: symbolTable) {
        if (item.first == var) {
            pthread_mutex_unlock(&mutex);
            return item.second;
        }
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}

bool global::isVar(string var) {
    pthread_mutex_lock(&mutex);
    for (auto item: bindTable) {
        if (item.first == var) {
           pthread_mutex_unlock(&mutex);
            return true;
        }
    }
    for (auto item: symbolTable) {
        if (item.first == var) {
           pthread_mutex_unlock(&mutex);
            return true;
        }
    }
    pthread_mutex_unlock(&mutex);
    return false;
}

// לבדוק את זה
void global::updateSymTbl() {
  //  pthread_mutex_lock(&mutex);
    for (auto item : xmlTable) {
        for (auto item1 : bindTable) {
            if (item.first == item1.second) {
                inserSymbTbl(item1.first, item.second);
            }
        }
    }
   // pthread_mutex_unlock(&mutex);
}

void global::setXMLTable(string str, double number) {
    pthread_mutex_lock(&mutex);
    xmlTable[str] = number;
    //cout<< number + ' ';
    pthread_mutex_unlock(&mutex);
}

void global::insertVarBind(string var, string newVar) {
     pthread_mutex_lock(&mutex);
    for (auto item : bindTable) {
        if (item.first == var) {
            insertBindTbl(newVar, item.second);
        }
    }
    for (auto item1 : symbolTable) {
        if (item1.first == var) {
            inserSymbTbl(newVar, item1.second);
        }
    }
      pthread_mutex_unlock(&mutex);
}

string global::OPgetVarBindTbl(string var) {
    pthread_mutex_lock(&mutex);
    for (auto item : bindTable) {
        if (item.first == var) {
            string path = item.second;
            path = removeSubstrs(path, "\"");
            int i = 0;
            for (auto c:path) {
                if (c == '/') {
                    path.erase(0, i + 1);
                    break;
                }
                i++;
            }
            pthread_mutex_unlock(&mutex);
            return path + ' ';
        }
    }
    pthread_mutex_unlock(&mutex);
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
    pthread_mutex_lock(&mutex);
    bindTable.insert(pair<string, string>(var, path));
    for (auto item : xmlTable) {
        if (item.first == path) {
            inserSymbTbl1(var, item.second);
        }
    }
    pthread_mutex_unlock(&mutex);
}