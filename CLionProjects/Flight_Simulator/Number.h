//
// Created by neta on 12/18/18.
//

#ifndef FLIGHT_SIMULATOR_NUMBER_H
#define FLIGHT_SIMULATOR_NUMBER_H
#include "Expression.h"
#include "unordered_map"
class Number: public Expression {
private:
    double number;

public:
    Number(double x){
        this->number = x;
    }
    double calculate(std::vector<std::string> v){
        return this->number;
    }
    void doExectue(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition){};



};
#endif //FLIGHT_SIMULATOR_NUMBER_H
