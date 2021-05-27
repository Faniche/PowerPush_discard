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

    in_port_t udpPort;

    in_port_t tcpPort;

    void readConfig(const std::string& confFilePath);


public:
    Config();

    Config(const std::string& confFilePath, zlog_category_t *log);

    json_object *getParsedJson() const;

    void setParsedJson(json_object *parsedJson);

    [[nodiscard]] const std::vector<struct GroupItem> &getGroupList() const;

    void setGroupList(const std::vector<struct GroupItem> &groupList);

    [[nodiscard]] const std::vector<struct DeviceListItem> &getDeviceList() const;

    void setDeviceList(const std::vector<struct DeviceListItem> &deviceList);

    [[nodiscard]] const std::vector<struct ClipboardListItem> &getClipboardContentList() const;

    void setClipboardContentList(const std::vector<struct ClipboardListItem> &clipboardContentList);

    void setLog(zlog_category_t *log);

    [[nodiscard]] in_port_t getUdpPort() const;

    void setUdpPort(in_port_t udpPort);

    [[nodiscard]] in_port_t getTcpPort() const;

    void setTcpPort(in_port_t tcpPort);

};


#endif //POWERPUSH_SERVER_CONFIG_H
