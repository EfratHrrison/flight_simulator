//
// Created by efrat on 23/12/18.
//

#ifndef FLIGHT_SIMULATOR_SLEEPCOMMAND_H
#define FLIGHT_SIMULATOR_SLEEPCOMMAND_H


#include<unistd.h>
#include "Command.h"
#include <chrono>
#include <thread>

using namespace std;

class sleepCommand : public Command {
public:
    sleepCommand()= default;
    void execute(const std::vector<std::string> ve);

};
#endif //FLIGHT_SIMULATOR_SLEEPCOMMAND_H
