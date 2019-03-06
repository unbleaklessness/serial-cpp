#pragma once

#include <string>
#include <termios.h>

class serial {
public:
    /**
     * Opens a serial port for read/write. By default baud rate is set to 9600.
     * @param port_name Name of the port (for example: "/dev/ttyUSB0" on linux or "COM0" on windows).
     * @param speed Read-write speed (baud rate). Use speed defines from "termios.h": B9600, B115200...
     */
    explicit serial(const std::string &port_name, const speed_t &speed = B9600);

    /**
     * Write to the serial port.
     * @param message Message to write.
     * @param message_size Size of the message in bytes.
     * @return Number of bytes written.
     */
    ssize_t write(const char *message, size_t message_size);

    /**
     * Read from the serial port. Will read from the serial until the `buffer` fills up.
     * @param buffer Output buffer.
     * @param buffer_size Size of the output buffer in bytes.
     */
    void read(char *buffer, size_t buffer_size);

    /**
     * Set baud rate for the serial port.
     * @param speed Baud rate value. Use speed defines from "termios.h": B9600, B115200...
     */
    void set_speed(speed_t speed);

private:
    std::string tty_path;
    int file_descriptor;
    speed_t speed = B9600;
};
