#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr{}, client_addr{};
    socklen_t client_len = sizeof(client_addr);
    int received_int;

    // Get UDP port from environment, default to 8080
    const char* port_env = std::getenv("WS_SERVER_PORT");
    std::string port_str = port_env ? port_env : "8080";

    // Always listen on all interfaces (includes tailscale0 now)
    const char* bind_ip = "0.0.0.0";

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::perror("Socket creation failed");
        return 1;
    }

    // Allow address reuse (prevents "Address already in use" after restart)
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Prepare server address
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(std::stoi(port_str));
    server_addr.sin_addr.s_addr = INADDR_ANY;  // listen on all interfaces

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::perror("Bind failed");
        close(sockfd);
        return 1;
    }

    std::cout << "UDP Receiver listening on 0.0.0.0:" << port_str
              << std::endl;

    // Main loop: receive and print integers
    while (true) {
        int bytes_received = recvfrom(sockfd, &received_int, sizeof(received_int), 0,
                                      (struct sockaddr*)&client_addr, &client_len);
        if (bytes_received < 0) {
            std::perror("Receive failed");
            continue;
        }

        received_int = ntohl(received_int);
        std::cout << "Received: " << received_int << std::endl;
    }

    close(sockfd);
    return 0;
}

