#include <vector>
#include "DataReaderServer.h"
#include <algorithm>
#include "ConnectCommand.h"
#include "openDataServerCommand.h"


void* DataReaderServer::openServer(void *arg) {
    clock_t time_start;
    time_start = clock();
    struct MyParams *params = (struct MyParams *) arg;
    global *glob =params->global1;

    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
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
    bzero(buffer, 256);
    string buff;
    string leftOvers;
    vector<double> ve;
    while (true) {
        bzero(buffer, 1024);
        n = read(newsockfd, buffer, 1023);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        string buf = buffer;
        DataReaderServer *d;
        ve = d->explode1(buf, ',');
        if(ve.size() > 23){
            unsigned long  size1 = buf.find("\n");
            buf.erase(0,size1 + 1);
            unsigned long size2 =  buf.find("\n");
            if(size2 != string::npos){
                buf.erase(size2,buf.size());
            }
            ve = d->explode1(buf, ',');
            if(ve.size() < 23){
                buf=  buffer;
                buf.erase(size1,buf.size());

            }
            ve = d->explode1(buf, ',');
        }
        for (int i = 0; i < glob->getVars().size(); ++i) {
            try {
                glob->setXMLTable(glob->getVars()[i], ve[i]);

            }   catch (exception& e)    {
                cout << "Exception!" << e.what() << endl;
            }

        }
        buff += leftOvers;
        leftOvers = "";
    }
}

vector<double> DataReaderServer::explode1(string &s, const char &c) {
    string buff{""};
    vector<double> v;
    for (auto n:s) {
        if (n != c) {
            buff += n;
        } else if(buff != ""){
            double num;
            num = stod(buff);
            v.push_back(num);
            buff = "";
        }
    }
    if (buff[buff.length() - 1] == '\n') {
        buff = buff.substr(0, buff.length() - 1);
    }
    double num;
    if (buff != "" && buff != "-" && buff[buff.length() - 1] != '.') {
        num = stod(buff);
        v.push_back(num);
    }
    return v;
}