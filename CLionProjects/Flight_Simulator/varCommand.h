//
// Created by neta on 12/19/18.
//

#ifndef FLIGHT_SIMULATOR_VARCOMMAND_H
#define FLIGHT_SIMULATOR_VARCOMMAND_H
#include "vector"
#include "Command.h"
#include "EvaluateExp.h"


using namespace std;
class varCommand : public Command {
public:
    varCommand()= default;
    void execute(const std::vector<std::string> ve) {
        //new var
        if (ve[3] == "bind") {
            //new bind for the bind table
            //params.insert(make_pair(ve[1],ve[4]));
        }
        else {
            //  EvaluateExp *evaluateExp1= new EvaluateExp(ve[3]);
            //  string eval1 = evaluateExp1->Infix_To_Prefix(ve[3]);
            //  Expression *x = evaluateExp1->evaluatePrefix(eval1);
            //  double value = x->calculate(ve);
            //  params1.insert(make_pair(ve[1],value));
            // }
            //  else {
            //  EvaluateExp *evaluateExp1= new EvaluateExp(ve[3]);
            //  string eval1 = evaluateExp1->Infix_To_Prefix(ve[3]);
            //  Expression *x = evaluateExp1->evaluatePrefix(eval1);
            //  double value = x->calculate(ve);
            //  params1.insert(make_pair(ve[1],value));
        }
    }
    void doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition) {}


};
#endif //FLIGHT_SIMULATOR_VARCOMMAND_H
