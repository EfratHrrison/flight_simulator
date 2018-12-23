//
// Created by efrat on 23/12/18.
//

#include "varCommand.h"

#include "ConnectCommand.h"
void varCommand::execute(const std::vector<std::string> ve) {
    char s= '"';
    if (ve[2]=="=") {
        //bind option
        if (ve[3] == "bind") {
            string bind = ve[4];
            if (ve[4].find('"') != std::string::npos) {
                //   bind.erase(bind.begin());
                //  bind.erase(bind.end()-1);
                this->glob->insertBindTbl(ve[1],bind);
            }
            else {
                this->glob->insertBindTbl(ve[1], ve[4]);
            }
            //new var option
        } else {
            EvaluateExp *evaluateExp1= new EvaluateExp(ve[3]);
            string eval1 = evaluateExp1->Infix_To_Prefix(ve[3]);
            Expression *x = evaluateExp1->evaluatePrefix(eval1);
            double value = x->calculate(ve);
            this->glob->inserSymbTbl(ve[1], value);
        }
        // update var option
    } else {
        EvaluateExp *evaluateExp1= new EvaluateExp(ve[3]);
        string eval1 = evaluateExp1->Infix_To_Prefix(ve[3]);
        Expression *x = evaluateExp1->evaluatePrefix(eval1);
        double value = x->calculate(ve);
        string path;
        path+="set ";
        path+=glob->OPgetVarBindTbl(ve[0]);
        string strValue = to_string(value);
        path+=strValue;
        path+="/r/n";
        this->glob->setIns(path);
        this->glob->updateSymTbl(ve[0],value);
    }
}