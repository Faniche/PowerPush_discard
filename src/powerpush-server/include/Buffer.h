//
// Created by faniche on 4/19/21.
//

#ifndef POWERPUSH_SERVER_BUFFER_H
#define POWERPUSH_SERVER_BUFFER_H


class Buffer {
private:
    void *buf;
    int wPtr;
    int rPtr;

public:
    [[nodiscard]] void *getBuf() const;

    void setBuf(void *buf);

    [[nodiscard]] int getWPtr() const;

    void setWPtr(int wPtr);

    [[nodiscard]] int getRPtr() const;

    void setRPtr(int rPtr);
};


#endif //POWERPUSH_SERVER_BUFFER_H
