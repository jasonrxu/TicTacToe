//
//  Player.hpp
//  Tic Tac Toe AI
//
//  Created by Jason Xu on 7/22/15.
//  Copyright © 2015 Jason Xu. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>

namespace TicTacToe {
    class Game;
    class Player {
        
    public:
        virtual int nextMove(Game &game) = 0;
        
        typedef enum {
            Player1 = 0,
            Player2
        } PlayerType;
        
        Player(PlayerType type);
        PlayerType playerType;
    };
}

#endif /* Player_hpp */
