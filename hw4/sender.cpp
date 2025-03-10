#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    // Get user input
    std::string ip, program_id, message;
    std::cout << "Enter IP address (e.g., 192.2.1.8 or 127.0.0.1): ";
    std::getline(std::cin, ip);
    std::cout << "Enter Program ID (e.g., 1): ";
    std::getline(std::cin, program_id);
    std::cout << "Enter message: ";
    std::getline(std::cin, message);

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        return 1;
    }

    // Set up server address
    serv_addr.sin_family = AF_INET;
    int port = (program_id == "1") ? 5001 : 5001; // Default to 5001 for simplicity
    serv_addr.sin_port = htons(port);

    // Convert IP address
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address" << std::endl;
        return 1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        return 1;
    }

    // Send message
    send(sock, message.c_str(), message.length(), 0);
    std::cout << "Message sent successfully!" << std::endl;

    close(sock);
    return 0;
}