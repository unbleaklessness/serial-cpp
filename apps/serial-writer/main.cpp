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

        std::cout << "Write strings with size no more than " << buffer_size << " characters." << std::endl;

        while (1) {
            std::cin >> buffer;

            ssize_t n = port->write(buffer, buffer_size);

            std::cout << "Bytes written: " << n << std::endl;
            std::fill_n(buffer, buffer_size, 0);

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    } else {
        std::cout << "ERROR: Specify serial port as the first argument!" << std::endl;
    }

    return 0;
}