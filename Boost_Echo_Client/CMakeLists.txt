cmake_minimum_required(VERSION 3.10)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS system filesystem thread REQUIRED)

IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lboost_thread")

include_directories(bin)
include_directories(include)
include_directories(src)
add_executable(Boost_Echo_Client
        include/ConnectionHandler.h
        src/ConnectionHandler.cpp
        src/Database.cpp
        src/InputProcessor.cpp
        include/InputProcessor.h
        include/Database.h
        src/Protocol.cpp
        include/Protocol.h
        src/StompFrame.cpp
        include/StompFrame.h
        src/StompClient.cpp
        include/ServerTask.h
        src/ServerTask.cpp)
target_link_libraries(Boost_Echo_Client LINK_PUBLIC ${Boost_LIBRARIES} )