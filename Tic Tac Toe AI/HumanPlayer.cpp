//
//  HumanPlayer.cpp
//  Tic Tac Toe AI
//
//  Created by Jason Xu on 7/23/15.
//  Copyright © 2015 Jason Xu. All rights reserved.
//

#include "HumanPlayer.hpp"
#include <iostream>


TicTacToe::HumanPlayer::HumanPlayer(TicTacToe::HumanPlayer::PlayerType type) : Player(type) {
    
}

int TicTacToe::HumanPlayer::nextMove(TicTacToe::Game &game) {
    int move = 0;
    std::cout << "Your move." << std::endl;
    std::cin >> move;
    return move;
}