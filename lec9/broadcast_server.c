#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define BROADCAST_IP "192.168.0.255"
#define BROADCAST_PORT 8888
#define BUFFER_SIZE 1024
#define SLEEP_INTERVAL 10

int main() {
    int sockfd;
    struct sockaddr_in broadcast_addr;
    int broadcast_enable = 1;
    char buffer[BUFFER_SIZE];
    time_t rawtime;
    struct tm * timeinfo;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options to enable broadcasting
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) < 0) {
        perror("Error in setting broadcast option");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Set up the broadcast address struct
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(BROADCAST_PORT);
    broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);

    while (1) {
        // Get current time
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        // Format the time into the buffer
        strftime(buffer, BUFFER_SIZE, "Current time: %Y-%m-%d %H:%M:%S", timeinfo);

        // Send broadcast message
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr)) < 0) {
            perror("Broadcast message send failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        printf("Broadcast message sent: %s\n", buffer);

        // Sleep for the defined interval
        sleep(SLEEP_INTERVAL);
    }

    // Close the socket
    close(sockfd);

    return 0;
}