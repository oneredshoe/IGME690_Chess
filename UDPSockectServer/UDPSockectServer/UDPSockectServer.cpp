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
        std::string data = "waiting to start";
        char buffer[100];


        vector<sockaddr_in> clients;
        // i wonder if any other data strcuture will work. 
        //  maybe the clients can just send requests for updates every so often?
        // Also, for the board, each client should have the board on their end
        // the server should only recieve moves, update it's matrix, and send that back

        // clients should have the board and the game - the client can determine if the move is legal
        //  -> does this make it hella easy to cheat? Maybe.....
       
        Socket.Bind(PORT);

        bool hasGameStarted = false;
        int white;
        int black;
        int currentPlayer = 0; 

        while (1)
        {
            // this while loop waits for two players to connect
            // and assigns one to white and one to black
            // then we start
            while (hasGameStarted == false)
            {
                // pushes the first two back
                if (clients.size() < 2)
                {
                    // when i get a message from someone
                    sockaddr_in temp = Socket.RecvFrom(buffer, sizeof(buffer));

                    // add to list
                    clients.push_back(temp);
                    std::cout << "I added a cllient to my list" << std::endl;
                }

                else if (clients.size() >= 2)
                {
                    std:cout << "I have 2 now" << std::endl;

                    // set the 0th index to white and tells them
                    white = 0;
                    data = "0";
                    Socket.SendTo(clients[0], data.c_str(), data.size());

                    // set the 1th index to black
                    black = 1;
                    data = "1";
                    Socket.SendTo(clients[1], data.c_str(), data.size());

                    std::cout << "Starting game" << std::endl;
                    hasGameStarted = true;
                }
            }

            std::cout << "Data Transmitted: ";
            sockaddr_in temp = Socket.RecvFrom(buffer, sizeof(buffer));
            std::cout << buffer << std::endl;

            if (buffer[0] == '0')
            {
                // this will be replaced with the board updates
                // std::cout << "Enter data to transmit : " << std::endl;
                // std::getline(std::cin, data);
                data = buffer;
                data = "They played: " + data;

                Socket.SendTo(clients[1], data.c_str(), data.size());
            }
            else if (buffer[0] == '1')
            {
                // this will be replaced with the board updates
                // std::cout << "Enter data to transmit : " << std::endl;
                // std::getline(std::cin, data);
                data = buffer;
                data = "They played: " + data;

                Socket.SendTo(clients[0], data.c_str(), data.size());
            }
            else
            {
                // wha happuh?
                std::cout << "You really hecked this up" << std::endl;
            }
        }
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what();
    }


}