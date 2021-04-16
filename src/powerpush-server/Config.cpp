//
// Created by faniche on 3/23/21.
//

#include "include/Config.h"

/* Public */
Config::Config(const std::string& confFilePath, zlog_category_t *log) {
    this->log = log;
    zlog_debug(this->log, "Config path: %s", confFilePath.c_str());
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
    zlog_debug(this->log, "test");
}

