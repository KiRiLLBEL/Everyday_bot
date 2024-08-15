cmake_minimum_required(VERSION 3.20)
project(everyday_bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

set(SECRET_FILE_PATH "${CMAKE_SOURCE_DIR}/secrets.cmake")

if(EXISTS "${SECRET_FILE_PATH}")
    include("${SECRET_FILE_PATH}")
else()
    message(WARNING "Secrets file not found! Please create a 'secrets.cmake' file.")
endif()

add_executable(everyday_bot src/main.cpp)

target_link_libraries(everyday_bot ${TGBOT_LIB_PATH} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})