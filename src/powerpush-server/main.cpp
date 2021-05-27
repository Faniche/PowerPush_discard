#include <iostream>
#include <cstring>
#include <queue>
#include "zlog.h"
#include "include/Transmission.h"
#include "include/Config.h"
using namespace std;

int main() {
    int logfile_fd = zlog_init("/etc/zlog/powerpush.conf");
    if (logfile_fd != 0) {
        std::cerr << "Init log file error " << strerror(errno) << std::endl;
    }
    zlog_category_t *log;
    log = zlog_get_category("powerpush");
    if (!log) {
        std::cerr << "Log get category failed ..." << strerror(errno) << std::endl;
        zlog_fini();
    }

    std::queue<Message> rcvMsgQueue;
    std::queue<Message> sndMsgQueue;
//    Message message(log);
//    message.setDeviceId("11");
//    message.setGroupId("ss");
//    message.setGroupToken("aa");
//    message.setMessageType(1);
//    message.setPayload("aa");
//    rcvMsgQueue.push(message);
//    sndMsgQueue.push(message);


    Config config(CONF_FILE_PATH, log);

    Cipher cipher;

    Transmission transmission(log, cipher, config, rcvMsgQueue, sndMsgQueue);
    transmission.initSocket();
//    transmission.rcvDataTCP();
    transmission.rcvDataUDP();

    std::string msg = transmission.getMsg();
    msg = cipher.decrypt(msg);


    return 0;
}
