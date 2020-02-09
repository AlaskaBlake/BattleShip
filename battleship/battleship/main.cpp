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
	if (turn)
		cout << player1.getname();
	else
		cout << player2.getname();
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
		while (cin.get() != '\n') {}

		pass(turn,player1,player2);

		player2.print();
		while (cin.get() != '\n') {}
	}



	return 0;
}