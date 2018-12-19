//
// Created by neta on 12/5/18.
//
#include "Command.h"
#include "vector"
#include "DataReaderServer.h"
#include <thread>
#include "string"
#include <iostream>
#include <cstdlib>
#include "EvaluateExp.h"
#include <pthread.h>

#ifndef FLIGHT_SIMULATOR_OPENDATASERVERCOMMAND_H
#define FLIGHT_SIMULATOR_OPENDATASERVERCOMMAND_H
using namespace std;
struct MyParams {
    double port;
    double hz;
};

class openServerCommand : public Command {
    Command *openServer;

public:
    openServerCommand(){
    }

    void execute(std::vector<std::string> ve);

    void doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition);

};

#endif //FLIGHT_SIMULATOR_OPENDATASERVERCOMMAND_H