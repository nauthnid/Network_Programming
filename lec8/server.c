#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t n;

    while ((n = read(client_socket, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[n] = '\0';  // Null-terminate the buffer
        printf("Received: %s", buffer);
        write(client_socket, buffer, n);  // Echo the message back to the client
    }

    close(client_socket);
    exit(0);  // Terminate the child process
}

void sigchld_handler(int s) {
    // Wait for all dead processes
    // We use a loop to handle all children that have terminated
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    pid_t pid;

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Allow the server to reuse the address
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the address and port number
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) == -1) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Handle SIGCHLD to prevent zombie processes
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;  // Reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_addr_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        // Fork a new process to handle the client
        pid = fork();
        if (pid == -1) {
            perror("fork");
            close(client_socket);
            continue;
        }

        if (pid == 0) {  // Child process
            close(server_socket);  // Close the listening socket in the child process
            handle_client(client_socket);
        } else {  // Parent process
            close(client_socket);  // Close the client socket in the parent process
        }
    }

    // Close the server socket
    close(server_socket);

    return 0;
}
