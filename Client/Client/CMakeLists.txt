set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.hpp *.cpp)

add_library(${BINARY}_client STATIC ${SOURCES})

find_package(cpprestsdk)
target_link_libraries(${BINARY}_client cpprestsdk::cpprest)
