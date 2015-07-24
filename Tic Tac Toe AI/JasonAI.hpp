//
//  JasonAI.hpp
//  Tic Tac Toe AI
//
//  Created by Jason Xu on 7/22/15.
//  Copyright © 2015 Jason Xu. All rights reserved.
//

#ifndef JasonAI_hpp
#define JasonAI_hpp

#include <stdio.h>
#include "Player.hpp"

namespace TicTacToe {
    class Game;
    class JasonAI : public Player {
    private:
        
    public:
        JasonAI(PlayerType type);
        virtual int nextMove(Game &game);
    };
}

#endif /* JasonAI_hpp */
