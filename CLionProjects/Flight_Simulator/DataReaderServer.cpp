
#include <vector>
#include "DataReaderServer.h"
#include "ConnectCommand.h"
#include "openDataServerCommand.h"


void* DataReaderServer::openServer(void *arg) {
    clock_t time_start;
    time_start = clock();
    vector<string> vars;
    struct MyParams *params = (struct MyParams *) arg;
    global *glob =params->global1;

    int sockfd, newsockfd, portno, clilen;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = params->port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    std::cout << "hi efrat" << endl;
    params->pass=true;

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    //If connection is established then start communicating */
    bzero(buffer, 1024);
    // אולי לשנות לדאבל
    vector<double > line;
    //sleep for this->Hz
    while (params->pass) {
      //  pthread_mutex_lock(&mutexIns);
        n = read(newsockfd, buffer, 1023);
       // cout<< buffer;
        string b = buffer;
        //cout << '\n';
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        string buff="";

        size_t pos = 0;
        //cout << b << endl;
        char delimiter = ',';
        for(auto n:b) {
            if(n != delimiter) {
                buff += n;
            }
            else {
                line.push_back(stod(buff));
                buff="";
            }
        }
        line.push_back(stod(buff));
        if(line.size() > 23) {
            int size = b.find("\n");
            b.erase(0,size +1);
            size =  b.find("\n");
            b.erase(size,b.size() +1);
            line.clear();
            for(auto n:b) {
                if(n != delimiter) {
                    buff += n;
                }
                else {
                    line.push_back(stod(buff));
                    buff="";
                }
            }
            line.push_back(stod(buff));
        }
       // pthread_mutex_lock(&mutexXml);
        glob->setXMLTable(line);
       // clock_t time_end;
      // time_end = time_start + 10 * params->hz * CLOCKS_PER_SEC / 1000;
       // pthread_mutex_unlock(&mutexXml);
       // while (clock() < time_end) {}
      // pthread_mutex_unlock(&mutexIns);
        line.clear();
    }
}

void*  DataReaderServer::openClientSocket(void *arg) {
    struct ClientParams *params = (struct ClientParams *) arg;
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    string ip=params->Ipaddress;
    portno = params->port;
    global *glob = params->global1;

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    glob->setSockfd(sockfd);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(ip.data());

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
    cout << "connected to simulator" << endl;
    while (true) {
        // pthread_mutex_lock(&mutexIns);
        if (glob->getIns() != "") {
            if(::send(sockfd, glob->getIns().data(), strlen(glob->getIns().data()),0) <0){
                perror("ERROR writing to socket");
                exit(1);
            }
            cout << glob->getIns().data() << endl;

            glob->setIns("");
            /* Send message to the server */
            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
        }
        //   pthread_mutex_trylock(&mutexIns);
    }
}





