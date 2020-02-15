//main.cpp
//Blake Caldwell and Theng Yang
//Febuary 9, 2020
//main file for the battleship game

#include "player.hpp"

#include <Windows.h>

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;
using std::getline;

void pass(bool & turn, const Player& player1, const Player& player2) {
	system("CLS");
	cout << "Pass the computer to ";
	if (turn) {
		cout << player1.getname();
		turn = false;
	}
	else {
		cout << player2.getname();
		turn = true;
	}
	cout << " and then hit enter." << endl;
	while (cin.get() != '\n') {}
	system("CLS");
}

int main() {
	Player player1;
	Player player2;
	bool turn = false; // True is player one and false for player two

	cout << "Player one please enter your name: ";
	string temp;
	getline(cin, temp);
	player1.setname(temp);
	cout << endl << "Hello " << player1.getname() << endl;

	cout << endl << "Player two please enter your name: ";
	getline(cin, temp);
	player2.setname(temp);
	cout << endl << "Hello " << player2.getname() << endl;

	cout << "Pass the computer to " << player1.getname() << " and hit enter when ready" << endl;
	while (cin.get() != '\n') {}
	system("CLS");

	player1.placeShip();

	pass(turn, player1, player2);

	player2.placeShip();

	while (true) {


		pass(turn, player1, player2);

		player1.print();
		if (player1.shoot(player2)) {
			system("CLS");
			if (player1.winCheck()) {
				cout << player1.getname() << " wins!!!!" << endl;
				return 0;
			}
			player1.print();
			cout << "Good HIT! Press enter to continue." << endl;
		}
		else {
			system("CLS");
			player1.print();
			cout << "That was a miss. Press enter to continue." << endl;
		}
		while (cin.get() != '\n') {}

		pass(turn,player1,player2);

		player2.print();
		if (player2.shoot(player1)) {
			system("CLS");
			if (player2.winCheck()) {
				cout << player2.getname() << " wins!!!!" << endl;
				return 0;
			}
			player2.print();
			cout << "Good HIT! Press enter to continue." << endl;
		}
		else {
			system("CLS");
			player2.print();
			cout << "That was a miss. Press enter to continue." << endl;
		}
		while (cin.get() != '\n') {}
	}



	return 0;
}