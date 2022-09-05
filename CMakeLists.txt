cmake_minimum_required(VERSION 2.8.12)
project(csockets)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


add_executable(ctest src/main.c)
target_link_libraries(ctest ${CONAN_LIBS})

add_executable(server src/server.c)
target_link_libraries(server ${CONAN_LIBS})

add_executable(client src/client.c)
target_link_libraries(client ${CONAN_LIBS})

