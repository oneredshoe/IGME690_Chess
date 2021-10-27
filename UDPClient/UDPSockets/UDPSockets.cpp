#include "Network.h"
#include "iostream"

#pragma once

int main()
{
    std::string IP = "127.0.0.1";
    int PORT = 8888;
    bool gameInPlay = true;
    bool isMyTurn;

    try
    {
        WSASession Session;
        UDPSocket Socket;
        std::string data = "I would like to play";
        char buffer[100];
        char id;

        // telling the server I want to play the game
        Socket.SendTo(IP, PORT, data.c_str(), data.size());

        // waits for the server to telll me if I'm white or black
        Socket.RecvFrom(buffer, sizeof(buffer));

        // 0 if white, 1 if black
        if (buffer[0] == '0')
        {
            isMyTurn = true;
            id = '0';
            std::cout << "I go first" << std::endl;
        }
        else
        {
            isMyTurn = false;
            id = '1';
            std::cout << "I go second" << std::endl;
        }
        
        while (1)
        {
            // if it's not my turn yet, I wait for the server
            // to tell me what happens
            // after the server tells me what happens
            // its my turn and i can send my move
            if (isMyTurn == false)
            {
                Socket.RecvFrom(buffer, sizeof(buffer));

                if (buffer == "invalid")
                {
                    // I played an invalid move, and need to play another
                    // get data from UI
                    std::cout << "Enter data to transmit : " << std::endl;
                    std::getline(std::cin, data);

                    // append my ID
                    data = id + data;

                    // send my move
                    Socket.SendTo(IP, PORT, data.c_str(), data.size());
                    isMyTurn = false;
                }
                else
                {
                    // sends the board the update from the server
                    // here I need to update my local board
                    std::cout << buffer << std::endl;

                    isMyTurn = true;
                }
            }

            // i don't /think/ i need this but liiiiiiike
            if (isMyTurn == true)
            {
                // it is now my turn and i get data that is my move
                std::cout << "Enter data to transmit : " << std::endl;
                std::getline(std::cin, data);
                data = id + data;

                // instead of getting data from the user, I'm going to send a array of size 4 
                // the first two are the start loc of the piece I'm moving
                // and the end two are the end location
                // this will go to the server, and the server will tell us if it was valid or not
                // if not, try again?
                // I think it'll actually have to be an array of 5, because we need the ID

                // when it is my turn, i send my move to the server
                Socket.SendTo(IP, PORT, data.c_str(), data.size());
                isMyTurn = false;
            }

            // because we wait at the start of the loop we /shouldnt/ need this
            // Socket.RecvFrom(buffer, sizeof(buffer));
        }


        //Game Loop
        while (gameInPlay)
        {
            gameInPlay = false;
        }
        

    }
    catch (std::exception& ex)
    {
        std::cout << ex.what();
    }


}