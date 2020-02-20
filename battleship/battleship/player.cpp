//player.cpp
//Blake Caldwell and Theng Yang
//Feburary 9, 2020
// Representation of a human player for a game of Battleship

#include "player.hpp"

using std::string;
using std::getline;

#include <Windows.h>
using std::system;


#include<iostream>
using std::cout;
using std::endl;
using std::cin;

#include<sstream>
using std::istringstream;

#include <algorithm>
using std::move;

// not a member function
// utility function to get user input on ship placement location.
bool getCord(const int& length, Board & _myBoard) {
	char row;
	int col;
	char dir;
	string cord;

	cout << "Please enter the coordinate of the nose of your ship and hit enter to continue." << endl;
	getline(cin, cord);

		istringstream instream(cord);
		instream >> row;
		instream >> col;

		row = toupper(row);
		if (row >= 'A' && row <= 'J' && cord[1] >='0' && cord[1] <='9') {
		
			cout << "What direction would you like to place this ship? Please enter one of the following: North (N) East (E) South (S) West (W) and hit enter." << endl;
			cin >> dir;
			dir = toupper(dir);
			if (dir == 'N' || dir == 'E' || dir == 'S' || dir == 'W') {
				if (_myBoard.writeShip(length, row, col, dir)) {
					system("CLS");
					return false;
				}
			}

		}
		else {

			cout << "NO valid coordinate, please hit Enter try again." << endl;
		}
	
	return true;
}


void Player::setname(const string& name) {
	_name = name;
}

string Player::getname() const {
	return _name;
}

// call board member function print() to print the boards
void Player::print() {
	_guessBoard.print();
	_myBoard.print();
}

// go through process of all ship placement with the player
void Player::placeShip() {

	while (true) {
		int choice = 0;
		string sChoice;

		bool five = true;
		bool four = true;
		bool three1 = true;
		bool three2 = true;
		bool two = true;

		// loop until every ship is placed
		while (five || four || three1 || three2 || two) {
			_myBoard.print();
			cout << "Please select which ship you want to place by entering their number and hitting enter." << endl;

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

			if (choice == 5 && five) {
				five = getCord(5, _myBoard);
			}
			else if (choice == 4 && four) {
				four = getCord(4, _myBoard);
			}
			else if (choice == 3 && three1) {
				three1 = getCord(3, _myBoard);
			}
			else if (choice == 3 && three2) {
				three2 = getCord(3, _myBoard);
			}
			else if (choice == 2 && two) {
				two = getCord(2, _myBoard);
			}
			else {
				cout << "Invalid ship selectioin. Please hit Enter to try again." << endl;
			}

			while (std::cin.get() != '\n') {}

			system("CLS");
		}

		char answer;

		// get valid user input 
		while (true) {
			_myBoard.print();
			cout << "Are you happy with your ship placement? Press 'Y' for yes or 'N' for no then hit enter." << endl;
			string input;
			getline(cin, input);
			istringstream ins(input);
			ins >> answer;
			if (!ins) {
				cout << "Not a valid input. Please hit enter to continue." << endl;
				while (cin.get() != '\n') {}
				system("CLS");
				continue;
			}

			answer = toupper(answer);

			if (answer == 'Y' || answer == 'N')
				break;
			system("CLS");
			cout << "Not a valid option. Please hit enter to try again." << endl;
		}

		// finish ship placement 
		if (answer == 'Y')
			break;
		
		// create new board and overide old board to start again.
		Board temp;
		_myBoard = move(temp);
		cout << "Press enter to start again." << endl;
		while (cin.get() != '\n') {}
		system("CLS");

	}
}

// get position player want to shoot at opponent
bool Player::shoot(Board & p2) {

	char row;
	int col = -1;
	char dir;
	string cord;

	while (true) {
		cout << endl << "Please enter the coordinate where you would like to shoot on your opponent's board and then hit enter." << endl;
		getline(cin, cord);
		istringstream instream(cord);
		instream >> row;
		instream >> col;
		row = toupper(row);
		if (!(row >= 'A' && row <= 'J' && cord[1] >= '0' && cord[1] <= '9'))
			continue;

		int index = 0;

		index = (row - 'A') * 10 + col;

		if (_guessBoard.getPos(index) == 'H' || _guessBoard.getPos(index) == 'M')
			continue;

		if (p2.getPos(index) == 'S') {
			p2.writeShot(index, 'H');
			_guessBoard.writeShot(index, 'H');
			return true;
		}
		else {
			p2.writeShot(index, 'M');
			_guessBoard.writeShot(index, 'M');
			return false;
		}
	}

}

// return true if game is over. 
bool Player::winCheck() {
	return _guessBoard.totalHit();
}

// return a reference player ship board
Board& Player::getBoard() {
	return _myBoard;
}