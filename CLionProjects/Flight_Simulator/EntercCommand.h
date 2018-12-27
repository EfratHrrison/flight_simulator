//
// Created by efrat on 26/12/18.
//

#ifndef FLIGHT_SIMULATOR_ENTERCCOMMAND_H
#define FLIGHT_SIMULATOR_ENTERCCOMMAND_H
#include<unistd.h>
#include "Command.h"
#include <chrono>
#include <thread>
#include "global.h"
using namespace std;

class EntercCommand : public Command {
    global *glob;
public:
    EntercCommand(global *glob){
        this->glob = glob;
    }
    void execute(const std::vector<std::string> ve);
    void doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition);
};
#endif //FLIGHT_SIMULATOR_ENTERCCOMMAND_H
