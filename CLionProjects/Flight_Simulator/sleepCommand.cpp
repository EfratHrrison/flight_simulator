//
// Created by efrat on 23/12/18.
//
#include "sleepCommand.h"

void sleepCommand::execute(const std::vector<std::string> ve) {
    int sleepTime=stoi(ve[1])*1000;
    sleep(sleepTime);
    //this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

}