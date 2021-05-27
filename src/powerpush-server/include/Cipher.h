//
// Created by faniche on 4/17/21.
//

#ifndef POWERPUSH_SERVER_CIPHER_H
#define POWERPUSH_SERVER_CIPHER_H

#include <openssl/aes.h>
#include <string>

class Cipher {
private:
    std::string method;
    std::string key;
    std::string message;

    void aes_encrypt();


public:
    [[nodiscard]] const std::string &getMethod() const;

    void setMethod(const std::string &method);

    [[nodiscard]] const std::string &getKey() const;

    void setKey(const std::string &key);

    std::string encrypt(const std::string &planText);

    std::string decrypt(const std::string &cipherText);

};


#endif //POWERPUSH_SERVER_CIPHER_H
