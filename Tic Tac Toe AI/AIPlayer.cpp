//
//  AIPlayer.cpp
//  Tic Tac Toe AI
//
//  Created by Timothy Chase Willard on 7/22/15.
//  Copyright © 2015 Timothy Chase Willard. All rights reserved.
//

#include <memory.h>
#include <iostream>
#include "AIPlayer.hpp"
#include "Game.hpp"

// constructor + setup
TicTacToe::AIPlayer::AIPlayer(Player::PlayerType type) : Player(type)
{
	playerType = type;
}
// called by the game class to determine next move,
// corresponds to 1 - 9 on a Tic Tac Toe board (1 is tl & 9 is br)
int TicTacToe::AIPlayer::nextMove(Game &game)
{
	// playerType == Player1;
	// playerType is equal to either Player1 or Player2, and is defined at start, determines what you are
	int move = checkPotentialWins(game.board);
	if (move != -1)
	{
        std::cout << "ChaseAI Move: " << move << std::endl;
		return move;
	}
	move = checkPotentialLosses(game.board);
	if (move != -1)
	{
        std::cout << "ChaseAI Move: " << move << std::endl;
		return move;
	}
	move = checkPotentialOther(game.board);
	if (move == -1)
	{
		std::cout << "Placement Error: No Avalible Spaces" << std::endl;
		std::exit(0);
	}
    std::cout << "ChaseAI Move: " << move << std::endl;
	return move;
}
// check to see if I (player2) can win this turn, returns -1 if not possible
int TicTacToe::AIPlayer::checkPotentialWins(TicTacToe::Game::Status board[3][3])
{
	if (((isMe(board[0][0]) && isMe(board[2][2])) || (isMe(board[0][2]) && isMe(board[2][0]))) && isEmpty(board[1][1]))
	{
		return xyBoard(1, 1);
	}
	else if (isMe(board[0][0]) && isMe(board[1][1]) && isEmpty(board[2][2]))
	{
		return xyBoard(2, 2);
	}
	else if (isEmpty(board[0][0]) && isMe(board[1][1]) && isMe(board[2][2]))
	{
		return xyBoard(0, 0);
	}
	else if (isMe(board[0][2]) && isMe(board[1][1]) && isEmpty(board[2][0]))
	{
		return xyBoard(2, 0);
	}
	else if (isEmpty(board[0][2]) && isMe(board[1][1]) && isMe(board[2][0]))
	{
		return xyBoard(0, 2);
	}
	for (int i = 0; i < 3; i++)
	{
		if (isMe(board[0][i]) && isMe(board[1][i]) && isEmpty(board[2][i]))
		{
			return xyBoard(2, i);
		}
		else if (isMe(board[0][i]) && isEmpty(board[1][i]) && isMe(board[2][i]))
		{
			return xyBoard(1, i);
		}
		else if (isEmpty(board[0][i]) && isMe(board[1][i]) && isMe(board[2][i]))
		{
			return xyBoard(0, i);
		}
		else if (isMe(board[i][0]) && isMe(board[i][1]) && isEmpty(board[i][2]))
		{
			return xyBoard(i, 2);
		}
		else if (isMe(board[i][0]) && isEmpty(board[i][1]) && isMe(board[i][2]))
		{
			return xyBoard(i, 1);
		}
		else if (isEmpty(board[i][0]) && isMe(board[i][1]) && isMe(board[i][2]))
		{
			return xyBoard(i, 0);
		}
	}
	return -1;
}
// check to see if he (player1) can win next turn, returns -1 if not possible
int TicTacToe::AIPlayer::checkPotentialLosses(Game::Status board[3][3])
{
	if (((isHim(board[0][0]) && isHim(board[2][2])) || (isHim(board[0][2]) && isHim(board[2][0]))) && isEmpty(board[1][1]))
	{
		return xyBoard(1, 1);
	}
	else if (isHim(board[0][0]) && isHim(board[1][1]) && isEmpty(board[2][2]))
	{
		return xyBoard(2, 2);
	}
	else if (isEmpty(board[0][0]) && isHim(board[1][1]) && isHim(board[2][2]))
	{
		return xyBoard(0, 0);
	}
	else if (isHim(board[0][2]) && isHim(board[1][1]) && isEmpty(board[2][0]))
	{
		return xyBoard(2, 0);
	}
	else if (isEmpty(board[0][2]) && isHim(board[1][1]) && isHim(board[2][0]))
	{
		return xyBoard(0, 2);
	}
	for (int i = 0; i < 3; i++)
	{
		if (isHim(board[0][i]) && isHim(board[1][i]) && isEmpty(board[2][i]))
		{
			return xyBoard(2, i);
		}
		else if (isHim(board[0][i]) && isEmpty(board[1][i]) && isHim(board[2][i]))
		{
			return xyBoard(1, i);
		}
		else if (isEmpty(board[0][i]) && isHim(board[1][i]) && isHim(board[2][i]))
		{
			return xyBoard(0, i);
		}
		else if (isHim(board[i][0]) && isHim(board[i][1]) && isEmpty(board[i][2]))
		{
			return xyBoard(i, 2);
		}
		else if (isHim(board[i][0]) && isEmpty(board[i][1]) && isHim(board[i][2]))
		{
			return xyBoard(i, 1);
		}
		else if (isEmpty(board[i][0]) && isHim(board[i][1]) && isHim(board[i][2]))
		{
			return xyBoard(i, 0);
		}
	}
	return -1;
}
// fiqure out where to place a piece if neither him or I can win next/this turn
// MUST return a space as this is kinda the catchall
int TicTacToe::AIPlayer::checkPotentialOther(Game::Status board[3][3])
{
	int move = -1;
	// try making a fork
	move = checkPotentialWinningForks(board);
	if (move == -1)
	{
		// block the `his` fork
		move = checkPotentialLosingForks(board);
	}
	if (move == -1)
	{
		// if center space is open take it
		if (isEmpty(board[1][1]))
		{
			move = xyBoard(1, 1);
		}
	}
	if (move == -1)
	{
		// if `he` has corner pieces, try to put a piece in an opposite corner 
		if (isHim(board[0][0]) && isEmpty(board[2][2]))
		{
			move = xyBoard(2, 2);
		}
		else if (isHim(board[0][2]) && isEmpty(board[2][0]))
		{
			move = xyBoard(2, 0);
		}
		else if (isHim(board[2][0]) && isEmpty(board[0][2]))
		{
			move = xyBoard(0, 2);
		}
		else if (isHim(board[2][2]) && isEmpty(board[0][0]))
		{
			move = xyBoard(0, 0);
		}
	}
	if (move == -1)
	{
		if (isEmpty(board[0][0]))
		{
			move = xyBoard(0, 0);
		}
		else if (isEmpty(board[0][2]))
		{
			move = xyBoard(0, 2);
		}
		else if (isEmpty(board[2][0]))
		{
			move = xyBoard(2, 0);
		}
		else if (isEmpty(board[2][2]))
		{
			move = xyBoard(2, 2);
		}
	}
	if (move == -1)
	{
		// take any free edge
		if (isEmpty(board[0][1]))
		{
			move = xyBoard(0, 1);
		}
		else if (isEmpty(board[1][0]))
		{
			move = xyBoard(1, 0);
		}
		else if (isEmpty(board[1][2]))
		{
			move = xyBoard(1, 2);
		}
		else if (isEmpty(board[2][1]))
		{
			move = xyBoard(2, 1);
		}
	}
	return move;
}
// forks! (and not the github kind...)
// return -1 if no for, else return 1 - 9, of placement (using xyBoard)
int TicTacToe::AIPlayer::checkPotentialWinningForks(Game::Status board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (isEmpty(board[i][j]))
			{
				Game::Status boardcopy[3][3];
                memcpy(boardcopy, board, sizeof(Game::Status) * 9);
				boardcopy[i][j] = myPiece();
				int count = checkPotentialWinsForksCount(boardcopy);
				if (count >= 2)
				{
					return xyBoard(i, j);
				}
			}
		}
	}
	return -1;
}
int TicTacToe::AIPlayer::checkPotentialLosingForks(Game::Status board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (isEmpty(board[i][j]))
			{
				Game::Status boardcopy[3][3];
				memcpy(boardcopy, board, sizeof(Game::Status) * 9);
				boardcopy[i][j] = hisPiece();
				int count = checkPotentialLossesForksCount(boardcopy);
				if (count >= 2)
				{
					return xyBoard(i, j);
				}
			}
		}
	}
	return -1;
}
int TicTacToe::AIPlayer::checkPotentialWinsForksCount(Game::Status board[3][3])
{
	int count = 0;
	if (((isMe(board[0][0]) && isMe(board[2][2])) || (isMe(board[0][2]) && isMe(board[2][0]))) && isEmpty(board[1][1]))
	{
		count++;
	}
	else if (isMe(board[0][0]) && isMe(board[1][1]) && isEmpty(board[2][2]))
	{
		count++;
	}
	else if (isEmpty(board[0][0]) && isMe(board[1][1]) && isMe(board[2][2]))
	{
		count++;
	}
	else if (isMe(board[0][2]) && isMe(board[1][1]) && isEmpty(board[2][0]))
	{
		count++;
	}
	else if (isEmpty(board[0][2]) && isMe(board[1][1]) && isMe(board[2][0]))
	{
		count++;
	}
	for (int i = 0; i < 3; i++)
	{
		if (isMe(board[0][i]) && isMe(board[1][i]) && isEmpty(board[2][i]))
		{
			count++;
		}
		else if (isMe(board[0][i]) && isEmpty(board[1][i]) && isMe(board[2][i]))
		{
			count++;
		}
		else if (isEmpty(board[0][i]) && isMe(board[1][i]) && isMe(board[2][i]))
		{
			count++;
		}
		else if (isMe(board[i][0]) && isMe(board[i][1]) && isEmpty(board[i][2]))
		{
			count++;
		}
		else if (isMe(board[i][0]) && isEmpty(board[i][1]) && isMe(board[i][2]))
		{
			count++;
		}
		else if (isEmpty(board[i][0]) && isMe(board[i][1]) && isMe(board[i][2]))
		{
			count++;
		}
	}
	return count;
}
int TicTacToe::AIPlayer::checkPotentialLossesForksCount(Game::Status board[3][3])
{
	int count = 0;
	if (((isHim(board[0][0]) && isHim(board[2][2])) || (isHim(board[0][2]) && isHim(board[2][0]))) && isEmpty(board[1][1]))
	{
		count++;
	}
	else if (isHim(board[0][0]) && isHim(board[1][1]) && isEmpty(board[2][2]))
	{
		count++;
	}
	else if (isEmpty(board[0][0]) && isHim(board[1][1]) && isHim(board[2][2]))
	{
		count++;
	}
	else if (isHim(board[0][2]) && isHim(board[1][1]) && isEmpty(board[2][0]))
	{
		count++;
	}
	else if (isEmpty(board[0][2]) && isHim(board[1][1]) && isHim(board[2][0]))
	{
		count++;
	}
	for (int i = 0; i < 3; i++)
	{
		if (isHim(board[0][i]) && isHim(board[1][i]) && isEmpty(board[2][i]))
		{
			count++;
		}
		else if (isHim(board[0][i]) && isEmpty(board[1][i]) && isHim(board[2][i]))
		{
			count++;
		}
		else if (isEmpty(board[0][i]) && isHim(board[1][i]) && isHim(board[2][i]))
		{
			count++;
		}
		else if (isHim(board[i][0]) && isHim(board[i][1]) && isEmpty(board[i][2]))
		{
			count++;
		}
		else if (isHim(board[i][0]) && isEmpty(board[i][1]) && isHim(board[i][2]))
		{
			count++;
		}
		else if (isEmpty(board[i][0]) && isHim(board[i][1]) && isHim(board[i][2]))
		{
			count++;
		}
	}
	return count;
}
// returns -1, if still playing (no winner & game isn't over)
// returns 0, if it is a draw (no winner & game is over)
// returns 1, if `I` won (winner & game is over)
// returns 2, if `he` won (winner & game is over)
int TicTacToe::AIPlayer::checkWinner(Game::Status board[3][3])
{
	if ((isMe(board[0][0]) && isMe(board[1][1]) && isMe(board[2][2])) || (isMe(board[0][2]) && isMe(board[1][1]) && isMe(board[2][0])))
	{
		return 1;
	}
	else if ((isHim(board[0][0]) && isHim(board[1][1]) && isHim(board[2][2])) || (isHim(board[0][2]) && isHim(board[1][1]) && isHim(board[2][0])))
	{
		return 2;
	}
	for (int i = 0; i < 3; i++)
	{
		if ((isMe(board[0][i]) && isMe(board[1][i]) && isMe(board[2][i])) || (isMe(board[i][0]) && isMe(board[i][1]) && isMe(board[i][2])))
		{
			return 1;
		}
		else if ((isHim(board[0][i]) && isHim(board[1][i]) && isHim(board[2][i])) || (isHim(board[i][0]) && isHim(board[i][1]) && isHim(board[i][2])))
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
// util
int TicTacToe::AIPlayer::xyBoard(int x, int y)
{
	return (((y * 3) + x) + 1);
}
bool TicTacToe::AIPlayer::isEmpty(Game::Status board)
{
	return board == Game::Status::Empty;
}
bool TicTacToe::AIPlayer::isMe(Game::Status board)
{
	if (playerType == Player::PlayerType::Player1)
	{
		return board == Game::Status::Player1;
	}
	else
	{
		return board == Game::Status::Player2;
	}
}
bool TicTacToe::AIPlayer::isHim(Game::Status board)
{
	if (playerType == Player::PlayerType::Player1)
	{
		return board == Game::Status::Player2;
	}
	else
	{
		return board == Game::Status::Player1;
	}
}
TicTacToe::Game::Status TicTacToe::AIPlayer::myPiece()
{
	if (playerType == Player::PlayerType::Player1)
	{
		return Game::Status::Player1;
	}
	else
	{
		return Game::Status::Player2;
	}
}
TicTacToe::Game::Status TicTacToe::AIPlayer::hisPiece()
{
	if (playerType == Player::PlayerType::Player1)
	{
		return Game::Status::Player2;
	}
	else
	{
		return Game::Status::Player1;
	}
}