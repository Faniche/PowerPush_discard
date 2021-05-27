//
// Created by faniche on 4/17/21.
//

#include "include/Cipher.h"

/* private */
void Cipher::aes_encrypt() {

}


const std::string &Cipher::getMethod() const {
    return method;
}

void Cipher::setMethod(const std::string &method) {
    Cipher::method = method;
}

const std::string &Cipher::getKey() const {
    return key;
}

void Cipher::setKey(const std::string &key) {
    Cipher::key = key;
}

std::string Cipher::encrypt(const std::string &planText) {
    this->message = planText;
    /* Encrypting ... */

    return this->message;
}

std::string Cipher::decrypt(const std::string &cipherText) {
    this->message = cipherText;
    /* Decrypting ... */


    return this->message;
}

/*testtesttesttesttesttesttesttesttesttesttesttesttest*/
/*testtesttesttesttesttesttesttesttesttesttesttesttest*/
/*testtesttesttesttesttesttesttesttesttesttesttesttest*/