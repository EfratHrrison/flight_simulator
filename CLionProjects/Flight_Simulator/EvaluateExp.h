//
// Created by neta on 12/18/18.
//

#ifndef FLIGHT_SIMULATOR_EVALUATEEXP_H
#define FLIGHT_SIMULATOR_EVALUATEEXP_H


#include "string"
#include "Expression.h"
#include "map"
#include "global.h"
using namespace std;
class EvaluateExp {
private:
    string string1;
    global *glob;
    vector<Expression*> vEx;

public:

    EvaluateExp(string string2, global *global2){
        this->string1=string2;
        this->glob=global2;
    }
    bool isVar1(string& str);

    double findVar(string s);
    void reverseStr(string& str);
    int Weight(char ch);
    bool Precedence(char ch1, char ch2);
    bool Operator(char ch);
    string Infix_To_Prefix(string exp);
    bool isOperand(char c);
    Expression* evaluatePrefix(string exprsn);
    ~EvaluateExp(){
        for(auto x: this->vEx){
            delete(x);
        }
    }


};


#endif //FLIGHT_SIMULATOR_EVALUATEEXP_H
