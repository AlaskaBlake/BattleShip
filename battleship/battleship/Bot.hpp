//Bot.hpp
//Blake Caldwell and Theng Yang
//Febuary 16, 2020
//header for the bot class

#ifndef BOT_HPP
#define BOT_HPP

#include "board.hpp"

class Bot {
public:
	Bot(const bool& diff);
	void setDiff(const bool& diff);
	void placeShip();
	bool shoot(Board& p2);
	bool winCheck();
	Board& getBoard();
private:
	bool _difficulty;
	Board _myBoard;
	Board _guessBoard;
};

#endif