//
// Created by efrat on 23/12/18.
//
#include "ConnectCommand.h"

void ConnectCommand::execute(const std::vector<std::string> ve) {
    EvaluateExp *evaluateExp1= new EvaluateExp(ve[1]);
    EvaluateExp *evaluateExp2= new EvaluateExp(ve[2]);
    string eval1 = evaluateExp1->Infix_To_Prefix(ve[1]);
    string eval2 = evaluateExp2->Infix_To_Prefix(ve[2]);
    Expression *x = evaluateExp1->evaluatePrefix(eval1);
    Expression *y = evaluateExp2->evaluatePrefix(eval2);
    double x1 = x->calculate(ve);
    double y1 = y->calculate(ve);
    struct ClientParams* params = new ClientParams();
    params->Ipaddress = x1;
    params->port = y1;
    params->global1=this->glob;
    params->instruction=this->glob->getIns();

    // DataReaderServer* serverS;

    pthread_t trid;
    pthread_create(&trid, nullptr, DataReaderServer::openClientSocket, params);
}
