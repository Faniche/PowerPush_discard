//
// Created by faniche on 3/23/21.
//

#include "include/Config.h"


void Config::readConfig(const std::string& confFilePath) {
    parsed_json = json_object_from_file(confFilePath.c_str());
    struct json_object_iterator it, itEnd;
    this->jgroupList = json_object_object_get(parsed_json, "groups");
    if (this->jgroupList != nullptr) {
        struct GroupItem groupItem;
        it = json_object_iter_begin(this->jgroupList);
        itEnd = json_object_iter_end(this->jgroupList);
        while (!json_object_iter_equal(&it, &itEnd)) {
            groupItem.groupId = json_object_iter_peek_name(&it);
            groupItem.groupToken = json_object_get_string(json_object_iter_peek_value(&it));
            this->groupList.push_back(groupItem);
            json_object_iter_next(&it);
        }
    }

    this->jdeviceList = json_object_object_get(parsed_json, "device_list");
    if (this->jdeviceList != nullptr) {
        it = json_object_iter_begin(this->jdeviceList);
        itEnd = json_object_iter_end(this->jdeviceList);
        while (!json_object_iter_equal(&it, &itEnd)) {
            struct DeviceListItem deviceListItem;
            deviceListItem.groupId = json_object_iter_peek_name(&it);
            struct json_object *jDeviceListItem = json_tokener_parse(json_object_get_string(json_object_iter_peek_value(&it)));
            for (int i = 0; i < json_object_array_length(jDeviceListItem); ++i) {
                struct DeviceItem deviceItem;
                struct json_object *jDeviceItem = json_object_array_get_idx(jDeviceListItem, i);
                deviceItem.deviceId = json_object_get_string(json_object_object_get(jDeviceItem, "device_id"));
                deviceItem.deviceIP = json_object_get_string(json_object_object_get(jDeviceItem, "device_ip"));
                deviceItem.devicePort = json_object_get_int(json_object_object_get(jDeviceItem, "device_id"));
                deviceListItem.deviceList.push_back(deviceItem);
            }
            this->deviceList.push_back(deviceListItem);
            json_object_iter_next(&it);
        }
    }

    this->jclipboardContentList = json_object_object_get(parsed_json, "clipboard_list");
    if (this->jclipboardContentList != nullptr) {
        it = json_object_iter_begin(this->jclipboardContentList);
        itEnd = json_object_iter_end(this->jclipboardContentList);
        while (!json_object_iter_equal(&it, &itEnd)) {
            struct ClipboardListItem clipboardListItem;
            clipboardListItem.groupId = json_object_iter_peek_name(&it);
            struct json_object *ClipboardListItem = json_tokener_parse(json_object_get_string(json_object_iter_peek_value(&it)));
            for (int i = 0; i < json_object_array_length(ClipboardListItem); ++i) {
                std::string clipItem = json_object_get_string(json_object_array_get_idx(ClipboardListItem, i));
                clipboardListItem.clipboardList.push_back(clipItem);
            }
            this->clipboardContentList.push_back(clipboardListItem);
            json_object_iter_next(&it);
        }
    }

    this->udpPort = json_object_get_int(json_object_object_get(parsed_json, "udp_port"));
    this->tcpPort = json_object_get_int(json_object_object_get(parsed_json, "tcp_port"));
}

/* Public */
/* If use the no params constructor, must set log manually */
Config::Config() {
    readConfig(CONF_FILE_PATH);
}

Config::Config(const std::string& confFilePath, zlog_category_t *log) {
    this->log = log;
    readConfig(confFilePath);
}

json_object *Config::getParsedJson() const {
    return parsed_json;
}

void Config::setParsedJson(json_object *parsedJson) {
    parsed_json = parsedJson;
}

const std::vector<struct GroupItem> &Config::getGroupList() const {
    return groupList;
}

void Config::setGroupList(const std::vector<struct GroupItem> &groupList) {
    Config::groupList = groupList;
}

const std::vector<struct DeviceListItem> &Config::getDeviceList() const {
    return deviceList;
}

void Config::setDeviceList(const std::vector<struct DeviceListItem> &deviceList) {
    Config::deviceList = deviceList;
}

const std::vector<struct ClipboardListItem> &Config::getClipboardContentList() const {
    return clipboardContentList;
}

void Config::setClipboardContentList(const std::vector<struct ClipboardListItem> &clipboardContentList) {
    Config::clipboardContentList = clipboardContentList;
}

in_port_t Config::getUdpPort() const {
    return udpPort;
}

void Config::setUdpPort(in_port_t udpPort) {
    Config::udpPort = udpPort;
}

in_port_t Config::getTcpPort() const {
    return tcpPort;
}

void Config::setTcpPort(in_port_t tcpPort) {
    Config::tcpPort = tcpPort;
}

void Config::setLog(zlog_category_t *log) {
    Config::log = log;
}


