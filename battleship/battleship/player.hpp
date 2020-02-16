//player.hpp
//Blake Caldwell and Theng Yang
//Febuary 9,2020
//header file for the player class


#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "board.hpp"

class Player
{
public:
	void setname(const std::string& name);
	std::string getname() const;
	void print();
	void placeShip();
	bool shoot(Board & p2);
	bool winCheck();
	Board& getBoard();

private:
	std::string _name;
	Board _myBoard;
	Board _guessBoard;
};

#endif