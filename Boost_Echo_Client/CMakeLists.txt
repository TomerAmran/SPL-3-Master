cmake_minimum_required(VERSION 3.10)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS system filesystem thread REQUIRED)

IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lboost_thread")

include_directories(bin)
include_directories(include)
include_directories(src)
add_executable(Boost_Echo_Client
        include/connectionHandler.h
        src/connectionHandler.cpp
        src/echoClient.cpp
        src/Inventory.cpp include/Inventory.h src/StompFrame.cpp include/StompFrame.h)
target_link_libraries(Boost_Echo_Client LINK_PUBLIC ${Boost_LIBRARIES} )
