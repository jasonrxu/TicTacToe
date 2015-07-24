//
//  AIPlayer.hpp
//  Tic Tac Toe AI
//
//  Created by Timothy Chase Willard on 7/22/15.
//  Copyright © 2015 Timothy Chase Willard. All rights reserved.
//

#ifndef AIPlayer_hpp
#define AIPlayer_hpp

#include <stdio.h>
#include "Player.hpp"
#include "Game.hpp"

namespace TicTacToe 
{
    class Game;
    class AIPlayer : 
		public Player 
	{  
    public:
        AIPlayer(PlayerType type);
        virtual int nextMove(Game &game);
	private:
		// breaking the AI into 3 components
		int checkPotentialWins(Game::Status board[3][3]);
		int checkPotentialLosses(Game::Status board[3][3]);
		int checkPotentialOther(Game::Status board[3][3]);
		// forks
		int checkPotentialWinningForks(Game::Status board[3][3]);
		int checkPotentialLosingForks(Game::Status board[3][3]);
		int checkPotentialWinsForksCount(Game::Status board[3][3]);
		int checkPotentialLossesForksCount(Game::Status board[3][3]);
		// internal checking
		int checkWinner(Game::Status board[3][3]);
		// util
		int xyBoard(int x, int y);
		bool isEmpty(Game::Status board);
		bool isMe(Game::Status board);
		bool isHim(Game::Status board);
		Game::Status myPiece();
		Game::Status hisPiece();
    };
}

#endif /* AIPlayer_hpp */
