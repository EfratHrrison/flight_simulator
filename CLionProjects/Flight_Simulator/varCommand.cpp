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
                this->glob->insertBindTbl(ve[1], ve[4]);
            }
            else {
                this->glob->insertVarBind(ve[4],ve[1]);
            }
            //new var option
        } else {
            EvaluateExp *evaluateExp1= new EvaluateExp(ve[3], this->glob);
            string eval1 = evaluateExp1->Infix_To_Prefix(ve[3]);
            Expression *x = evaluateExp1->evaluatePrefix(eval1);
            double value = x->calculate(ve);
            this->glob->inserSymbTbl(ve[1], value);
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
        sendMessage(path);
        this->glob->inserSymbTbl(ve[0],value);
    }
}

void varCommand::sendMessage(string str) {
    int sockfd = this->glob->getSockfd();
    char *s = const_cast<char *>(str.c_str());
    /* Send message to the server */
    if(::send(sockfd, str.data(), strlen(str.data()),0) <0){
                    perror("ERROR writing to socket");
                     exit(1);
                };
    cout << str.data() << endl;
}