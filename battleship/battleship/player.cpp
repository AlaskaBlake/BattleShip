//player.cpp
//Blake Caldwell and Theng Yang
//Feburary 9, 2020
//

#include "player.hpp"


using std::string;
using std::getline;

#include<iostream>
using std::cout;
using std::endl;
using std::cin;

#include<sstream>
using std::istringstream;

bool getCord(const int& length, Board & _myBoard) {
	char row;
	int col;
	char dir;
	string cord;

	cout << "Please select the coordinate of the nose of your ship" << endl;
	getline(cin, cord);
	istringstream instream(cord);
	instream >> row;
	instream >> col;

	if (row >= 'A' && row<='J') {
		if (col >= 0 && col <= 9) {

			cout << "What direction would you like to place this ship? north (N) east (E) south (S) west (W)" << endl;
			cin >> dir;

			if (dir == 'N' || dir == 'E' || dir == 'S' || dir == 'W') {
				if (_myBoard.writeShip(length, row, col, dir)) {

					cout << "Ship placed." << endl;
					return false;
				}
				else {
					cout << "Bad ship placement. Try again." << endl;
				}
			}

		}
		else {
			cout << "NO valid coordinate, please try again." << endl;
		}
		
	}
	else {
		cout << "NO valid coordinate, please try again." << endl;
	}

	return true;
}
void Player::setname(const string& name) {
	_name = name;
}

string Player::getname() const {
	return _name;
}

void Player::print() {
	_guessBoard.print();
	_myBoard.print();
}

void Player::placeShip() {
	int choice = 0;
	string sChoice;
	
	bool five = true;
	bool four = true;
	bool three1 = true;
	bool three2 = true;
	bool two = true;

	while (five || four || three1 || three2 || two) {
		_myBoard.print();
		cout << "Please select which ship you want to place by entering their number." << endl;

		if (five) {
			cout << "Place five? (5)" << endl;
		}
		if (four) {
			cout << "Place four? (4)" << endl;
		}
		if (three1) {
			cout << "Place three? (3)" << endl;
		}
		if (three2) {
			cout << "Place three? (3)" << endl;
		}
		if (two) {
			cout << "Place two? (2)" << endl;
		}

		getline(cin, sChoice);
		istringstream ins(sChoice);
		ins >> choice;

		if (choice == 5) {
			five = getCord(5, _myBoard);
		}
		else if (choice == 4) {
			four = getCord(4, _myBoard);
		}
		else if (choice == 3 && three1) {
			three1 = getCord(3, _myBoard);
		}
		else if (choice == 3) {
			three2 = getCord(3, _myBoard);
		}
		else if (choice == 2) {
			two = getCord(2, _myBoard);
		}

		while (std::cin.get() != '\n') {}

	}

}