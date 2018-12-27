//
// Created by neta on 12/18/18.
//

#ifndef FLIGHT_SIMULATOR_BINARYEXPRESSION_H
#define FLIGHT_SIMULATOR_BINARYEXPRESSION_H
#include "Expression.h"

class BinaryExpression : public Expression {
protected:
    Expression* left;
    Expression* right;

public:
    BinaryExpression(Expression* a, Expression* b){
        this->left = a;
        this->right = b;
    }
    ~BinaryExpression(){
        delete left;
        delete right;
    }

};

#endif //FLIGHT_SIMULATOR_BINARYEXPRESSION_H
