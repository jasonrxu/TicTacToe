//
//  Game.hpp
//  Tic Tac Toe AI
//
//  Created by Jason Xu on 7/22/15.
//  Copyright © 2015 Jason Xu. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Player.hpp"

namespace TicTacToe {
    class Game {
        
    public:
        
        typedef enum : int {
            Player1 = 0,
            Player2,
            Empty
        } Status;
        
        Game(Player &player1, Player &player2);
        
        Status board[3][3];
        
        Player &player1, &player2;
        
        void start();
        
    private:
        int checkWin() const;
        void displayBoard() const;
    };
}

#endif /* Game_hpp */
