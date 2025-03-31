#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BROADCAST_PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in listen_addr;
    char buffer[BUFFER_SIZE];
    ssize_t num_bytes_received;
    socklen_t addr_len = sizeof(listen_addr);

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the listen address struct
    memset(&listen_addr, 0, sizeof(listen_addr));
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_port = htons(BROADCAST_PORT);
    listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the port
    if (bind(sockfd, (struct sockaddr*)&listen_addr, sizeof(listen_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Listening for broadcast messages on port %d...\n", BROADCAST_PORT);

    while (1) {
        // Receive broadcast message
        num_bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&listen_addr, &addr_len);
        if (num_bytes_received < 0) {
            perror("Receive failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        // Null-terminate the received data
        buffer[num_bytes_received] = '\0';

        // Print the received message
        printf("Received broadcast message: %s\n", buffer);
    }

    // Close the socket
    close(sockfd);

    return 0;
}