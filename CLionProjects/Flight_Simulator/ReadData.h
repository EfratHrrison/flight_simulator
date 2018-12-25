//
// Created by neta on 12/18/18.
//
#include "Expression.h"
#include "CommandExpression.h"
#include "openDataServerCommand.h"
#include "ConnectCommand.h"
#include "cstring"
#include "fstream"
#include "sleepCommand.h"
#include "conditionParser.h"
#include "loopCommand.h"
#include "unordered_map"
#include "endOfLoopCommand.h"
#include "PrintCommand.h"
#include "varCommand.h"
#include "global.h"

#ifndef FLIGHT_SIMULATOR_READDATA_H
#define FLIGHT_SIMULATOR_READDATA_H

class ReadData  {
private:
Expression *c;
    map<string, Expression*> mapOfCommand;;
    vector<string> vector1;
    global *glob;
    map<Expression*,vector<string> > map2;

public:
    ReadData() {
        this->glob =new global();
        initMapCommand();
    }

    void initMapCommand() {
        Expression *open = new CommandExpression(new openServerCommand(this->glob));
        Expression *endOfLoop = new CommandExpression(new endOfLoopCommand(this->glob));
        Expression *connect = new CommandExpression(new ConnectCommand(this->glob));
        //Expression *var = new CommandExpression(new varCommand(this->glob));
        Expression *sleep = new CommandExpression(new sleepCommand(this->glob));
        Expression *print = new CommandExpression(new printCommand(this->glob));
        Expression *whileCommand = new CommandExpression(new loopCommand(c, vector1,this->glob));
        Expression *ifCmd= new CommandExpression(new ifCommand(c,vector1,this->glob));
        mapOfCommand["openDataServer"] = open;
        mapOfCommand["}"] = endOfLoop;
        mapOfCommand["connect"] = connect;
        //mapOfCommand["var"] = var;
        mapOfCommand["print"] = print;
        mapOfCommand["while"] = whileCommand;
        mapOfCommand["if"]= ifCmd;
        mapOfCommand["sleep"] = sleep;

    }

    int lexerCndition(string condition , std::ifstream& myfile) {
        bool push=false;
        string equal = "=";
        string var = "var";
        string bind = "bind";
        string open ="openDataServer";
        string connect = "connect";
        string print ="print";
        string sleep ="sleep";
        string line = "";
        string cnd1 = "if";
        string cnd2 = "while";
        map<Expression*,vector<string> > mapOfCnd;
        std::vector<std::string> temp;
        std::vector<vector<string>> result;
        int open5 = 1;
        int close = 0;
        string open1 = "{";
        string close1 = "}";
        if (strstr(condition.c_str(),cnd1.c_str())) {
            condition=removeSubstrs(condition,cnd1);
            condition=trim(condition);
            if (strstr(condition.c_str(),open1.c_str())) {
                condition=removeSubstrs(condition,open1);
                push= true;
            }
            temp = explodeCnd(condition);
            temp.insert(temp.begin(),cnd1);
        } else if (strstr(condition.c_str(),cnd2.c_str())) {
            condition = removeSubstrs(condition, cnd2);
            condition = trim(condition);
            if (strstr(condition.c_str(),open1.c_str())) {
                condition=removeSubstrs(condition,open1);
                push= true;
            }
            temp = explodeCnd(condition);
            temp.insert(temp.begin(), cnd2);
        }
        if (push) {
            temp.push_back(open1);
        }
        result.push_back(temp);
        if (myfile.is_open()) {
            while (getline(myfile, line)) {
                if (line.empty()) {
                    continue;
                }
                if (strstr(line.c_str(),cnd1.c_str())) {
                    line=removeSubstrs(line,cnd1);
                    line=trim(line);
                    temp = explodeCnd(line);
                    temp.insert(temp.begin(),cnd1);
                } else if (strstr(line.c_str(),cnd2.c_str())) {
                    line=removeSubstrs(line,cnd2);
                    line=trim(line);
                    temp = explodeCnd(line);
                    temp.insert(temp.begin(),cnd2);
                } else if (strstr(line.c_str(),open.c_str())){
                    line=removeSubstrs(line,open);
                    line=trim(line);
                    temp = explodeOpen(line);
                    temp.insert(temp.begin(),open);
                } else if (strstr(line.c_str(),connect.c_str())) {
                    line=removeSubstrs(line,connect);
                    line=trim(line);
                    temp = explodeConnect(line);
                    temp.insert(temp.begin(),connect);
                } else if (strstr(line.c_str(),equal.c_str())) {
                    temp=explode(line,'=',equal);
                } else if (strstr(line.c_str(),var.c_str())) {
                    temp=explode(line,'=',var);
                } else if (strstr(line.c_str(),bind.c_str())) {
                    temp=explode(line,'=',bind);
                } else if (strstr(line.c_str(),print.c_str())) {
                    temp.clear();
                    line=removeSubstrs(line,print);
                    line=trim(line);
                    temp.push_back(print);
                    temp.push_back(line);
                } else if (strstr(line.c_str(),sleep.c_str())) {
                    temp.clear();
                    line=removeSubstrs(line,sleep);
                    line=trim(line);
                    temp.push_back(sleep);
                    temp.push_back(line);
                }
                if(strstr(line.c_str(),open1.c_str())) {
                    if (line.size()==1) {
                        result.at(result.size()-1).push_back(line);
                        continue;
                    }
                    open5++;
                }
                if(strstr(line.c_str(),close1.c_str())) {
                    temp.clear();
                    temp.push_back(close1);
                    close++;
                }
                if (open5 == close) {
                    result.push_back(temp);
                    //call to parser
                    parserOfCondition(result);
                    return 0;
                }
                result.push_back(temp);
            }
        }
    }

