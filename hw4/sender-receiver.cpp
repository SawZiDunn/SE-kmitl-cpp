#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <fcntl.h>

class CombinedProgram
{
private:
    int program_id;
    int listen_port;
    std::atomic<bool> is_receiving;
    std::thread receive_thread;

    // Function to map program ID to port
    int mapProgramIdToPort(int id)
    {
        return 5000 + id;
    }

    // Function to receive messages
    void receiveMessages()
    {
        int server_fd, client_fd;
        struct sockaddr_in address;
        int addrlen = sizeof(address);
        char buffer[1024] = {0};

        // Create socket
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == 0)
        {
            std::cerr << "Socket creation failed" << std::endl;
            return;
        }

        // Set socket options to allow reuse of address/port
        int opt = 1;
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        {
            std::cerr << "Set socket options failed" << std::endl;
            close(server_fd);
            return;
        }

        // Set up address
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
        address.sin_port = htons(listen_port);

        // Bind socket
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
            std::cerr << "Bind failed on port " << listen_port << std::endl;
            close(server_fd);
            return;
        }

        // Listen for connections
        if (listen(server_fd, 3) < 0)
        {
            std::cerr << "Listen failed" << std::endl;
            close(server_fd);
            return;
        }

        std::cout << "Listening for messages on port " << listen_port << "..." << std::endl;
        std::cout << "Press Enter to return to the main menu." << std::endl;

        // Set socket to non-blocking mode
        int flags = fcntl(server_fd, F_GETFL, 0);
        fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);

        while (is_receiving)
        {
            // Try to accept a connection (non-blocking)
            client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

            if (client_fd >= 0)
            {
                // Connection accepted
                read(client_fd, buffer, 1024);

                char client_ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(address.sin_addr), client_ip, INET_ADDRSTRLEN);

                std::cout << "\nReceived message from " << client_ip << ": " << buffer << std::endl;
                std::cout << "Press Enter to return to the main menu." << std::endl;

                // Clear buffer and close client connection
                memset(buffer, 0, 1024);
                close(client_fd);
            }

            // Sleep a bit to avoid hogging CPU
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        close(server_fd);
        std::cout << "Stopped listening for messages." << std::endl;
    }

public:
    CombinedProgram() : is_receiving(false) {}

    ~CombinedProgram()
    {
        stopReceiving();
    }

    // Initialize the program with a program ID
    void initialize()
    {
        std::cout << "Enter your Program ID: ";
        std::cin >> program_id;
        std::cin.ignore(); // Clear the newline

        listen_port = mapProgramIdToPort(program_id);
        std::cout << "Program initialized with ID " << program_id << " (Port " << listen_port << ")" << std::endl;
    }

    // Start receiving messages in a separate thread
    void startReceiving()
    {
        if (is_receiving)
        {
            std::cout << "Already in receive mode." << std::endl;
            return;
        }

        is_receiving = true;
        receive_thread = std::thread(&CombinedProgram::receiveMessages, this);

        // Wait for Enter key to stop receiving
        std::cin.get();
        stopReceiving();
    }

    // Stop receiving messages
    void stopReceiving()
    {
        if (is_receiving)
        {
            is_receiving = false;
            if (receive_thread.joinable())
            {
                receive_thread.join();
            }
        }
    }

    // Send a message to a specific IP and program ID
    void sendMessage()
    {
        int sock = 0;
        struct sockaddr_in serv_addr;
        std::string target_ip, target_program_id, message;

        // Get user input
        std::cout << "Enter target IP address: ";
        std::getline(std::cin, target_ip);

        std::cout << "Enter target Program ID: ";
        std::getline(std::cin, target_program_id);

        std::cout << "Enter message: ";
        std::getline(std::cin, message);

        // Create socket
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            std::cerr << "Socket creation error" << std::endl;
            return;
        }

        // Set up server address
        serv_addr.sin_family = AF_INET;
        int target_port = mapProgramIdToPort(std::stoi(target_program_id));
        serv_addr.sin_port = htons(target_port);

        // Convert IP address
        if (inet_pton(AF_INET, target_ip.c_str(), &serv_addr.sin_addr) <= 0)
        {
            std::cerr << "Invalid address" << std::endl;
            close(sock);
            return;
        }

        // Connect to server
        std::cout << "Connecting to " << target_ip << " on port " << target_port << "..." << std::endl;
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            std::cerr << "Connection failed. Make sure the target program is running and listening." << std::endl;
            close(sock);
            return;
        }

        // Send message
        send(sock, message.c_str(), message.length(), 0);
        std::cout << "Message sent successfully!" << std::endl;

        close(sock);
    }

    // Display the main menu and handle user choices
    void run()
    {
        std::string choice;

        while (true)
        {
            std::cout << "\n==== Program ID " << program_id << " ====\n";
            std::cout << "1. Send a message\n";
            std::cout << "2. Receive messages\n";
            std::cout << "3. Exit\n";
            std::cout << "Enter your choice (1-3): ";

            std::getline(std::cin, choice);

            if (choice == "1")
            {
                sendMessage();
            }
            else if (choice == "2")
            {
                startReceiving();
            }
            else if (choice == "3")
            {
                break;
            }
            else
            {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main()
{
    CombinedProgram program;
    program.initialize();
    program.run();
    return 0;
}