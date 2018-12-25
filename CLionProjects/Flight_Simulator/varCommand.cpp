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
            if ((ve[4].find('/') != std::string::npos)) {
               // pthread_mutex_lock(&mutexXml);
                this->glob->insertBindTbl(ve[1], ve[4]);
              //  pthread_mutex_unlock(&mutexXml);
            }
            else {
                // מיוטקס ??
                this->glob->insertVarBind(ve[4],ve[1]);
            }
            //new var option
        } else {
          //  pthread_mutex_lock(&mutexXml);
            EvaluateExp *evaluateExp1= new EvaluateExp(ve[3], this->glob);
            string eval1 = evaluateExp1->Infix_To_Prefix(ve[3]);
            Expression *x = evaluateExp1->evaluatePrefix(eval1);
            double value = x->calculate(ve);
            this->glob->inserSymbTbl(ve[1], value);
            //pthread_mutex_unlock(&mutexXml);
        }
        // update var option
    } else {
        EvaluateExp *evaluateExp1= new EvaluateExp(ve[2], this->glob);
        string eval1 = evaluateExp1->Infix_To_Prefix(ve[2]);
        Expression *x = evaluateExp1->evaluatePrefix(eval1);
        double value = x->calculate(ve);
        string path;
        path+="set ";
        string addr=glob->OPgetVarBindTbl(ve[0]);
        path+=addr;
        string strValue = to_string(value);
        path+=strValue;
        path+="\r\n";
      //  pthread_mutex_lock(&mutexIns);
        this->glob->setIns(path);
      //  pthread_mutex_unlock(&mutexIns);
      //  pthread_mutex_lock(&mutexXml);
        this->glob->inserSymbTbl(ve[0],value);
     //   pthread_mutex_unlock(&mutexXml);
    }
}