//
// Created by neta on 12/19/18.
//

#ifndef FLIGHT_SIMULATOR_CONNECTCOMMAND_H
#define FLIGHT_SIMULATOR_CONNECTCOMMAND_H
#include "vector"
#include "Command.h"

using namespace std;
class connectCommand : public Command {
    Command *c;
public:
    connectCommand() = default;
    void execute(const std::vector<std::string> ve) {
        //לבדוק תקינות
    }
    void doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition) {}

};


#endif //FLIGHT_SIMULATOR_CONNECTCOMMAND_H
