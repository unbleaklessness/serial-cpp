#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "serialcpp/serial.h"

int main(int argc, char **argv) {
    if (argc > 1) {
        auto port = new serial(argv[1], B115200);

        const size_t buffer_size = 64;
        char *buffer = new char[buffer_size]();

        while (1) {
            port->read(buffer, buffer_size);

            std::cout << std::string(buffer, buffer_size);
            std::fill_n(buffer, buffer_size, 0);

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    } else {
        std::cout << "ERROR: Specify serial port as the first argument!" << std::endl;
    }

    return 0;
}