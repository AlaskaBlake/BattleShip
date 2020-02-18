//board.cpp
//Blake Caldwell and Theng Yang
//Febuary 9, 2020
//does board stuff for battleship

#include "board.hpp"

using std::ostream;

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>
using std::count;

#include <Windows.h>

Board::Board(){
	for (int i = 0; i < 100; ++i)
		_board.push_back('-');
}

void Board::print() {
	//built in array for console text attributes
	// 0x30 - cyan background black text
	// 0x40 - red background black text
	// 0x80 - gray background black text
	// 0xF0 - white background black text

	const WORD colors[] = { 0x30, 0x40, 0x80, 0xF0 };

	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD index = 0;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	char row = 'A';

	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	cout << "   0    1    2    3    4    5    6    7    8    9" << endl;

	for (int i = 0; i < _board.size(); i += 10) {//for the entire board

		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
		cout << (char)('A' + (i / 10)) << " ";

		for (int j = 0; j < 2; ++j) {//do each row twice
			if (j % 2 == 1) {
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
				cout << "  ";
			}

			for (int k = 0; k < 10; ++k) {//for every row position
				if (_board[i + k] == '-') {
					SetConsoleTextAttribute(hstdout, colors[0]);
					cout << "    ";
				}
				else if (_board[i + k] == 'S') {
					SetConsoleTextAttribute(hstdout, colors[2]);
					cout << "    ";
				}
				else if (_board[i + k] == 'H') {
					SetConsoleTextAttribute(hstdout, colors[1]);
					cout << "    ";
				}
				else if (_board[i + k] == 'M') {
					SetConsoleTextAttribute(hstdout, colors[3]);
					cout << "    ";
				}

				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
				cout << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}

	SetConsoleTextAttribute(hstdout, csbi.wAttributes);


}

bool Board::writeShip(const int& length, const char& row, const int& col, const char& dir) {

	int index = ((row - 'A') * 10) + col;

	int buttIn = 0;
	bool flag = false;

	if (dir == 'E') {
		if (index / 10 == (index + length) / 10) {

			for (int i = index; i < index + length; ++i) {
				if (_board[i] == 'S')
					flag = true;
			}

			if (!flag) {
				for (int i = index; i < index + length; ++i) {
					_board[i] = 'S';
				}
				return true;
			}

		}
	
	}

	if (dir == 'W') {
		if (index!= 0 && (index / 10 == (index - length) / 10)) {

			for (int i = index - length + 1; i <= index; ++i) {
				if (_board[i] == 'S')
					flag = true;
			}

			if (!flag) {
				for (int i = index - length + 1; i <= index; ++i) {
					_board[i] = 'S';
				}
				return true;
			}
		}

	}

	if (dir == 'N') {

		int copy = length;

		copy *= 10;

		if (index - copy >= 0) {
			for (int i = index; i > index - copy; i -= 10) {
				if (_board[i] == 'S')
					flag = true;
			}

			if (!flag) {
				for (int i = index; i > index - copy; i -= 10) {
					_board[i] = 'S';
				}
				return true;
			}
		}

	}

	if (dir == 'S') {

		int copy = length;

		copy *= 10;

		if (index + copy <= 99) {
			for (int i = index; i < index + copy; i += 10) {
				if(_board[i] == 'S')
					flag = true;
			}
			if (!flag) {
				for (int i = index; i < index + copy; i += 10) {
					_board[i] = 'S';
				}
				return true;
			}
		}

	}
	return false;
}

char Board::getPos(const int& index) {
	return _board[index];
}

void Board::writeShot(const int& index, const char& letter) {
	_board[index] = letter;
}

bool Board::totalHit() {
	if (count(_board.begin(), _board.end(), 'H') == 17)
		return true;
	return false;
}