//
//  main.cpp
//  Tic Tac Toe AI
//
//  Created by Jason Xu on 7/22/15.
//  Copyright © 2015 Jason Xu. All rights reserved.
//

#include <iostream>
#include "Game.hpp"
#include "Player.hpp"
#include "HumanPlayer.hpp"
#include "JasonAI.hpp"
#include "AIPlayer.hpp"

int main(int argc, const char * argv[]) {
    auto human = TicTacToe::HumanPlayer(TicTacToe::Player::Player1);
//    auto jasonAI = TicTacToe::JasonAI(TicTacToe::Player::Player2);
    auto chaseAI = TicTacToe::AIPlayer(TicTacToe::Player::Player2);
    auto game = TicTacToe::Game(human, chaseAI);
    game.start();
    return 0;
}
