//board.hpp
//Blake Caldwell and Theng Yang
//Febuary 9, 2020
//header for the board class

#include <vector>

#include <ostream>

class Board {
public:
	Board();
	void print();
	bool writeShip(const int & length, const char & row, const int & col, const char & dir);
private:
	std::vector<char> _board;
};