    void Lexer (string line) {
        std::vector<std::string> v;
        std::string buff{""};
        string equal = "=";
        string var = "var";
        string bind = "bind";
        string open ="openDataServer";
        string connect = "connect";
        string print ="print";
        string sleep ="sleep";
        //3 option of vars
        if(strstr(line.c_str(),equal.c_str())) {
            //2 option - or var xxx = xxx or xxx = xxx
            if (!strstr(line.c_str(),bind.c_str())) {
                //xxx = xxx  - work!!!!!
                if (!strstr(line.c_str(),var.c_str())) {
                    v= explode(line, '=', equal);
                }
                    //var xxx = xxx
                else {
                    v= explode(line, '=', var);
                }
                // bind option. var xxx = bind "/////" or var xxx = bind
            } else {
                v= explode(line, '=', bind);
            }
        }
        else if (strstr(line.c_str(),open.c_str())) {
            buff=removeSubstrs(line,open);
            buff=trim(buff);
            v = explodeOpen(buff);
            v.insert(v.begin(),open);
        }
        else if (strstr(line.c_str(),connect.c_str())) {
            buff=removeSubstrs(line,connect);
            buff=trim(buff);
            v = explodeConnect(buff);
            v.insert(v.begin(),connect);
        }
        else if (strstr(line.c_str(),print.c_str())) {
            buff=removeSubstrs(line,print);
            buff=trim(buff);
            v.push_back(print);
            v.push_back(buff);
        }
        else if (strstr(line.c_str(),sleep.c_str())) {
            buff=removeSubstrs(line,sleep);
            buff=trim(buff);
            v.push_back(sleep);
            v.push_back(buff);
        }
        else {
            throw "invalid input";
        }
        parser(v);
    }

    std::vector<std::string> explodeCnd(const std::string& s) {
        std::string buff{""};
        bool check=false;
        std::vector<std::string> v;
        for(auto n:s) {
            if (check) {
                buff+=n;
            } else if (!isOperand1(n)) {
                buff += n;
            } else {
                check=true;
                v.push_back(buff);
                buff="";
                buff+=n;
                v.push_back(buff);
                buff="";
            }
        }
        buff=trim(buff);
        v.push_back(buff);
        return v;
    }

// לא מכסה בכלל את כל המקרי קצה!!!!!
    std::vector<std::string> explodeConnect(const std::string& s) {
        std::string buff{""};
        std::vector<std::string> v;
        int counterPoint=0;
        for(auto n:s) {
            if (n != '.') {
                if (n != ' ' && (isdigit(n) || isalpha(n) || n=='_')) {
                    buff += n;
                    if(counterPoint==3){
                        counterPoint++;
                        v.push_back(buff);
                        buff="";
                    }
                }
            }
            else {
                if (counterPoint < 3) {
                    if (n != ' ') {
                        buff += n;
                        counterPoint++;
                    }
                }
            }
        }
        buff=trim(buff);
        v.push_back(buff);
        return v;
    }

    // 5+3 -6
    std::vector<std::string> explodeOpen(const std::string& s) {
        std::string buff{""};
        bool isSpace=false;
        std::vector<std::string> v;
        for(auto n:s) {
            if (isOperator1(n)) {
                if (isSpace) {
                    if (buff.at(buff.size() - 1) == ')') {
                        if (n == '(') {
                            v.push_back(buff);
                            buff="";
                        }
                    }
                    isSpace= false;
                }
                buff += n;
            } else if (n == ' ') {
                isSpace=true;
                continue;
            } else if (isdigit(n)) {
                if (isSpace) {
                    if (isdigit(buff.at(buff.size()-1))) {
                        v.push_back(buff);
                        buff="";
                    }
                    isSpace = false;
                }
                buff.push_back(n);
                //buff+=n;
            } else {
                v.push_back(buff);
                buff="";
                isSpace= false;
            }
        }
        v.push_back(buff);
        return v;
    }

