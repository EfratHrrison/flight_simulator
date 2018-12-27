//
// Created by neta on 12/19/18.
//

#ifndef FLIGHT_SIMULATOR_VARCOMMAND_H
#define FLIGHT_SIMULATOR_VARCOMMAND_H
#include "vector"
#include "Command.h"
#include "EvaluateExp.h"
#include "global.h"

using namespace std;
class varCommand : public Command {
    global *glob;
public:
    varCommand(global *global1){
        this->glob=global1;
    }
    void execute(const std::vector<std::string> ve);
    void doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition) {}
    void sendMessage(string str);

};
#endif //FLIGHT_SIMULATOR_VARCOMMAND_H
