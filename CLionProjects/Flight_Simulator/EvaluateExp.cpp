//
// Created by neta on 12/18/18.
//

#include "EvaluateExp.h"
#include<bits/stdc++.h>
#include "Expression.h"
#include "Plus.h"
#include "Minus.h"
#include "map"
#include "Mult.h"
#include "Div.h"
#include "Number.h"

using namespace std;

int EvaluateExp::findVar(string s) {
    return 0;
    //map<string, double >::iterator it;
    //   for (it = symbTbl.begin(); it != symbTbl.end(); it++) {
    //      if (it->first==s) {
    //        return it->second;
    //      }
    //  }
}

bool EvaluateExp::isVar1(string &string1) {
    //  unordered_map<string, double >::iterator it;
    //  for (it = param2.begin(); it != param2.end(); it++) {
    //      if (it->first==string1) {
    //         return true;
    //     }
    //  }
    return false;
}

void EvaluateExp::reverseStr(string& str) {
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

int EvaluateExp::Weight(char ch) {
    int power = 0;
    if(ch == '*' || ch == '/') {
        power = 2;
    }
    else if(ch == '+' || ch == '-') {
        power = 1;
    }
    return power;
}

bool EvaluateExp::Precedence(char ch1, char ch2) {
    int operator_1 = Weight(ch1);
    int operator_2 = Weight(ch2);
    return (operator_1 >= operator_2 ?  true : false);
}

bool EvaluateExp::Operator(char ch) {
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/'){
        return true;
    }
    return false;
}

string EvaluateExp::Infix_To_Prefix(string exp) {
    reverse(exp.begin(), exp.end());
    for(int i = 0; i < exp.length(); i++){
        if(exp[i] == ')'){
            exp.replace(i, 1, "(");
        }
        else if(exp[i] == '('){
            exp.replace(i, 1, ")");
        }
    }
    stack <char> S;
    string postfix = "";
    string var="";
    for(int i = 0; i < exp.length(); i++) {
        if(exp[i] == ' ') {
            continue;
        }
        else if(Operator(exp[i])) {
            postfix += ' ';
            if(exp[i]=='-' && (i==exp.length()-1 || !isdigit(exp[i+1]))) {
                postfix+="0";
                postfix += ' ';
                postfix+="-";
                continue;
            }
            while(!S.empty() && S.top() != '(' && Precedence(S.top(), exp[i])) {
                postfix += S.top();
                postfix += ' ';
                S.pop();
            }
            S.push(exp[i]);
        }
        else if (isalpha(exp[i])) {
            while (exp[i] != ' ' && isalpha(exp[i])) {
                var+=exp[i];
                i++;
            }
            i--;
            reverseStr(var);
            if(isVar1(var)){
                int numV= findVar(var);
                postfix+=to_string(numV);
                var="";
            }
            else {
                throw "illigal var";
            }
        }
        else if(isdigit(exp[i])) {
            postfix += exp[i];
        }
        else if (exp[i] == '(') {
            S.push(exp[i]);
        }
        else if(exp[i] == ')') {
            while(!S.empty() && S.top() != '(') {
                postfix += ' ';
                postfix += S.top();
                S.pop();
            }
            S.pop();
        }
    }
    while(!S.empty()) {
        postfix += ' ';
        postfix += S.top();
        S.pop();
    }
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

bool EvaluateExp::isOperand(char c) {
    return isdigit(c);
}

Expression* EvaluateExp::evaluatePrefix(string exprsn) {
    stack<Expression*> Stack;
    for (int j = exprsn.size() - 1; j >= 0; j--) {
        if (isOperand(exprsn[j])) {
            string s = "";
            while (exprsn[j] != ' ' && j>=0) {
                s+=exprsn[j];
                j--;
            }
            reverseStr(s);
            Stack.push(new Number(stoi(s)));
        }
        else {
            Expression *o1 = Stack.top();
            Stack.pop();
            Expression *o2 = Stack.top();
            Stack.pop();
            Expression *exp;
            switch (exprsn[j]) {
                case '+': {
                    exp = new Plus(o1,o2);
                    Stack.push(exp);
                    j--;
                    break;
                }
                case '-': {
                    exp = new Minus(o1, o2);
                    Stack.push(exp);
                    j--;
                    break;
                }
                case '*': {
                    exp = new mult(o1,o2);
                    Stack.push(exp);
                    j--;
                    break;
                }
                case '/': {
                    exp = new Div(o1,o2);
                    Stack.push(exp);
                    j--;
                    break;
                }
            }
        }
    }
    return Stack.top();
}