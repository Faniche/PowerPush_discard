//
// Created by faniche on 3/22/21.
//

#ifndef POWERPUSH_SERVER_MESSAGE_H
#define POWERPUSH_SERVER_MESSAGE_H

#include "env.h"
#include <string>
#include <map>
#include <vector>
#include <json-c/json.h>
#include <openssl/sha.h>
#include <zlog.h>

class Message {
private:
    std::string deviceId;
    std::string groupId;
    std::string groupToken;
    int messageType;
    std::string payload;
    uint16_t msgLen;

public:
    explicit Message();

    [[nodiscard]] const std::string &getDeviceId() const;

    void setDeviceId(const std::string &_deviceId);

    [[nodiscard]] const std::string &getGroupId() const;

    void setGroupId(const std::string &_groupId);

    [[nodiscard]] const std::string &getGroupToken() const;

    void setGroupToken(const std::string &_groupToken);

    [[nodiscard]] int getMessageType() const;

    void setMessageType(int _messageType);

    [[nodiscard]] const std::string &getPayload() const;

    void setPayload(const std::string &_payload);

    bool resolveRcvMsg(const std::string &_msg, zlog_category_t *log);
};


#endif //POWERPUSH_SERVER_MESSAGE_H
