#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    const char* ip = std::getenv("WS_SERVER_IP");
    const char* port = std::getenv("WS_SERVER_PORT");

    if (!ip || !port) {
        std::cerr << "Missing WS_SERVER_IP or WS_SERVER_PORT env variables." << std::endl;
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(std::stoi(port));
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        std::perror("Invalid IP address");
        close(sockfd);
        return 1;
    }

    std::cout << "UDP Sender started, sending to " << ip << ":" << port << std::endl;

    for (int i = 0; ; ++i) {
        int number_to_send = htonl(i);
        ssize_t sent = sendto(sockfd, &number_to_send, sizeof(number_to_send), 0,
                              (struct sockaddr*)&server_addr, sizeof(server_addr));
        if (sent < 0) {
            std::perror("Send failed");
        } else {
            std::cout << "Sent: " << i << std::endl;
        }
        sleep(1);
    }

    close(sockfd);
    return 0;
}

