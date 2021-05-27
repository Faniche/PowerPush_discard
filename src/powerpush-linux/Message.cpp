//
// Created by faniche on 3/22/21.
//

#include "../powerpush-linux/include/Message.h"

/* Public */
Message::Message() {
    this->messageType = 0;
}

const std::string &Message::getDeviceId() const {
    return deviceId;
}

void Message::setDeviceId(const std::string &_deviceId) {
    Message::deviceId = _deviceId;
}

const std::string &Message::getGroupId() const {
    return groupId;
}

void Message::setGroupId(const std::string &_groupId) {
    Message::groupId = _groupId;
}

const std::string &Message::getGroupToken() const {
    return groupToken;
}

void Message::setGroupToken(const std::string &_groupToken) {
    Message::groupToken = _groupToken;
}

int Message::getMessageType() const {
    return messageType;
}

void Message::setMessageType(int _messageType) {
    Message::messageType = _messageType;
}


const std::string &Message::getPayload() const {
    return payload;
}

void Message::setPayload(const std::string &_payload) {
    Message::payload = _payload;
}

bool Message::resolveRcvMsg(const std::string &_msg, zlog_category_t *log) {
    struct json_object *jmsg = json_object_new_string(_msg.c_str());
    struct json_object *jdeviceId, *jmsgType, *jpaylaod, *jgroupId, *jgroupToken, *jclipboardList, *jdeviceList;
    if(json_object_object_get_ex(jmsg, "device_id", &jdeviceId) == false) {
        zlog_debug(log, "Something error");
        return false;
    }
    this->deviceId = json_object_get_string(jdeviceId);

    if(json_object_object_get_ex(jmsg, "msg_type", &jmsgType) == false) {
        zlog_debug(log, "Something error");
        return false;
    }
    this->messageType = json_object_get_int(jmsgType);
    if (this->messageType == GROUP_CREATE)
        return true;

    if(json_object_object_get_ex(jmsg, "group_id", &jgroupId) == false) {
        zlog_debug(log, "Something error");
        return false;
    }
    this->groupId = json_object_get_string(jgroupId);

    if(json_object_object_get_ex(jmsg, "group_token", &jgroupToken)== false) {
        zlog_debug(log, "Something error");
        return false;
    }
    this->groupToken = json_object_get_string(jgroupToken);

    if (this->messageType == CLIPBOARD_PUSH) {
        if(json_object_object_get_ex(jmsg, "payload", &jpaylaod) == false) {
            zlog_debug(log, "Something error");
            return false;
        }
        this->payload = json_object_get_string(jpaylaod);
    }
    return true;
}
