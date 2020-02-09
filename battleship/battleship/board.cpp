//board.cpp
//Blake Caldwell and Theng Yang
//Febuary 9, 2020
//does board stuff for battleship

#include "board.hpp"

using std::ostream;

#include <iostream>
using std::cout;
using std::endl;

Board::Board(){
	for (int i = 0; i < 100; ++i)
		_board.push_back('-');
}

void Board::print() {
	cout << "  0 1 2 3 4 5 6 7 8 9";

	for (int i = 0; i < _board.size(); ++i)
	{
		if (i % 10 == 0)
			cout << endl << (char) ('A'+(i/10))<<" " << _board[i];
		else
			cout << _board[i];			
		cout << " ";
	}
	cout << endl;
}

bool Board::writeShip(const int& length, const char& row, const int& col, const char& dir) {
	int index = 0;

	switch (row) {
	case 'A':
		break;

	case 'B':
		index = 10;
		break;

	case 'C':
		index = 20;
		break;

	case 'D':
		index = 30;
		break;

	case 'E':
		index = 40;
		break;

	case 'F':
		index = 50;
		break;

	case 'G':
		index = 60;
		break;

	case 'H':
		index = 70;
		break;

	case 'I':
		index = 80;
		break;

	case 'J':
		index = 90;
		break;
	}

	index += col;

	int buttIn = 0;

	if (dir == 'E') {
		if (index / 10 == (index + length) / 10) {

			for (int i = index; i < index + length; ++i) {
				_board[i] = 'S';
			}
			return true;

		}
	
	}

	if (dir == 'W') {
		if (index / 10 == (index - length) / 10) {

			for (int i = index-length+1; i <= index; ++i) {
				_board[i] = 'S';
			}
			return true;
		}

	}

	if (dir == 'N') {

		int copy = length;

		copy *= 10;

		if (index - copy >= 0) {
			for (int i = index; i > index-copy; i-=10) {
				_board[i] = 'S';
			}
			return true;
		}

	}

	if (dir == 'S') {

		int copy = length;

		copy *= 10;

		if (index + copy <= 99) {
			for (int i = index; i < index + copy; i += 10) {
				_board[i] = 'S';
			}
			return true;
		}

	}
	return false;
}