    std::vector<std::string> explode(const std::string& s, const char& c, const string& c1) {
        bool var = false;
        std::string buff{""};
        std::vector<std::string> v;
        for (int i = 0; i < s.size(); i++) {
            if(var) {
                if (s[i] != ' ') {
                    if (isalpha(s[i])|| isdigit(s[i]) || (s[i]=='/') || (isOperator1(s[i])) ||(s[i]=='_') ||(s[i]=='-')){
                        buff += s[i];
                    }
                }
                continue;
            }
            if(s[i] != c) {
                if (s[i] != ' ' && (isalpha(s[i])|| isdigit(s[i]) || (isOperator1(s[i]))||(s[i]=='-') )) {
                    buff += s[i];
                }
            }
            else {
                buff = trim(buff);
                //x = 8
                if (c1 == "=") {
                    v.push_back(buff);
                    v.push_back("=");
                    var= true;
                }
                    //var x = 8 + bind;
                else if (c1 == "var" || c1 == "bind") {
                    buff=removeSubstrs(buff,"var");
                    buff=trim(buff);
                    v.push_back("var");
                    v.push_back(buff);
                    v.push_back("=");
                    if (c1 == "bind") {
                        v.push_back("bind");
                    }
                    var= true;
                }
                else {
                    v.push_back(buff);
                }
                buff = "";
            }
        }
        // maybe dont needed
        if (c1=="bind") {
            buff=removeSubstrs(buff,"bind");
            buff=trim(buff);
        }
        buff=trim(buff);
        v.push_back(buff);
        return v;
    }

    bool isOperator1(char c) {
        if ( (c=='(' ) || (c==')') || (c=='-')|| (c=='+') || (c=='*') || (c=='/') ) {
            return true;
        }
        return false;
    }

    bool isOperand1(char c) {
        if ( (c=='>' ) || (c=='<') || (c=='==')|| (c=='!=') || (c=='>=') || (c=='<=') ) {
            return true;
        }
        return false;
    }

    // this fuction remove leading sapce
    string trim(string s) {
        size_t p = s.find_first_not_of(" \t");
        s.erase(0, p);
        p = s.find_last_not_of(" \t");
        if (string::npos != p) {
            s.erase(p + 1);
        }
        return s;
    }

    string removeSubstrs(string s, string p) {
        string::size_type n = p.length();
        for (string::size_type i = s.find(p);
             i != string::npos;
             i = s.find(p)) {
            s.erase(i, n);
        }
        return s;
    }

    void parser(std::vector<std::string> ve) {
        if (ve.size()>2) {
            if (ve[2] == "=" || ve[1] == "=") {
                Expression *var = new CommandExpression(new varCommand(this->glob));
                var->calculate(ve);
            } else {
                for (std::map<string,Expression*>::iterator it=mapOfCommand.begin(); it!=mapOfCommand.end(); ++it) {
                    if (it->first == ve[0]) {
                        Expression *expression = it->second;
                        expression->calculate(ve);
                    }
                }
            }
        } else {
            for (std::map<string,Expression*>::iterator it=mapOfCommand.begin(); it!=mapOfCommand.end(); ++it) {
                if (it->first == ve[0]) {
                    Expression *expression = it->second;
                    expression->calculate(ve);
                }
            }
        }
    }

    //לעשות איטרטור על המפה של הסימבול- אם ve במקום ה0 שווה לאחד מהמפתחות -- תלך לset var command
    void parserOfCondition(std::vector<vector<string>> ve) {
        conditionParser *conditionParser1;
        vector<pair<Expression*,vector<string>>> veOfcnd;
        for (int i=1 ; i < ve.size() ; i++) {
            if (ve.at(i).size()>2) {
                if (ve.at(i).at(1) == "=" || ve.at(i).at(2) == "=") {
                    Expression *var = new CommandExpression(new varCommand(this->glob));
                    veOfcnd.push_back(std::make_pair(var, ve[i]));
                } else {
                    try {
                        Expression *commandExpression = mapOfCommand.at(ve.at(i).at(0));
                        veOfcnd.push_back(std::make_pair(commandExpression, ve[i]));

                    } catch (out_of_range &e) {
                        throw "No matching variable";
                    }
                }
            } else {
                try {
                    Expression *commandExpression = mapOfCommand.at(ve.at(i).at(0));
                    veOfcnd.push_back(std::make_pair(commandExpression, ve[i]));

                } catch (out_of_range &e) {
                    throw "No matching variable";
                }
            }
        }
        if (ve.at(0).at(0) == "while") {
            conditionParser1= new conditionParser(new CommandExpression(new loopCommand(c, vector1, this->glob)), ve[0], this->glob);
        }
            //if condition
        else {
            conditionParser1= new conditionParser(new CommandExpression(new ifCommand(c, vector1, this->glob)), ve[0], this->glob);
        }
        veOfcnd.erase(veOfcnd.end());
        conditionParser1->doCommand(veOfcnd,ve[0]);
    }

};
#endif //FLIGHT_SIMULATOR_READDATA_H
