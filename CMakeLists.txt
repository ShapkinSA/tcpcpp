cmake_minimum_required(VERSION 3.28)
project(Tcp)

set(CMAKE_CXX_STANDARD 17)

include(CMakeLists.macro.cmake)

DOWNLOAD_REPOSITORY_FROM_GIT("nlohmann" "develop" "https://github.com/nlohmann/json")


BUILD_LIBRARY_FROM_OWN_CODE("src" "src")


add_executable(server server.cpp)
add_executable(client client.cpp)
add_executable(test test.cpp)

target_link_libraries(server src)
target_link_libraries(client src)
target_link_libraries(test src)

#add_executable(server server.cpp
#        src/utils/Serialization.h
#        src/model/TcpServer.h
#        src/model/TcpServer.cpp
#        src/messageBoxModel/MessageBox.h
#)
#
#add_executable(client client.cpp
#        src/utils/Serialization.h
#        src/model/TcpClient.h
#        src/model/TcpClient.cpp
#        src/messageBoxModel/MessageBox.h
#)
#
#add_executable(testOwnProtobuff testOwnProtobuff.cpp)
#
#
#add_executable(test test.cpp
#        src/utils/Serialization.h
#        src/model/TcpServer.h
#        src/model/TcpServer.cpp
#        src/model/TcpClient.h
#        src/model/TcpClient.cpp
#        src/messageBoxModel/MessageBox.h
#)


