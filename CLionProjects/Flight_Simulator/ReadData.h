//
// Created by neta on 12/18/18.
//
#include "Expression.h"
#include "CommandExpression.h"
#include "openDataServerCommand.h"
#include "cstring"
#include "fstream"
#include "conditionParser.h"
#include "loopCommand.h"
#include "unordered_map"
#include "endOfLoopCommand.h"
#include "ConnectCommand.h"
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
        Expression *connect = new CommandExpression(new connectCommand(this->glob));
        Expression *var = new CommandExpression(new varCommand(this->glob));
        Expression *print = new CommandExpression(new printCommand(this->glob));
        Expression *whileCommand = new CommandExpression(new loopCommand(c, vector1,this->glob));
        Expression *ifCmd= new CommandExpression(new ifCommand(c,vector1,this->glob));
        mapOfCommand["openDataServer"] = open;
        mapOfCommand["}"] = endOfLoop;
        mapOfCommand["connect"] = connect;
        mapOfCommand["var"] = var;
        mapOfCommand["print"] = print;
        mapOfCommand["while"] = whileCommand;
        mapOfCommand["if"]= ifCmd;

    }

    int lexerCndition(string condition , std::ifstream& myfile) {
        // לטפל במקרה שהסוגריים בשורה מתחת
        string line = "";
        map<Expression*,vector<string> > mapOfCnd;
        std::vector<std::string> temp;
        std::vector<vector<string>> result;
        int open = 1;
        int close = 0;
        string open1 = "{";
        string close1 = "}";
        temp = Lexer2(condition,' ');
        result.push_back(temp);
        if (myfile.is_open()) {
            while (getline(myfile, line)) {
                temp = Lexer2(line,' ');
                if(strstr(line.c_str(),open1.c_str())) {
                    open++;
                }
                if(strstr(line.c_str(),close1.c_str())) {
                    close++;
                }
                if (open == close) {
                    result.push_back(temp);
                    //call to parser
                    parserOfCondition(result);
                    return 0;
                }
                result.push_back(temp);
            }
        }
    }

    void parserOfCondition(std::vector<vector<string>> ve) {
        conditionParser *conditionParser1;
        vector<pair<Expression*,vector<string>>> veOfcnd;
       // unordered_multimap<Expression*,vector<string> > mapOfCnd;
        for (int i=1 ; i < ve.size() ; i++) {
            int j=0;
                try {
                  Expression *commandExpression = mapOfCommand.at(ve.at(i).at(0));
                    veOfcnd.push_back(std::make_pair(commandExpression,ve[i]));


                } catch (out_of_range &e) {
                    throw "No matching variable";
                }
        }
//        if (ve.at(0).at(0) == "while") {
//            conditionParser1= new conditionParser(new CommandExpression(new loopCommand(c, vector1,this->glob)), ve[0]);
//        }
            //if condition
//        else {
//            conditionParser1= new conditionParser(new CommandExpression(new ifCommand(c, vector1,this->glob)), ve[0]);
//        }

        conditionParser1->doCommand(veOfcnd,ve[0]);
    }

    std::vector<std::string> Lexer2(const std::string& s, const char& c) {
        std::string buff{""};
        std::vector<std::string> v;
        for(auto n:s) {
            if(n != c) {
                buff += n;
            }
            else {
                v.push_back(buff);
                buff="";
            }
        }
        v.push_back(buff);
     //   v.push_back("@");
        return v;
    }

    void Lexer(const std::string& s, const char& c) {
        std::string buff{""};
        std::vector<std::string> v;
        for(auto n:s) {
            if(n != c) {
                buff += n;
            }
            else {
                v.push_back(buff);
                buff="";
            }
        }
        v.push_back(buff);
        parser(v);
    }

    void parser(std::vector<std::string> ve) {
        for (std::map<string,Expression*>::iterator it=mapOfCommand.begin(); it!=mapOfCommand.end(); ++it) {
            if (it->first == ve[0]) {
                Expression *expression = it->second;
                expression->calculate(ve);
                }
            }
        }
        //לעשות איטרטור על המפה של הסימבול- אם ve במקום ה0 שווה לאחד מהמפתחות -- תלך לset var command


};
#endif //FLIGHT_SIMULATOR_READDATA_H
