//
// Created by faniche on 4/19/21.
//

#include "include/Buffer.h"

void *Buffer::getBuf() const {
    return buf;
}

void Buffer::setBuf(void *buffer) {
    Buffer::buf = buffer;
}

int Buffer::getWPtr() const {
    return wPtr;
}

void Buffer::setWPtr(int wrtPtr) {
    Buffer::wPtr = wrtPtr;
}

int Buffer::getRPtr() const {
    return rPtr;
}

void Buffer::setRPtr(int readPtr) {
    Buffer::rPtr = readPtr;
}
