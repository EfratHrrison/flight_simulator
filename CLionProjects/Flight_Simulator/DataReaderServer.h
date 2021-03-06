//
// Created by neta on 12/19/18.
//

#ifndef FLIGHT_SIMULATOR_DATAREADERSERVER_H
#define FLIGHT_SIMULATOR_DATAREADERSERVER_H

#include "thread"
#include "sys/socket.h"
#include "netinet/in.h"
#include <stdio.h>
#include "iostream"
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include "global.h"
#include "vector"



using namespace std;
class DataReaderServer : public thread {
private:
    int port;
    int time;
public:
    DataReaderServer(int a, int b) {
        this->port=a;
        this->time=b;
    }
    vector<string>explode(string s,char c);
    static void* openServer(void *arg);
    static void* openClientSocket(void *arg);
    vector<double> explode1(string &s, const char &c);
};




#endif //FLIGHT_SIMULATOR_DATAREADERSERVER_H
