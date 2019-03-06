cmake_minimum_required(VERSION 3.0)

set(NAME serial_cpp)

add_library(${NAME} STATIC SHARED serial.cpp)

target_include_directories(${NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/include/${NAME}"
        PRIVATE "${PROJECT_SOURCE_DIR}/src/${NAME}")

install(TARGETS ${NAME} DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/${NAME}" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")