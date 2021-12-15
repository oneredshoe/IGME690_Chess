#pragma once
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#include "Network.h"
#include <iostream>
#include "BoardState.h"
#include "Board.h"


char board[8][8];

void drawBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8;  j++) {
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    }
}

void setUpBoard() {
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = '0';
        }
    }
    for (int i = 0; i < 8; i++) {
        board[1][i] = 'p';
        board[6][i] = 'P';
    }

    board[0][0] = 'c';
    board[0][7] = 'c';
    board[7][0] = 'C';
    board[7][7] = 'C';

    board[0][1] = 'h';
    board[0][6] = 'h';
    board[7][1] = 'H';
    board[7][6] = 'H';

    board[0][5] = 'b';
    board[0][2] = 'b';
    board[7][5] = 'B';
    board[7][2] = 'B';

    board[0][4] = 'q';
    board[7][4] = 'Q';

    board[0][3] = 'k';
    board[7][3] = 'K';
    drawBoard();
}

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
            setUpBoard();
        }
        else
        {
            isMyTurn = false;
            id = '1';
            std::cout << "I go second" << std::endl;
            setUpBoard();
        }

        if (id == '0' || id == '1')
        {
            gameInPlay = true;
        }
        else
        {
            gameInPlay = false;
        }
        
        while (gameInPlay)///window.isOpen())
        {
            
            
            // if it's not my turn yet, I wait for the server
            // to tell me what happens
            // after the server tells me what happens
            // its my turn and i can send my move
            if (isMyTurn == false)
            {
                Socket.RecvFrom(buffer, sizeof(buffer));

                std::cout << buffer << std::endl;

                // if your move was invalid, get another move and send it
                if (buffer[0] == 'i')
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

                // if you get the codes of Q, O, or D, then you need to give input so it's your turn
                else if (buffer[0] == 'Q' // invalid input for draw offer
                    || buffer[0] == 'O' // the other player offered a draw
                    || buffer[0] == 'D') // the draw you offered was declined
                {
                    isMyTurn = true;
                }

                // if the draw was accepted or if the other player resigned, the game is over and the loop ends
                else if (buffer[0] == 'A' || buffer[0] == 'R')
                {
                    gameInPlay = false;
                }

                // this would be getting a normal move fromt he server that the opponent played
                else
                {
                    // sends the board the update from the server
                    // here I need to update my local board
                    std::cout << buffer << std::endl;

                    // this gets just the move portion, getting rid of the ID
                    string incomingMove = buffer;
                    incomingMove = incomingMove.substr(0, 4);

                    // now I need to break that into two int array
                    int startPos[2];
                    startPos[0] = stoi(incomingMove.substr(0,1));
                    startPos[1] = stoi(incomingMove.substr(1, 1));

                    int endPos[2];
                    endPos[0] = stoi(incomingMove.substr(2, 1));
                    endPos[1] = stoi(incomingMove.substr(3, 1));

                    board[endPos[0]][endPos[1]] = board[startPos[0]][startPos[1]];
                    board[startPos[0]][startPos[1]] = '0';

                    drawBoard();
                    // now you send it through your board to update it
                    // the move is already validated by the server

                    isMyTurn = true;
                }
            }

            // if you have recieved a move and it is now your turn
            // or if they offered a draw, you gave invalid draw acceptance input, or your draw offer was declined
            // then it is your turn to give input in the form of move or whatever the server asks for
            if (isMyTurn == true)
            {
               
                // it is now my turn and i get data that is my move
                std::cout << "Enter data to transmit in the format (start location end location) or requested by server: " << std::endl;
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