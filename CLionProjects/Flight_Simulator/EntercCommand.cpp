//
// Created by efrat on 26/12/18.
//

//

#include "EntercCommand.h"
#include "iostream"
using namespace std;

void EntercCommand::execute(const std::vector<std::string> ve) {
    cout << "enter a c" << endl;
    cin.ignore();
}

void EntercCommand::doCondition(vector<pair<Expression*,vector<string>>> mapOfCnd, vector<string> condition){}