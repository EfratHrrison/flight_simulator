//
// Created by efrat on 23/12/18.
//
#include "sleepCommand.h"
#include "EvaluateExp.h"

void sleepCommand::execute(const std::vector<std::string> ve) {
    EvaluateExp *evaluateExp1= new EvaluateExp(ve[1],this->glob);
    string eval1 = evaluateExp1->Infix_To_Prefix(ve[1]);
    Expression *x = evaluateExp1->evaluatePrefix(eval1);
    double x1 = x->calculate(ve);
    double sleepTime=x1;
    usleep(sleepTime*1000);
}

void sleepCommand::doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition){}