#!/bin/bash

# install zlog lib
git clone https://github.com/HardySimpson/zlog.git
cd zlog
make && sudo make install
rm -r zlog

git clone https://github.com/json-c/json-c.git
mkdir json-c-build && cd json-c-build && cmake ../json-c && make && sudo make install

