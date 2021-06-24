//
// Created by faniche on 12/26/20.
//

#include "include/Transmission.h"

/* Private function */
void Transmission::clipThreadFun() {
    zlog_info(this->log, "Starting receiving clipboard push ... ");
    socklen_t addrlen = sizeof(this->udpClient);
    std::string oldMsg, newMsg;
    while (true) {
        ssize_t ret = recvfrom(this->udpSocketFd, this->udpBuffer, MSG_LEN,
                               MSG_WAITALL, (sockaddr *) &this->udpClient, &addrlen);
        if (ret <= 0) {
            if (errno == EAGAIN)
                continue;
            zlog_debug(this->log, "Receive message error code: %d, %s", errno, strerror(errno));
            usleep(10);
            break;
        }
        newMsg = std::string((char *) this->udpBuffer);
        zlog_debug(this->log, "New clipboard content, %s", newMsg.c_str());
        if (newMsg != oldMsg) {
            oldMsg = newMsg;
            // Decrypt the message and add the message to received queue.
            setUdpMsg(newMsg);
        }
        memset(this->udpBuffer, 0, MSG_LEN);
        sleep(1);
    }
}

/* Public function */
Transmission::Transmission(zlog_category_t *log, Cipher &cipher,
                           Config &conf, std::queue<Message> &rcvQueue, std::queue<Message> &sndQueue) {
    this->log = log;
    tcpBuffer = malloc(MSG_LEN);
    if (tcpBuffer == nullptr) {
        zlog_debug(this->log, "Failed to allocate memory, %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    udpBuffer = malloc(MSG_LEN);
    memset(&this->tcpServer, 0, sizeof(struct sockaddr_in));
    memset(&this->tcpClient, 0, sizeof(struct sockaddr_in));
    memset(&this->tcpServer, 0, sizeof(struct sockaddr_in));
    memset(&this->tcpClient, 0, sizeof(struct sockaddr_in));
    Transmission::cipher = cipher;
    Transmission::config = conf;
    Transmission::rcvMsgQueue = rcvQueue;
    Transmission::sndMsgQueue = sndQueue;
}

Transmission::~Transmission() {
    free(tcpBuffer);
}

void Transmission::initSocket() {
    /* Initiate the tcp socket */
    Transmission::tcpSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    Transmission::tcpServer.sin_family = AF_INET;
    Transmission::tcpServer.sin_port = htons(this->config.getTcpPort());
    Transmission::tcpServer.sin_addr.s_addr = htonl(INADDR_ANY);
    if (Transmission::tcpSocketFd < 0) {
        zlog_debug(this->log, "Create socket failed, %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    int reuse = 1;
    if (setsockopt(Transmission::tcpSocketFd, SOL_SOCKET, SO_REUSEADDR,
                   (char *) &reuse, sizeof(int)) == -1) {
        zlog_debug(this->log, "Set socket option failed, %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (bind(Transmission::tcpSocketFd, (struct sockaddr *) &(Transmission::tcpServer),
             sizeof(Transmission::tcpServer)) < 0) {
        zlog_debug(this->log, "Bind socket failed, %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Initiate the udp socket */
    Transmission::udpSocketFd = socket(AF_INET, SOCK_DGRAM, 0);
    Transmission::udpServer.sin_family = AF_INET;
    Transmission::udpServer.sin_port = htons(this->config.getUdpPort());
    Transmission::udpServer.sin_addr.s_addr = htonl(INADDR_ANY);
    if (Transmission::udpSocketFd < 0) {
        zlog_debug(this->log, "Create socket failed, %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (bind(Transmission::udpSocketFd, (struct sockaddr *) &(Transmission::udpServer),
             sizeof(Transmission::udpServer)) < 0) {
        zlog_debug(this->log, "Bind socket failed, %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int Transmission::rcvDataTCP() {
    socklen_t addrlen = sizeof(Transmission::tcpClient);
    while (true) {
        int acptSockFd = accept(Transmission::tcpSocketFd, (struct sockaddr *) &tcpClient, &addrlen);
        if (acptSockFd < 0) {
            if (this->tcpClient.sin_addr.s_addr == 0) continue;
            zlog_debug(this->log, "Accept connection failed, %s", strerror(errno));
            exit(EXIT_FAILURE);
        }
        zlog_debug(this->log, "Connection from, %s", inet_ntoa(tcpClient.sin_addr));
        std::string oldMsg, newMsg;
        while (true) {
//            int ret = read(acptSockFd, tcpBuffer, MSG_LEN);
//            int ret = recv(acptSockFd, tcpBuffer, MSG_LEN, MSG_WAITALL);
            ssize_t ret = recvfrom(acptSockFd, this->tcpBuffer, MSG_LEN, MSG_DONTWAIT, NULL, NULL);
            if (ret <= 0) {
                if (errno == EAGAIN) continue;
                zlog_debug(this->log, "Receive message error code: %d, %s", errno, strerror(errno));
                memset(this->tcpBuffer, 0, MSG_LEN);
                usleep(10);
                break;
            }
            newMsg = std::string((char *) this->tcpBuffer);
            zlog_debug(this->log, "New clipboard content, %s", newMsg.c_str());
            if (newMsg == oldMsg) {
//                zlog_debug(this->log, "New clipboard content, %s", newMsg.c_str());
                memset(this->tcpBuffer, 0, MSG_LEN);
                usleep(10);
                continue;
            }
            oldMsg = newMsg;
            setTcpMsg(newMsg);
            memset(this->tcpBuffer, 0, MSG_LEN);
            usleep(10);
        }
    }
    return 0;
}

int Transmission::sendData() {
    return 0;
}

const std::string &Transmission::getMsg() const {
    return tcpMsg;
}

int Transmission::rcvDataUDP() {
    std::thread clipRcvThread(&Transmission::clipThreadFun, this);
    clipRcvThread.join();
    return 0;
}

void Transmission::setTcpMsg(const std::string &msg) {
    Transmission::tcpMsg = msg;
}

void Transmission::setUdpMsg(const std::string &msg) {
    /* Resolve the string msg to Class Message */
    Transmission::udpMsg = this->cipher.decrypt(msg);
    Message message;
    message.resolveRcvMsg(Transmission::udpMsg, this->log);
    this->rcvMsgQueue.push(message);
}
