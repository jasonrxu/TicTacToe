//
//  JasonAI.cpp
//  Tic Tac Toe AI
//
//  Created by Jason Xu on 7/22/15.
//  Copyright © 2015 Jason Xu. All rights reserved.
//

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include "JasonAI.hpp"
#include "Game.hpp"

struct Point {
    int column, row;
    int priority;
    
    bool operator < (const Point &p2) const {
        return this->priority < p2.priority;
    }
};

void SetPriorityWithBoard(const TicTacToe::Game::Status board[3][3], const TicTacToe::Player::PlayerType &playerType, Point &location);

int TicTacToe::JasonAI::nextMove(Game &game) {
    auto board = game.board;
    auto emptyPositions = std::vector<Point>();
    for (auto column = 0; column < 3; column++) {
        for (auto row = 0; row < 3; row++) {
            if (board[column][row] == Game::Empty) {
                emptyPositions.push_back({ column, row, 0 });
            }
        }
    }
    
    for (auto i = emptyPositions.begin(); i != emptyPositions.end(); i++) {
        SetPriorityWithBoard(board, playerType, *i);
    }
    
    std::sort(emptyPositions.begin(), emptyPositions.end());
    
    
//    for (auto i = emptyPositions.begin(); i != emptyPositions.end(); i++) {
//        using namespace std;
//        cout << i->column << ", " << i->row << ", " << i->priority << endl;
//    }
    
//    std::cout << std::endl << emptyPositions.back().column << ", " << emptyPositions.back().row << ", " << emptyPositions.back().priority << std::endl;
    
    auto index = emptyPositions.back().row * 3 + emptyPositions.back().column + 1;
    std::cout << std::endl << "AI Chose " << index << "." << std::endl << std::endl;
    
    std::cout << std::endl << "Continue?" << std::endl;
    
    std::string s;
    std::cin >> s;
    
    return index;
}

TicTacToe::JasonAI::JasonAI(TicTacToe::Player::PlayerType type) : Player(type) {
    
}

bool TwoInARow(TicTacToe::Game::Status type, TicTacToe::Game::Status row[3]) {
    int count = 0;
    for (auto i = 0; i < 3; i++) {
        if (row[i] == type) {
            count++;
        }
    }
    if (count >= 2) {
        return true;
    } else {
        return false;
    }
}

bool AtCorner(const Point &location) {
    if ((location.column == 0 || location.column == 2) &&
        (location.row == 0 || location.row == 2)) {
        return true;
    }
    return false;
}

void DiagonalWithBoard(const TicTacToe::Game::Status board[3][3], const Point &location, TicTacToe::Game::Status diagonal[3]) {
    diagonal[0] = board[location.column][location.row];
    diagonal[1] = board[1][1];
    diagonal[2] = board[(int)std::abs((double)location.column - 2)][(int)std::abs((double)location.row - 2)];
}

struct RowInfo {
    int Player1Count = 0;
    int Player2Count = 0;
    int EmptyCount = 0;
    
    RowInfo(const TicTacToe::Game::Status row[3]) {
        for (auto i = 0; i < 3; i++) {
            if (row[i] == TicTacToe::Game::Player1) Player1Count++;
            if (row[i] == TicTacToe::Game::Player2) Player2Count++;
            if (row[i] == TicTacToe::Game::Empty)   EmptyCount++;
        }
    }
    
    int countForStatus(TicTacToe::Game::Status status) {
        if (status == TicTacToe::Game::Player1) {
            return Player1Count;
        } else if (status == TicTacToe::Game::Player2) {
            return Player2Count;
        } else {
            return EmptyCount;
        }
    }
};

int NumberOfRowsContainingTwo(const TicTacToe::Game::Status board[3][3], const TicTacToe::Player::PlayerType &player, const Point &location) {
    auto column = board[location.column];
    auto columnInfo = RowInfo(column);
    
    TicTacToe::Game::Status row[3] = { board[0][location.row], board[1][location.row], board[2][location.row] };
    auto rowInfo = RowInfo(row);
    
    auto count = 0;
    
    if (columnInfo.countForStatus((TicTacToe::Game::Status)player) == 2 || rowInfo.countForStatus((TicTacToe::Game::Status)player) == 2) {
        count++;
    }
    
    if (AtCorner(location)) {
        TicTacToe::Game::Status diagonal[3];
        DiagonalWithBoard(board, location, diagonal);
        auto info = RowInfo(diagonal);
        if (info.countForStatus((TicTacToe::Game::Status)player) == 2) {
            count++;
        }
    }
    
    if (location.column == 1 && location.row == 1) {
        if (board[0][0] == (TicTacToe::Game::Status)player && board[2][2] == (TicTacToe::Game::Status)player) {
            count++;
        }
        if (board[2][0] == (TicTacToe::Game::Status)player && board[0][2] == (TicTacToe::Game::Status)player) {
            count++;
        }
    }
    
    return count;
}

