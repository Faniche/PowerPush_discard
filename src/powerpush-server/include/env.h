//
// Created by faniche on 12/27/20.
//

#ifndef POWERPUSH_SERVER_ENV_H
#define POWERPUSH_SERVER_ENV_H

#define TRANS_LISTEN_QSIZE 10

#define CONF_FILE_PATH "/etc/powerpush/server.json"

#define MSG_LEN 946

#define UDP_RCV_MSG_NUM 1000

#define UDP_SND_MSG_NUM 1000

#define GROUP_CREATE 1

#define GROUP_CREATE_REPLY 2

#define GROUP_JOIN 3

#define GROUP_JOIN_AGREE 4

#define ALIVE 5

#define CLIPBOARD_SYNC 6

#define CLIPBOARD_PUSH 7

#define CLIPBOARD_ACK 8

#define CLIPBOARD_FORWARD 9

#define CLIPBOARD_PULL 10



#endif //POWERPUSH_SERVER_ENV_H
