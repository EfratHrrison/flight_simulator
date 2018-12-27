//
// Created by neta on 12/18/18.
//

#ifndef FLIGHT_SIMULATOR_COMMAND_H
#define FLIGHT_SIMULATOR_COMMAND_H
#include "Expression.h"
#include "string"

#include "vector"
#include "unordered_map"
using std::string;

class Command {
public:
    virtual void execute(const std::vector<std::string> ve)=0;
    virtual ~Command() = default;
    virtual void doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition)=0;
};

#endif //FLIGHT_SIMULATOR_COMMAND_H
