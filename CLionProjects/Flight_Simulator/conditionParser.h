//
// Created by neta on 12/18/18.
//

#ifndef FLIGHT_SIMULATOR_CONDITIONPARSER_H
#define FLIGHT_SIMULATOR_CONDITIONPARSER_H
#include "vector"
#include "Command.h"
#include "CommandExpression.h"
#include <string>
#include "map"
#include "openDataServerCommand.h"
#include "unordered_map"
using namespace std;
class conditionParser : public Command {
protected:
    Expression *command;
    vector<std::string> condition;
    global *glob;
public:
    conditionParser(Expression *command1, vector<std::string> condition, global *global1) {
        this->command = command1;
        this->condition=condition;
        this->glob=global1;
    }

    bool isTrue (const std::vector<std::string> ve) {
        string op = ve[2];
        EvaluateExp *evaluateExp1= new EvaluateExp(ve[1]);
        EvaluateExp *evaluateExp2= new EvaluateExp(ve[3]);
        string eval1 = evaluateExp1->Infix_To_Prefix(ve[1]);
        string eval2 = evaluateExp2->Infix_To_Prefix(ve[3]);
        Expression *x = evaluateExp1->evaluatePrefix(eval1);
        Expression *y = evaluateExp2->evaluatePrefix(eval2);
        double x1 = x->calculate(ve);
        double y1 = y->calculate(ve);
        int comper = stoi(ve[3]);
        if (op == "==") {
            if (x1 == y1) { return true; }
            else { return false; }
        } else if (op == "!=") {
            if (x1 != y1) {
                return true;
            } else { return false; }
        } else if (op == ">") {
            if (x1 > y1) {
                return true;
            } else { return false; }
        } else if (op == "<=") {
            if (x1 <= y1) {
                return true;
            } else { return false; }
        } else if (op == "<") {
            if (x1 < y1) {
                return true;
            } else { return false; }
        } else if (op == "<=") {
            if (x1 <= y1) {
                return true;
            } else { return false; }
        }
    }

    void execute(std::vector<std::string> ve) {}

    void cndINcnd(vector<pair<Expression*,vector<string>>> veOfCnd) {
        vector<pair<Expression*,vector<string>>> saveVE= veOfCnd;
        int open =0;
        int close =0;
        int row=0;
        for (auto it = veOfCnd.begin(); it != veOfCnd.end(); it++) {
            row++;
            if (it->second.at(it->second.size() - 1) == "{") {
                open++;
            }
            if (it->second.at(it->second.size() - 1) == "}") {
                close++;
            }
            if (open == close && open != 0){
                break;
            }

        }

        veOfCnd.erase(veOfCnd.begin()+row-1, veOfCnd.end());
        veOfCnd.erase(veOfCnd.begin());
        conditionParser *conditionParser1 = new conditionParser(saveVE.at(0).first, saveVE.at(0).second,this->glob);
        conditionParser1->doCommand(veOfCnd,  saveVE.at(0).second);
    }

    void doCommand(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<std::string> condition) {
        if (isTrue(condition)) {
            //אין משמעות לוקטור ששולחים - לא משתמשים בו
            this->command->doExectue(mapOfCnd,condition);
        }
    }

    void doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition) {}

};
#endif //FLIGHT_SIMULATOR_CONDITIONPARSER_H