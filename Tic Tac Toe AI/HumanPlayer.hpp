//
//  HumanPlayer.hpp
//  Tic Tac Toe AI
//
//  Created by Jason Xu on 7/23/15.
//  Copyright © 2015 Jason Xu. All rights reserved.
//

#ifndef HumanPlayer_hpp
#define HumanPlayer_hpp

#include <stdio.h>
#include "Player.hpp"

namespace TicTacToe {
    class HumanPlayer : public Player {
    public:
        HumanPlayer(PlayerType type);
        virtual int nextMove(Game &game);
    };
}

#endif /* HumanPlayer_hpp */
