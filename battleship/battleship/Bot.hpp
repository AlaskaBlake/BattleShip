//Bot.hpp
//Blake Caldwell and Theng Yang
//Febuary 16, 2020
//header for the bot class

#ifndef BOT_HPP
#define BOT_HPP

#include "board.hpp"

#include <vector>

#include <tuple>

class Bot {
public:
	Bot(const int& diff);
	void setDiff(const int& diff);
	void placeShip(Board& p2);
	bool shoot(Board& p2);
	bool winCheck();
	Board& getBoard();

	bool randomGuess(Board& p2);
private:
	int _difficulty;
	Board _myBoard;
	Board _guessBoard;
	std::vector<std::tuple<int, bool, bool, bool, bool>> _hits;
	std::vector<int> _hitList;
};

#endif