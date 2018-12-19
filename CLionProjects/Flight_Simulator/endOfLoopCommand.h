//
// Created by neta on 12/19/18.
//

#ifndef FLIGHT_SIMULATOR_ENDOFLOOPCOMMAND_H
#define FLIGHT_SIMULATOR_ENDOFLOOPCOMMAND_H

#include "Command.h"

using namespace std;
class endOfLoopCommand : public Command {
public:
    endOfLoopCommand(){
    }
    void execute(std::vector<std::string> ve) {
    }
    void doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition) {}
};
#endif //FLIGHT_SIMULATOR_ENDOFLOOPCOMMAND_H
