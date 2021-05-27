//
// Created by faniche on 12/26/20.
//

#ifndef POWERPUSH_SERVER_TRANSMISSION_H
#define POWERPUSH_SERVER_TRANSMISSION_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <queue>
#include <thread>
#include <cstring>
#include <iostream>
#include <cerrno>
#include <zconf.h>
#include <arpa/inet.h>
#include "env.h"
#include "zlog.h"
#include "Message.h"
#include "Cipher.h"
#include "Config.h"


class Transmission {
private:
    int udpSocketFd = 0;
    int tcpSocketFd = 0;
    struct sockaddr_in tcpServer{};
    struct sockaddr_in tcpClient{};
    struct sockaddr_in udpServer{};
    struct sockaddr_in udpClient{};
    void *tcpBuffer;
    void *udpBuffer;
    std::string tcpMsg;
    std::string udpMsg;
//    Message udpMsg;
    zlog_category_t *log;
    Config config;
    Cipher cipher;

    std::queue<Message> rcvMsgQueue;
    std::queue<Message> sndMsgQueue;

    void clipThreadFun();
public:
    explicit Transmission(zlog_category_t *log, Cipher &cipher,
                          Config &conf, std::queue<Message> &rcvQueue, std::queue<Message> &sndQueue);

    virtual ~Transmission();

    [[nodiscard]] const std::string &getMsg() const;

    void setTcpMsg(const std::string &tcpMsg);

    void setUdpMsg(const std::string &msg);

    void initSocket();

    int rcvDataTCP();

    int rcvDataUDP();

    static int sendData();
};


#endif //POWERPUSH_SERVER_TRANSMISSION_H
