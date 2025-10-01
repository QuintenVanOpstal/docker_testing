#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define SERIAL_PORT "/dev/ttyACM0"  // Change to your ESP32's port
#define BAUD_RATE B115200

int serial_fd;

int serial_init(const char* port, int baudrate) {
    serial_fd = open(port, O_RDWR | O_NOCTTY);
    if (serial_fd == -1) {
        perror("Error opening serial port");
        return -1;
    }
    
    struct termios options;
    tcgetattr(serial_fd, &options);
    
    // Set baud rate
    cfsetispeed(&options, baudrate);
    cfsetospeed(&options, baudrate);
    
    // Configure serial port options
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    
    // Set timeouts
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 1; // 0.1 second timeout
    
    tcsetattr(serial_fd, TCSANOW, &options);
    
    printf("Serial port %s opened successfully at %d baud\n", port, baudrate);
    return 0;
}

int read_integer() {
    char buffer[256];
    char *endptr;
    int value = -1;
    
    // Read data from serial port
    int bytes_read = read(serial_fd, buffer, sizeof(buffer) - 1);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        
        // Try to convert to integer
        value = strtol(buffer, &endptr, 10);
        
        // Check if conversion was successful
        if (endptr == buffer) {
            printf("Received non-integer data: %s", buffer);
            return -1;
        }
    }
    
    return value;
}

void serial_close() {
    close(serial_fd);
}

int main() {
    if (serial_init(SERIAL_PORT, BAUD_RATE) != 0) {
        return 1;
    }
    int distance =4; //mm    
    printf("Listening for integers from ESP32. Press Ctrl+C to exit.\n");
    
    while (1) {
        int received_value = read_integer();
        
        if (received_value != -1) {
            printf("recorded distance %d mm\n", received_value * distance);
        }
        
        usleep(10000); // 10ms delay
    }
    
    serial_close();
    return 0;
}
