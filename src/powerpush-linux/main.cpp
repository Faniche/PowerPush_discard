#include <iostream>
#include <zconf.h>
#include <cstring>
#include "include/Transmission.h"
#include "clip/clip.h"
#include "zlog.h"

#define PAYLOAD_LEN 946
#define INDEX_LEN 10
#define ASYNC_DATA_LEN 50
#define LAST_CHAR 1
#define TOTAL_SND_PKE_NUM 20

int main() {
    int logfile_fd = zlog_init("/etc/zlog/powerpush.conf");
    if (logfile_fd) {
        std::cerr << "Init log file error" << strerror(errno) << std::endl;
    }
    zlog_category_t *log;
    log = zlog_get_category("powerpush");
    if (!log) {
        std::cerr << "Log get category failed ..." << strerror(errno) << std::endl;
        zlog_fini();
    }
    Transmission transmission(log);
    transmission.initSocket();
    std::string oldClip;
    std::string newClip;

    /* Test */
    char data[PAYLOAD_LEN];
    char content[PAYLOAD_LEN - INDEX_LEN];
    int content_len = PAYLOAD_LEN - INDEX_LEN - LAST_CHAR;
    for (int i = 0; i < content_len; ++i) {
        if (i < PAYLOAD_LEN - ASYNC_DATA_LEN - INDEX_LEN) {
            sprintf(content + i, "%s", "a");
            continue;
        }
        sprintf(content + i, "%s", "b");
    }
    if (LAST_CHAR) {
        sprintf(content + PAYLOAD_LEN - INDEX_LEN - 1, "\n");
    }

    for (int i = 0; i < TOTAL_SND_PKE_NUM + 50; ++i) {
        sprintf(data, "%09d-", i);
        strcpy(data + INDEX_LEN, content);
        clip::set_text(data);
        newClip = std::string(data);
        oldClip = newClip;
        transmission.setMsg(newClip);
        if (!transmission.sendData()) break;
        usleep(20);
    }
    /* End test */


//    while (true) {
//        clip::get_text(newClip);
//        if (oldClip == newClip) {
//            usleep(50);
//            continue;
//        }
//        oldClip = newClip;
//        transmission.setMsg(newClip);
//        if (!transmission.sendData()) break;
//        usleep(50);
//    }

    return 0;
}
