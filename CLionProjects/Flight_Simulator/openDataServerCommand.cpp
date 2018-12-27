//
// Created by neta on 12/19/18.
//

//
// Created by neta on 12/12/18.
//

#include "openDataServerCommand.h"
#include <pthread.h>
#include <iostream>
using namespace std;

//
//void* thread_func(void* arg) {
//    DataReaderServer* serverS;
//    serverS->openServer(arg);
//}

void openServerCommand::execute(std::vector<std::string> ve) {
    if(ve.size() != 3) {
        throw "No illigal input";
    }
    EvaluateExp *evaluateExp1= new EvaluateExp(ve[1],this->glob);
    EvaluateExp *evaluateExp2= new EvaluateExp(ve[2], this->glob);
    string eval1 = evaluateExp1->Infix_To_Prefix(ve[1]);
    string eval2 = evaluateExp2->Infix_To_Prefix(ve[2]);
    Expression *x = evaluateExp1->evaluatePrefix(eval1);
    Expression *y = evaluateExp2->evaluatePrefix(eval2);
    double x1 = x->calculate(ve);
    double y1 = y->calculate(ve);
    struct MyParams* params = new MyParams();
    params->port = x1;
    params->hz = y1;
    params->global1=this->glob;

    // DataReaderServer* serverS;

    for (int i = 0; i < glob->getVars().size(); ++i) {
        glob->setXMLTable(glob->getVars()[i], 0);
    }
    pthread_t trid;
    pthread_create(&trid, nullptr, DataReaderServer::openServer, params);
    while(!params->pass) {}
    delete(evaluateExp1);
    delete(evaluateExp2);
    return;


}
void openServerCommand::doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition) {

}