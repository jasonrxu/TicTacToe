//
//  Game.cpp
//  Tic Tac Toe AI
//
//  Created by Jason Xu on 7/22/15.
//  Copyright © 2015 Jason Xu. All rights reserved.
//

#include "Game.hpp"
#include "Player.hpp"
#include <iostream>



TicTacToe::Game::Game(Player &player1, Player &player2) : player1(player1), player2(player2) {
    for (auto i = 0; i < 3; i++) {
        for (auto j = 0; j < 3; j++) {
            board[i][j] = Empty;
        }
    }
}

void TicTacToe::Game::start() {
    
    using namespace std;
    
    auto currentPlayer = Player::PlayerType::Player1;
    displayBoard();
    while (checkWin() == -1) {
        if (currentPlayer == Player::PlayerType::Player1) {
            auto move = player1.nextMove(*this) - 1;
            board[move % 3][move / 3] = Player1;
            displayBoard();
            currentPlayer = Player::PlayerType::Player2;
        } else {
            int move = player2.nextMove(*this) - 1;
            board[move % 3][move / 3] = Player2;
            displayBoard();
            currentPlayer = Player::PlayerType::Player1;
        }
    }
    if (checkWin() == 1) {
        cout << "PLAYER 1 WON!" << endl;
    } else if (checkWin() == 2) {
        cout << "PLAYER 2 WON!" << endl;
    } else {
        cout << "draw" << endl;
    }
}

void TicTacToe::Game::displayBoard() const {
    using namespace std;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            cout << (int)board[column][row] << " ";
        }
        cout << endl;
    }
}

bool isPlayer1(const TicTacToe::Game::Status &status) {
    return status == TicTacToe::Game::Status::Player1;
}

bool isPlayer2(const TicTacToe::Game::Status &status) {
    return status == TicTacToe::Game::Status::Player2;
}

bool isEmpty(const TicTacToe::Game::Status &status) {
    return status == TicTacToe::Game::Status::Empty;
}

int TicTacToe::Game::checkWin() const {
    if ((isPlayer1(board[0][0]) && isPlayer1(board[1][1]) && isPlayer1(board[2][2])) || (isPlayer1(board[0][2]) && isPlayer1(board[1][1]) && isPlayer1(board[2][0])))
    {
        return 1;
    }
    else if ((isPlayer2(board[0][0]) && isPlayer2(board[1][1]) && isPlayer2(board[2][2])) || (isPlayer2(board[0][2]) && isPlayer2(board[1][1]) && isPlayer2(board[2][0])))
    {
        return 2;
    }
    for (int i = 0; i < 3; i++)
    {
        if ((isPlayer1(board[0][i]) && isPlayer1(board[1][i]) && isPlayer1(board[2][i])) || (isPlayer1(board[i][0]) && isPlayer1(board[i][1]) && isPlayer1(board[i][2])))
        {
            return 1;
        }
        else if ((isPlayer2(board[0][i]) && isPlayer2(board[1][i]) && isPlayer2(board[2][i])) || (isPlayer2(board[i][0]) && isPlayer2(board[i][1]) && isPlayer2(board[i][2])))
        {
            return 2;
        }
    }
    bool fullBoard = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (isEmpty(board[i][j]))
            {
                fullBoard = false;
            }
        }
    }
    if (fullBoard)
    {
        return 0;
    }
    return -1;
}
