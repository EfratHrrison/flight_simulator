//
// Created by neta on 12/18/18.
//
#include "vector"
#include "string"
#include "map"
#include "unordered_map"

#ifndef FLIGHT_SIMULATOR_EXPRESSION_H
#define FLIGHT_SIMULATOR_EXPRESSION_H
using namespace std;

class Expression {
private:
    std::vector<std::string> v;
public:
    Expression(){
    }
    virtual double calculate(std::vector<std::string> v)=0;
    virtual void doExectue(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition)=0;


};
#endif //FLIGHT_SIMULATOR_EXPRESSION_H
