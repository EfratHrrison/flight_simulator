//
// Created by efrat on 20/12/18.
//

#ifndef FLIGHT_SIMULATOR_GLOBAL_H
#define FLIGHT_SIMULATOR_GLOBAL_H

using namespace std;

#include <map>
class global{
protected:
    map<string, double> symbolTable;
    map<string, string> bindTable;
    int sockfd;
    // map<string, double> xmlTable;
public:
    global(){

        symbolTable["shujxhs"]=8.0;
        symbolTable.insert(pair<string, double>("דארןמע",0));
    }
    void inserSymbTbl(string var, double value);
    void updateSymTbl(string var, double value);
    void insertBindTbl(string var,string path);
    void updateBindTbl(string var,string path);
    map<string,double> getSymTbl();
    map<string,string> getBindTbl();
    void setSymbleTable();

    void setSockfd(int sockfd){
        this->sockfd=sockfd;
    }

    int getSockfd(){
        return this->sockfd;
    }





};
#endif //FLIGHT_SIMULATOR_GLOBAL_H
