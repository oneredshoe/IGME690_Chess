#include "Network.h"
#include "iostream"

#pragma once

int main()
{
    std::string IP = "127.0.0.1";
    int PORT = 8888;

    try
    {
        WSASession Session; 
        UDPSocket Socket;
        std::string data = "hello world";
        char buffer[100];
        Socket.Bind(PORT);
        while (1)
        {
            std::cout << "Data Transmitted: ";
            sockaddr_in client = Socket.RecvFrom(buffer, sizeof(buffer));
            std::cout << buffer << std::endl;
            
            std::cout << "Enter data to transmit : " << std::endl;
            std::getline(std::cin, data);
            Socket.SendTo(client, data.c_str(), data.size());
          
        }
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what();
    }


}