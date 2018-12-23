//
// Created by neta on 12/18/18.
//
#include "vector"
#include "CommandExpression.h"
#include "Command.h"
#include "conditionParser.h"
#include "Expression.h"
#include "unordered_map"
#include "global.h"
#ifndef FLIGHT_SIMULATOR_IFCOMMAND_H
#define FLIGHT_SIMULATOR_IFCOMMAND_H
class ifCommand : public conditionParser {
    vector<std::string> vector1;
    Expression *c;
    global *glob;
public:
    ifCommand(Expression *command1, vector<std::string> vector1,global *global1) : conditionParser(command1,vector1,global1){
    }

    void execute(const std::vector<std::string> ve) {}

    void doCondition(vector<pair<Expression*,vector<string>>> veOfCnd, vector<string> condition) {
        vector<pair<Expression*,vector<string>>> temp = veOfCnd;
        int open=1;
        int close=0;
        bool fromLoop=false;
        if (isTrue(condition)) {
            int i = 0;
            for (auto it = veOfCnd.begin(); it != veOfCnd.end(); it++) {
                if (fromLoop) {
                    while (open != close) {
                        if (it->second.at(it->second.size() - 1) == "{") {
                            open++;
                        } else if (it->second.at(it->second.size() - 1) == "}") {
                            close++;
                        }
                        i++;
                        it++;
                    }
                    open=1;
                    close=0;
                    fromLoop=false;
                }
                if (it->first == NULL){
                    break;
                }
                if (it->second.at(0)=="while" || it->second.at(0)=="if") {
                    temp.erase(temp.begin(),temp.begin()+i);
                    fromLoop=true;
                    cndINcnd(temp);
                    temp = veOfCnd;

                } else {
                    if (it->second.size()>1) {
                        it->first->calculate(it->second);
                    }
                }
                i++;
            }
        }
    }

};

#endif //FLIGHT_SIMULATOR_IFCOMMAND_H