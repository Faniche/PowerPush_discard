//
// Created by faniche on 3/23/21.
//

#ifndef POWERPUSH_SERVER_CONFIG_H
#define POWERPUSH_SERVER_CONFIG_H

#include "env.h"
#include "type.h"
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <json-c/json.h>
#include <zlog.h>

class Config {
private:

    struct json_object *parsed_json;

    struct json_object *jgroupList;

    struct json_object *jdeviceList;

    struct json_object *jclipboardContentList;

    std::vector<struct GroupItem> groupList;

    std::vector<struct DeviceListItem> deviceList;

    std::vector<struct ClipboardListItem> clipboardContentList;

    zlog_category_t *log;

    void readConfig();


public:
    Config(const std::string& confFilePath, zlog_category_t *log);


};


#endif //POWERPUSH_SERVER_CONFIG_H
