
#include <vector>
#include "DataReaderServer.h"
#include "openDataServerCommand.h"
#include "ConnectCommand.h"

void* DataReaderServer::openServer(void *arg) {
    vector<string> vars;
    struct MyParams *params = (struct MyParams *) arg;
    global *glob = params->global1;

    glob->updateSymTbl("efrfr", 10.9090);
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

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    //If connection is established then start communicating */
    bzero(buffer, 1024);

    //sleep for this->Hz
    while (true) {
        n = read(newsockfd, buffer, 1024);
        string b = buffer;
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        vector<string> line;
        size_t pos = 0;
        string delimiter = ",";
        //splitting by ","
        while ((pos = b.find(delimiter)) != string::npos) {
            line.push_back(b.substr(0, pos));
            b.erase(0, pos + delimiter.length());
            //cout << b << endl;
        }
        line.push_back(b.substr(0, pos));

        //update the map with new values read from the simulator
        for (int i = 0; i < line.size(); ++i) {
            glob->updateSymTbl(vars[i], stod(line[i]));
        }
    }
}


void* DataReaderServer::openClientSocket(void *arg) {
    struct ClientParams *params = (struct ClientParams *) arg;
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    global *glob = params->global1;

//    char buffer[256];

//    if (argc < 3) {
//        fprintf(stderr,"usage %s hostname port\n", argv[0]);
//        exit(0);
//    }

    portno = params->port;

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    glob->setSockfd(sockfd);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(params->Ipaddress.c_str());

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

    return 0;
}

