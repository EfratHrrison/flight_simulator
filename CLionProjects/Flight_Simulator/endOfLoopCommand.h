//
// Created by neta on 12/19/18.
//

#ifndef FLIGHT_SIMULATOR_ENDOFLOOPCOMMAND_H
#define FLIGHT_SIMULATOR_ENDOFLOOPCOMMAND_H

#include "Command.h"
#include "global.h"

using namespace std;
class endOfLoopCommand : public Command {
    global *glob;
public:
    endOfLoopCommand(global *global1){
        this->glob=global1;
    }
    void execute(std::vector<std::string> ve) {
    }
    void doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition) {}
};
#endif //FLIGHT_SIMULATOR_ENDOFLOOPCOMMAND_H
