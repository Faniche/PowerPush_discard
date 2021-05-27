//
// Created by faniche on 12/26/20.
//

#include <cstring>
#include <iostream>
#include <cerrno>
#include <thread>
#include <zconf.h>
#include <arpa/inet.h>
#include "include/Transmission.h"

/* Private function */
void Transmission::rcvDataFun() {

}

void Transmission::connectToServer() {
    int ret = connect(Transmission::socketFd, (struct sockaddr *) &server, sizeof(server));
    if (ret == -1) {
        zlog_debug(log, "%s", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

/* Public function */
Transmission::Transmission(zlog_category_t *log) {
    this->log = log;
    buffer = malloc(MSG_LEN);
    if (buffer == nullptr) {
        zlog_debug(log, "failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    memset((void *)&(Transmission::server), 0, sizeof(Transmission::server));
}

Transmission::~Transmission(){
    free(buffer);
}

void Transmission::initSocket() {
    buffer = malloc(MSG_LEN);
//    Transmission::socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    Transmission::socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    Transmission::server.sin_family = AF_INET;
    Transmission::server.sin_port = htons(51234);
    Transmission::server.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (Transmission::socketFd < 0) {
        zlog_debug(log, "create socket failed %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
//    connectToServer();
}

bool Transmission::sendData() {
    void * tmp = memset(Transmission::buffer, 0, getMsg().length());
    if (tmp == nullptr) {
        zlog_debug(this->log, "memset error");
    }
//    buffer = (void *)this->msg.c_str();
    memcpy(buffer, (void *) this->msg.c_str(), MSG_LEN);
//    int sentOutBytes =send(Transmission::socketFd , buffer , MSG_LEN , MSG_DONTWAIT);
//    int sentOutBytes = write(Transmission::socketFd, buffer, getMsg().length());
    size_t sentOutBytes = sendto(Transmission::socketFd, buffer, strlen((char *)getMsg().c_str()),
                          MSG_CONFIRM, (struct sockaddr *) &this->server, sizeof(this->server));
    if (sentOutBytes == -1) {
        zlog_debug(Transmission::log, "send msg to server error, %s", strerror(errno));
        return false;
    }
    return true;
}

const std::string &Transmission::getMsg() const {
    return msg;
}

void Transmission::setMsg(const std::string &newMsg) {
    Transmission::msg = newMsg;
}

