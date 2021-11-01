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
       
        Socket.Bind(PORT);

        bool hasGameStarted = false;
        int white;
        int black;
        int currentPlayer = 0; 

        bool validMove = true;

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
                    std:cout << "There are now two players, the game can start." << std::endl;

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

            // here instead of just putting it into the buffer, I go and validate moves
            // if the move is valid, I just send it to the next player and we're good
            // if not, I have to tell the user it's invalid, and ask for another one

            // check for valid move here

            // this is white's move
            if (buffer[0] == '0')
            {
                // if white played a valid move, just send it to black
                if (validMove == true)
                {
                    // this will be replaced with the board updates
                    // it will ideally be the four character array to represent starting position and ending position
                    data = buffer;
                    data = "They played: " + data;

                    Socket.SendTo(clients[1], data.c_str(), data.size());
                }
                // if white played an invalid move, tell them
                else
                {
                    data = "invalid";
                    Socket.SendTo(clients[0], data.c_str(), data.size());
                }
            }
            // this is black's move
            else if (buffer[0] == '1')
            {
                // if black played a valid move, just send it to white
                if (validMove == true)
                {
                    // this will be replaced with the board updates
                    // again, here will ideally be the 4 char array
                    data = buffer;
                    data = "They played: " + data;

                    Socket.SendTo(clients[0], data.c_str(), data.size());
                }
                // if black played an invalid move, tell them
                else
                {
                    data = "invalid";
                    Socket.SendTo(clients[1], data.c_str(), data.size());
                }
            }
            // no on'es move, should never reach this
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