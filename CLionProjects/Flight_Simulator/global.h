//
// Created by efrat on 20/12/18.
//

#ifndef FLIGHT_SIMULATOR_GLOBAL_H
#define FLIGHT_SIMULATOR_GLOBAL_H
#include <pthread.h>
using namespace std;

#include "vector"
#include <map>
class global {
protected:
    mutable pthread_mutex_t mutex;
    map<string, double> symbolTable;
    map<string, string> bindTable;
    map<string,double> xmlTable;
    vector <string> vars;
    string ins;
    int sockfd;
public:
    global(){
        initXML();
    }

    void initXML() {
        this->vars.push_back("/instrumentation/airspeed-indicator/indicated-speed-kt");
        this->vars.push_back("/instrumentation/altimeter/indicated-altitude-ft");
        this->vars.push_back("/instrumentation/altimeter/pressure-alt-ft");
        this->vars.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg");
        this->vars.push_back("/instrumentation/attitude-indicator/indicated-roll-deg");
        this->vars.push_back("/instrumentation/attitude-indicator/internal-pitch-deg");
        this->vars.push_back("/instrumentation/attitude-indicator/internal-roll-deg");
        this->vars.push_back("/instrumentation/encoder/indicated-altitude-ft");
        this->vars.push_back("/instrumentation/encoder/pressure-alt-ft");
        this->vars.push_back("/instrumentation/gps/indicated-altitude-ft");
        this->vars.push_back("/instrumentation/gps/indicated-ground-speed-kt");
        this->vars.push_back("/instrumentation/gps/indicated-vertical-speed");
        this->vars.push_back("/instrumentation/heading-indicator/indicated-heading-deg");
        this->vars.push_back("/instrumentation/magnetic-compass/indicated-heading-deg");
        this->vars.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
        this->vars.push_back("/instrumentation/turn-indicator/indicated-turn-rate");
        this->vars.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
        this->vars.push_back("/controls/flight/aileron");
        this->vars.push_back("/controls/flight/elevator");
        this->vars.push_back("/controls/flight/rudder");
        this->vars.push_back("/controls/flight/flaps");
        this->vars.push_back("/controls/engines/current-engine/throttle");
        this->vars.push_back("/engines/engine/rpm");
    }

    void updateXML(string string1, double value);

    bool isVar(string var);

    void inserSymbTbl1(string var, double value);

    void inserSymbTbl(string var, double value);

    string removeSubstrs(string s, string p);

    void updateSymTbl();

    double getValueSymbTbl(string var);

    void insertBindTbl(string var,string path);

    void insertVarBind(string var, string newVar);

    string OPgetVarBindTbl(string var);

    void updateBindTbl(string var,string path);

    map<string,double> getSymTbl();

    void setXMLTable(string s , double d );

    void setSockfd(int sockfd) {
        this->sockfd=sockfd;
    }

    int getSockfd(){
        return this->sockfd;
    }

    void setIns(string inst){
      //  pthread_mutex_lock(&mutexIns);
        this->ins=inst;
        //pthread_mutex_unlock(&mutexIns);
    }
    vector <string> getVars() {
        return this->vars;
    }
    string getIns(){
        return this->ins;
    }
};
#endif //FLIGHT_SIMULATOR_GLOBAL_H
