//
// Created by efrat on 20/12/18.
//

#ifndef FLIGHT_SIMULATOR_GLOBAL_H
#define FLIGHT_SIMULATOR_GLOBAL_H

using namespace std;

#include "vector"
#include <map>
class global {
protected:
    map<string, double> symbolTable;
    multimap<string, string> bindTable;
    map<string,double> xmlTable;
    vector <string> vars;
    string ins;
    int sockfd;
    // map<string, double> xmlTable;
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
        this->vars.push_back("/instrumentation/gps/indicated-vertical-speed</node>");
        this->vars.push_back("/instrumentation/heading-indicator/indicated-heading-deg");
        this->vars.push_back("/instrumentation/magnetic-compass/indicated-heading-deg");
        this->vars.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
        this->vars.push_back("/instrumentation/turn-indicator/indicated-turn-rate");
        this->vars.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
        this->vars.push_back("/controls/flight/aileron");
        this->vars.push_back("controls/flight/rudder");
        this->vars.push_back("controls/flight/flaps");
        this->vars.push_back("controls/engines/engine/throttle");
        this->vars.push_back("/engines/engine/rpm");
    }

    void updateXML(string string1, double value);

    void inserSymbTbl(string var, double value);

    void updateSymTbl(string var, double value);

    void insertBindTbl(string var,string path);
    string OPgetVarBindTbl(string var);
    void updateBindTbl(string var,string path);

    map<string,double> getSymTbl();

    //map<string,string> getBindTbl();

    void setXMLTable(vector<string> number);

    string getVarBindTbl(string path);

    void setSockfd(int sockfd) {
        this->sockfd=sockfd;
    }

    int getSockfd(){
        return this->sockfd;
    }

    void setIns(string inst){
        this->ins=inst;
    }
    string getIns(){
        return this->ins;
    }






};
#endif //FLIGHT_SIMULATOR_GLOBAL_H
