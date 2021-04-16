#include <iostream>
#include <thread>
#include <cstring>
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

    Config config(CONF_FILE_PATH, log);


//    Transmission transmission(log);
//    transmission.initSocket();
//    transmission.rcvDataTCP();
//    transmission.rcvDataUDP();
//    std::string clipContent;
//    clip::get_text(clipContent);
//    std::cout << clipContent << std::endl;


    return 0;
}
