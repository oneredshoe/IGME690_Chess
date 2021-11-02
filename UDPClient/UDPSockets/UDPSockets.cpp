#include "Network.h"
#include "iostream"
#include "BoardState.h"
#include "Piece.h"

#pragma once

int main()
{
    std::string IP = "127.0.0.1";
    int PORT = 8888;
    bool gameInPlay = true;
    bool isMyTurn;

    BoardState m_boardState = BoardState();


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

        if (id == '0' || id == '1')
        {
            gameInPlay = true;
        }
        else
        {
            gameInPlay = false;
        }
        
        while (gameInPlay)
        {
            // if it's not my turn yet, I wait for the server
            // to tell me what happens
            // after the server tells me what happens
            // its my turn and i can send my move
            if (isMyTurn == false)
            {
                Socket.RecvFrom(buffer, sizeof(buffer));

                std::cout << buffer << std::endl;

                if (buffer == "invalid")
                {
                    std::cout << "You entered an invalid move" << std::endl;

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

                    // this gets just the move portion, getting rid of the ID
                    string incomingMove = buffer;
                    incomingMove = incomingMove.substr(1, 4);

                    // now I need to break that into two int array
                    int startPos[2];
                    startPos[0] = stoi(incomingMove.substr(0,1));
                    startPos[1] = stoi(incomingMove.substr(1, 1));

                    int endPos[2];
                    endPos[0] = stoi(incomingMove.substr(2, 1));
                    endPos[1] = stoi(incomingMove.substr(3, 1));

                    // now you send it through your board to update it
                    // the move is already validated by the server
                    m_boardState.movePiece(startPos, endPos);

                    isMyTurn = true;
                }
            }

            // i don't /think/ i need this but liiiiiiike
            if (isMyTurn == true)
            {
                // it is now my turn and i get data that is my move
                std::cout << "Enter data to transmit in the format (start location end location): " << std::endl;
                std::getline(std::cin, data);
                data = id + data;

                // instead of getting data from the user, I'm going to send a array of size 4 
                // the first two are the start loc of the piece I'm moving
                // and the end two are the end location
                // this will go to the server, and the server will tell us if it was valid or not
                // if not, try again?
                // I think it'll actually have to be an array of 5, because we need the ID
                // this will be when visuals hook up, but for now the user will type in their moves in terms of a 2d array from 0-7 on both axes

                // when it is my turn, i send my move to the server
                Socket.SendTo(IP, PORT, data.c_str(), data.size());
                isMyTurn = false;
            }
        }


        ////Game Loop
        //while (gameInPlay)
        //{
        //    gameInPlay = false;
        //}
        

    }
    catch (std::exception& ex)
    {
        std::cout << ex.what();
    }


}