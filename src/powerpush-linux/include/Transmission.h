//
// Created by faniche on 12/26/20.
//

#ifndef POWERPUSH_SERVER_TRANSMISSION_H
#define POWERPUSH_SERVER_TRANSMISSION_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include "zlog.h"
#include "env.h"

class Transmission {
private:
    int socketFd = 0;
    struct sockaddr_in server{};
    //int reuse = true;
    void * buffer;
    std::string msg;
    zlog_category_t *log;
    void rcvDataFun();
    void connectToServer();

public:
    explicit Transmission(zlog_category_t *log);

    virtual ~Transmission();

    [[nodiscard]] const std::string &getMsg() const;

    void setMsg(const std::string &newMsg);

    void initSocket();

    bool sendData();
};


#endif //POWERPUSH_SERVER_TRANSMISSION_H
