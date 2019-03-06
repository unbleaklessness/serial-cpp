#include "serial.h"

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <serial.h>

serial::serial(const std::string &port_name, const speed_t &speed) {
    this->tty_path = port_name;
    this->speed = speed;

    file_descriptor = open(this->tty_path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

    set_speed(this->speed);
}

ssize_t serial::write(const char *message, size_t message_size) {
    ssize_t n_written = 0;
    ssize_t spot = 0;

    do {
        n_written = ::write(file_descriptor, &message[spot], 1);
        spot += n_written;
    } while (spot < message_size && n_written > 0);

    return spot;
}

void serial::read(char *buffer, size_t buffer_size) {
    ssize_t n_received = 0;
    ssize_t spot = 0;

    do {
        n_received = ::read(file_descriptor, &buffer[spot], 1);
        spot += n_received;
    } while (spot < buffer_size);
}

void serial::set_speed(speed_t speed) {
    this->speed = speed;

    termios tty {};
    memset(&tty, 0, sizeof(tty));

    /* Error handling: */
    if (tcgetattr(file_descriptor, &tty) != 0) {
        std::cout << "Error " << errno << " from Serial class: " << strerror(errno) << std::endl;
    }

    /* Set baud rate: */
    cfsetospeed(&tty, static_cast<speed_t>(this->speed)); // Output speed.
    cfsetispeed(&tty, static_cast<speed_t>(this->speed)); // Input speed.

    /* Setting other port stuff: */
    tty.c_cflag     &=  ~PARENB;            // Make 8n1.
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;
    tty.c_cflag     &=  ~CRTSCTS;           // No flow control.
    tty.c_cc[VMIN]   =  1;                  // Read doesn't block.
    tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout.
    tty.c_cflag     |=  CREAD | CLOCAL;     // Turn on READ, ignore CTRL lines.

    /* Make raw: */
    cfmakeraw(&tty);

    /* Flush Port, then applies attributes: */
    tcflush(file_descriptor, TCIFLUSH);
    if (tcsetattr(file_descriptor, TCSANOW, &tty) != 0) {
        std::cout << "Error " << errno << " from Serial class" << std::endl;
    }
}

