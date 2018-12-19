//
// Created by neta on 12/18/18.
//

#ifndef FLIGHT_SIMULATOR_COMMANDEXPRESSION_H
#define FLIGHT_SIMULATOR_COMMANDEXPRESSION_H
#include "vector"
#include "Expression.h"
#include "Command.h"
#include "unordered_map"
class CommandExpression: public Expression {
private:
    Command *c;
public:
    CommandExpression(Command *c) {
        this->c = c;
    }
    double calculate(std::vector<std::string> v) {
        c->execute(v);
    }
    virtual void doExectue(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition) {
        c->doCondition(mapOfCnd,condition);
    }


};

#endif //FLIGHT_SIMULATOR_COMMANDEXPRESSION_H
