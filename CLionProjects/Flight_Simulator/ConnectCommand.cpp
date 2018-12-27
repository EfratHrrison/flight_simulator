//
// Created by efrat on 23/12/18.
//
#include "ConnectCommand.h"

void ConnectCommand::execute(const std::vector<std::string> ve) {
 //   EvaluateExp *evaluateExp1= new EvaluateExp(ve[1]);
  //  EvaluateExp *evaluateExp2= new EvaluateExp(ve[2]);
//    string eval1 = evaluateExp1->Infix_To_Prefix(ve[1]);
 //   string eval2 = evaluateExp2->Infix_To_Prefix(ve[2]);
 //   Expression *x = evaluateExp1->evaluatePrefix(eval1);
  //  Expression *y = evaluateExp2->evaluatePrefix(eval2);
  //  double x1 = x->calculate(ve);
//    double y1 = y->calculate(ve);
    struct ClientParams* params = new ClientParams();
    params->Ipaddress = ve[1];
    params->port = 5402;
 //   params->port =;
    params->global1=this->glob;
    // DataReaderServer* serverS;
    openClientSocket(params);
    //pthread_t trid;
    //pthread_create(&trid, nullptr, DataReaderServer::openClientSocket, params);
}

void*  ConnectCommand::openClientSocket(void *arg) {
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

  //  while (true) {
        // pthread_mutex_lock(&mutexIns);
   //     if (glob->getIns() != "") {
   //         if(::send(sockfd, glob->getIns().data(), strlen(glob->getIns().data()),0) <0){
   //             perror("ERROR writing to socket");
   //             exit(1);
    //        }
    //        cout << glob->getIns().data() << endl;

   //         glob->setIns("");
            /* Send message to the server */
    //        if (n < 0) {
    //            perror("ERROR writing to socket");
    //            exit(1);
    //        }
    //    }
        //   pthread_mutex_trylock(&mutexIns);
   // }
}
