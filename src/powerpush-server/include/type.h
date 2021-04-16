//
// Created by faniche on 4/7/21.
//

#ifndef POWERPUSH_SERVER_TYPE_H
#define POWERPUSH_SERVER_TYPE_H
#include <string>
#include <resolv.h>
#include <set>
#include <vector>

#
#include "env.h"

struct GroupItem{
    std::string groupId;
    std::string groupToken;
};

struct DeviceItem{
    std::string deviceId;
    std::string deviceIP;
    in_port_t devicePort = 0;
};

struct DeviceListItem{
    std::string groupId;
    std::vector<DeviceItem> deviceList;
};

struct ClipboardListItem{
    std::string groupId;
    std::vector<std::string> clipboardList;
};





#endif //POWERPUSH_SERVER_TYPE_H
