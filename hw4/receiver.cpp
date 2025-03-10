#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        std::cerr << "Socket failed" << std::endl;
        return 1;
    }

    // Set up address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    address.sin_port = htons(5001);       // Port 5001 for Program ID 1

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0)
    {
        std::cerr << "Listen failed" << std::endl;
        return 1;
    }

    std::cout << "Receiver listening on port 5001..." << std::endl;

    while (true)
    {
        // Accept a connection
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (client_fd < 0)
        {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }

        // Read message
        read(client_fd, buffer, 1024);
        std::cout << "Received message: " << buffer << std::endl;

        // Clear buffer
        memset(buffer, 0, 1024);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}