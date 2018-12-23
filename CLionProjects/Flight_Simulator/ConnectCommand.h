//
// Created by neta on 12/19/18.
//

#ifndef FLIGHT_SIMULATOR_CONNECTCOMMAND_H
#define FLIGHT_SIMULATOR_CONNECTCOMMAND_H
#include "vector"
#include "Command.h"
#include "global.h"
#include "EvaluateExp.h"
#include <pthread.h>
#include "DataReaderServer.h"
using namespace std;
struct ClientParams{
    string Ipaddress;
    int port;
    global *global1;
};
class ConnectCommand : public Command {
    Command *c;
    global *glob;
public:
    ConnectCommand(global *global1){
        this->glob=global1;
    }
    void execute(const std::vector<std::string> ve);

    static void* thread_func(void* arg);
    void doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition) {}

};


#endif //FLIGHT_SIMULATOR_CONNECTCOMMAND_H
