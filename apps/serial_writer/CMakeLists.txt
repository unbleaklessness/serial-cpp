cmake_minimum_required(VERSION 3.0)

set(NAME serial_writer)

add_executable(${NAME} main.cpp)

target_include_directories(${NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(${NAME} PRIVATE serial_cpp)

install(TARGETS ${NAME} DESTINATION "${CMAKE_INSTALL_BINDIR}")