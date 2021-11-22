#include "Network.h"
#include "iostream"
#include <vector>
#include "BoardState.h"
#include "Piece.h"
#define SFML_STATIC


using namespace std;
#pragma once

int main()
{
    std::string IP = "127.0.0.1";
    int PORT = 8888;

    BoardState m_boardState = BoardState();

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
        bool drawOffered = false;

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

            // to do this, I split the buffer, stripping away the id
            // then i split it into two int arrays
            // then i pass those into the boardstat.movepiece
            // this gives back true if it's a valid move and false otherwise

            // this gets just the move portion, getting rid of the ID
            string incomingMove = buffer;

            // first thing is to do logic for if the draw has been offered
            if (drawOffered)
            {
                // if the draw was accepted
                if (buffer[1] == 'y' || buffer[1] == 'Y')
                {
                    // tell both members the draw was accepted
                    data = "A: Draw has been accepted. The game is over and has ended in a draw.";

                    Socket.SendTo(clients[0], data.c_str(), data.size());
                    Socket.SendTo(clients[1], data.c_str(), data.size());

                    // reset for next game
                    currentPlayer = 0;
                    white = NULL;
                    black = NULL;
                    hasGameStarted = false;
                    drawOffered = false;
                }
                // if the draw was turned down
                else if (buffer[1] == 'n' || buffer[1] == 'N')
                {
                    // the opposite of the one who declined should be the one moving next
                    // because W offers, B says no, W plays move
                    if (buffer[0] == '0')
                    {
                        currentPlayer = 1;

                        // give code for draw declined but also tell who is supposed to go next
                        data = "D0: Draw has been declined. The game will continue.";

                        // tell the player that it was declined and it's their turn now
                        Socket.SendTo(clients[1], data.c_str(), data.size());
                    }
                    else if (buffer[0] == '1')
                    {
                        currentPlayer = 0;
                        // give code for draw declined but also tell who is supposed to go next
                        data = "D1: Draw has been declined. The game will continue.";

                        // tell the player that offered the draw that it was declined
                        Socket.SendTo(clients[0], data.c_str(), data.size());
                    }
                    // set this back to false so they can keep playing
                    drawOffered = false;
                }
                // if the user typed in something in valid
                else
                {
                    // ask the user for a valid input
                    data = "Q: That was not a valid input. Type Y to accept and N to deny.";

                    // send it to the person who just sent us a reply
                    if (buffer[0] == '0')
                    {
                        Socket.SendTo(clients[0], data.c_str(), data.size());
                        currentPlayer = 0;
                    }
                    else if (buffer[0] == '1')
                    {
                        Socket.SendTo(clients[1], data.c_str(), data.size());
                        currentPlayer = 1;
                    }
                }
            }
            else
            {
                // logic for draws and resigning
                // resigning
                if (buffer[1] == 'r' || buffer[1] == 'R')
                {
                    // send the message to the player that won.
                    if (buffer[0] == '0')
                    {
                        // set data to tell the player that they resigned
                        data = "R: The other player resigned. You win.";
                        Socket.SendTo(clients[1], data.c_str(), data.size());

                        // now tell the player that resigned the game is over.
                        data = "R: You have resigned. Game over.";
                        Socket.SendTo(clients[0], data.c_str(), data.size());
                    }
                    else if (buffer[0] == '1')
                    {
                        // set data to tell the player that they resigned
                        data = "R: The other player resigned. You win.";
                        Socket.SendTo(clients[0], data.c_str(), data.size());

                        // now tell the player that resigned the game is over.
                        data = "R: You have resigned. Game over.";
                        Socket.SendTo(clients[1], data.c_str(), data.size());
                    }

                    // reset for next game
                    currentPlayer = 0;
                    white = NULL;
                    black = NULL;
                    hasGameStarted = false;
                    drawOffered = false;
                }

                // draw offer
                else if (buffer[1] == 'o' || buffer[1] == 'O')
                {
                    // set the bool to true
                    drawOffered = true;

                    // set data to tell them they draw was 
                    data = "O: The other player has offered a draw. Type Y to accept and N to deny.";

                    // send this data to the next player
                    if (buffer[0] == '0')
                    {
                        Socket.SendTo(clients[1], data.c_str(), data.size());
                        currentPlayer = 1;
                    }
                    else if (buffer[0] == '1')
                    {
                        Socket.SendTo(clients[0], data.c_str(), data.size());
                        currentPlayer = 0;
                    }
                }
                // if neither draw nor resign, go through normal stuff
                else
                {
                    incomingMove = incomingMove.substr(1, 4);

                    std::cout << incomingMove << std::endl;

                    // now I need to break that into two int array
                    int startPos[2];
                    startPos[0] = stoi(incomingMove.substr(0, 1));
                    startPos[1] = stoi(incomingMove.substr(1, 1));

                    std::cout << "Start pos" << std::endl;
                    std::cout << startPos[0] << std::endl;
                    std::cout << startPos[1] << std::endl;

                    int endPos[2];
                    endPos[0] = stoi(incomingMove.substr(2, 1));
                    endPos[1] = stoi(incomingMove.substr(3, 1));


                    std::cout << "End pos" << std::endl;
                    std::cout << endPos[0] << std::endl;
                    std::cout << endPos[1] << std::endl;

                    // now you send it through the board to validate it. 
                    validMove = m_boardState.movePiece(startPos, endPos);

                    std::cout << validMove << std::endl;

                    std::cout << buffer << std::endl;

                    // this is white's move
                    if (buffer[0] == '0' && currentPlayer == 0)
                    {
                        // if white played a valid move, just send it to black
                        if (validMove == true)
                        {
                            // this will be replaced with the board updates
                            // it will ideally be the four character array to represent starting position and ending position
                            data = incomingMove;

                            data += " Type r to resign and o to offer draw.";

                            Socket.SendTo(clients[1], data.c_str(), data.size());
                            currentPlayer = 1;
                        }
                        // if white played an invalid move, tell them
                        else
                        {
                            data = "invalid";
                            Socket.SendTo(clients[0], data.c_str(), data.size());
                            currentPlayer = 0;
                        }
                    }
                    // this is black's move
                    else if (buffer[0] == '1' && currentPlayer == 1)
                    {
                        // if black played a valid move, just send it to white
                        if (validMove == true)
                        {
                            // this will be replaced with the board updates
                            // again, here will ideally be the 4 char array
                            data = incomingMove;

                            data += " Type r to resign and o to offer draw.";

                            Socket.SendTo(clients[0], data.c_str(), data.size());
                            currentPlayer = 0;
                        }
                        // if black played an invalid move, tell them
                        else
                        {
                            data = "invalid";
                            Socket.SendTo(clients[1], data.c_str(), data.size());
                            currentPlayer = 1;
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
        }
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what();
    }


}