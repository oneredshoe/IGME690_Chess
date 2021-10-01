#include "Network.h"
#include "iostream"
#include <vector>


using namespace std;
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


        vector<sockaddr_in> client;
       
        Socket.Bind(PORT);
        while (1)
        {
            std::cout << "Data Transmitted: ";


            
            //how to get multiple clients?
            //loop until
            sockaddr_in temp = Socket.RecvFrom(buffer, sizeof(buffer));

            //client.push_back(temp);

            std::cout << buffer << std::endl;            
            std::cout << "Enter data to transmit : " << std::endl;



            std::getline(std::cin, data);
            Socket.SendTo(temp, data.c_str(), data.size());
          
        }
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what();
    }


}