//board.hpp
//Blake Caldwell and Theng Yang
//Febuary 9, 2020
//header for the board class

#ifndef BOARD_HPP
#define BOARD_HPP


#include <vector>

#include <ostream>

// representation of an 10X10 battleship board
class Board {
public:
	Board();
	void print();
	bool writeShip(const int & length, const char & row, const int & col, const char & dir);
	char getPos(const int& index);
	void writeShot(const int& index, const char& letter);
	bool totalHit();
	int getSize();
private:
	std::vector<char> _board;
};

#endif // !BOARD_HPP
