CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
project(client)

set(BINARY ${CMAKE_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

add_executable(${BINARY} main.cpp)

add_subdirectory(Client)

include_directories(Client)

target_link_libraries(${BINARY} PUBLIC
                      ${BINARY}_client)