int NumberOfRowsContainingOne(const TicTacToe::Game::Status board[3][3], const TicTacToe::Player::PlayerType &player, const Point &location) {
    
    using namespace TicTacToe;
    
    auto column = board[location.column];
    auto columnInfo = RowInfo(column);
    
    Game::Status row[3] = { board[0][location.row], board[1][location.row], board[2][location.row] };
    auto rowInfo = RowInfo(row);
    
    auto oppositePlayer = (Player::PlayerType)std::abs((float)player - 1);
    
    auto count = 0;
    
    if (rowInfo.countForStatus(Game::Empty) == 2 && rowInfo.countForStatus((Game::Status)player) == 1) {
        count++;
    }
    
    if (columnInfo.countForStatus(Game::Empty) == 2 && columnInfo.countForStatus((Game::Status)player) == 1) {
        count++;
    }
    
    if (AtCorner(location)) {
        Game::Status diagonal[3];
        DiagonalWithBoard(board, location, diagonal);
        auto info = RowInfo(diagonal);
        if (info.countForStatus(Game::Empty) == 2 && info.countForStatus((Game::Status)player) == 1) {
            count++;
        }
    }
    
    if (location.column == 1 && location.row == 1) {
        if (board[0][0] != (Game::Status)oppositePlayer && board[2][2] != (Game::Status)oppositePlayer) {
            if ((board[0][0] == Game::Status::Empty || board[2][2] == Game::Status::Empty) &&
                (int)board[0][0] + (int)board[2][2] == (int)Game::Status::Empty + (int)player) {
                count++;
            }
        }
        if (board[2][0] != (Game::Status)oppositePlayer && board[0][2] != (Game::Status)oppositePlayer) {
            if ((board[2][0] == Game::Status::Empty || board[0][2] == Game::Status::Empty) &&
                (int)board[2][0] + (int)board[0][2] == (int)Game::Status::Empty + (int)player) {
                count++;
            }
        }
    }
    
    return count;
}

int NumberOfEmptyRows(const TicTacToe::Game::Status board[3][3], const Point &location) {
    
    using namespace TicTacToe;
    
    auto column = board[location.column];
    auto columnInfo = RowInfo(column);
    
    Game::Status row[3] = { board[0][location.row], board[1][location.row], board[2][location.row] };
    auto rowInfo = RowInfo(row);
    
    auto count = 0;
    
    if (columnInfo.countForStatus(Game::Status::Empty) == 3) {
        count++;
    }
    
    if (rowInfo.countForStatus(Game::Status::Empty) == 3) {
        count++;
    }
    
    if (AtCorner(location)) {
        Game::Status diagonal[3];
        DiagonalWithBoard(board, location, diagonal);
        auto info = RowInfo(diagonal);
        if (info.countForStatus(Game::Status::Empty) == 3) {
            count++;
        }
    }
    
    if (location.column == 1 && location.row == 1) {
        if (board[0][0] == Game::Status::Empty && board[2][2] == Game::Status::Empty) {
            count++;
        }
        if (board[2][0] == Game::Status::Empty && board[0][2] == Game::Status::Empty) {
            count++;
        }
    }
    
    return count;
}

void SetPriorityWithBoard(const TicTacToe::Game::Status board[3][3], const TicTacToe::Player::PlayerType &currentPlayer, Point &location) {
    
    using namespace TicTacToe;
    
    auto oppositePlayer = (Player::PlayerType)std::abs((float)currentPlayer - 1);
    
    int priority = 0;
    
    priority += NumberOfRowsContainingTwo(board, currentPlayer, location) * 10000;
    
    priority += NumberOfRowsContainingTwo(board, oppositePlayer, location) * 1000;
    
    priority += NumberOfRowsContainingOne(board, currentPlayer, location) * 100;
    
    priority += NumberOfRowsContainingOne(board, oppositePlayer, location) * 10;
    
    priority += NumberOfEmptyRows(board, location);
    
    location.priority = priority;
    
}
