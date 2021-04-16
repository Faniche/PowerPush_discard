cmake_minimum_required(VERSION 3.17)
project(powerpush_server)

set(CMAKE_CXX_STANDARD 20)

add_executable(powerpush_server
        main.cpp
        include/env.h
        Transmission.cpp include/Transmission.h Message.cpp include/Message.h Config.cpp include/Config.h include/type.h)

# Disable clip examples and tests
set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")

# In case that you have ${PNG_LIBRARY} set to support copy/paste images on Linux
#set(CLIP_X11_PNG_LIBRARY "${PNG_LIBRARY}")

# Add clip subdirectory to compile the library
add_subdirectory(clip)

target_link_libraries(powerpush_server
        clip
        zlog -ldl
        json-c -ldl)