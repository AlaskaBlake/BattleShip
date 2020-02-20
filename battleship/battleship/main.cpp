//main.cpp
//Blake Caldwell and Theng Yang
//Febuary 9, 2020
//main file for the battleship game

#include "player.hpp"
#include "Bot.hpp"

#include <Windows.h>

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;
using std::getline;

#include <sstream>
using std::istringstream;


// intermission screen for pass and play
// bool turn is true for player1 turn
// bool turn is false for player2 turn
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


// overhead for player vs. player
// goes through name retrieval for both players, ship placements, and turn control 
int pvp() {
	Player player1;
	Player player2;
	bool turn = false; // True is player one and false for player two

	// ******************* name retrieval ***************************//
	cout << "Player one please enter your name and then hit enter: ";
	string temp;
	while (true) {
		getline(cin, temp);
		if (temp != "")
			break;
		cout << "Name must not be Empty. Please enter you name and then hit enter:" << endl;
	}
	player1.setname(temp);
	cout << endl << "Hello " << player1.getname() << endl;

	cout << endl << "Player two please enter your name and then hit enter: ";
	while (true) {
		getline(cin, temp);
		if (temp == "") {
			cout << "Name must not be Empty. Please enter you name and then hit enter:" << endl;
			continue;
		}
		else if (temp == player1.getname()) {
			cout << "Name taken. Please try again. Press enter to continue." << endl;
			continue;
		}
		break;
	}
	player2.setname(temp);
	cout << endl << "Hello " << player2.getname() << endl;

	cout << "Pass the computer to " << player1.getname() << " and hit enter when ready." << endl;
	while (cin.get() != '\n') {}
	system("CLS");

	// ******************* Place Ships ***************************//
	player1.placeShip();

	pass(turn, player1, player2);

	player2.placeShip();

	// ******************* turn overhead ***************************//
	while (true) {

		pass(turn, player1, player2);

		player1.print();
		if (player1.shoot(player2.getBoard())) {
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

		pass(turn, player1, player2);

		player2.print();
		if (player2.shoot(player1.getBoard())) {
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
}


// overhead for player vs. bot
// goes through name retrieval for the player, ship placements for player and bot,
// and turn overhead
int pvbot() {

	// ******************* name retrieval ***************************//
	Player player1;
	cout << "Player one please enter your name and then hit enter: ";
	string temp;
	while (true) {
		getline(cin, temp);
		if (temp != "")
			break;
		cout << "Name must not be Empty. Please enter you name and then hit enter:" << endl;
	}
	player1.setname(temp);

	char choice;

	// ******************* bot difficulty selection ***************************//
	while (true) {
		cout << endl << "Hello " << player1.getname() << " would you like an easy computer or a harder computer? Please \"E\" for an easy bot, \"M\" for a medium bot, or \"H\" for a hard bot" << endl;

		string option;
		getline(cin, option);
		istringstream ins(option);
		ins >> choice;
		if (!ins || (choice != 'E' && choice != 'e' && choice != 'H' && choice != 'h' && choice != 'M' && choice != 'm')) {
			cout << "Bad input please try again. Hit enter to continue." << endl;
			continue;
		}

		break;
	}

	Bot bot(0);

	if (choice == 'M' || choice == 'm')
		bot.setDiff(1);
	if (choice == 'H' || choice == 'h')
		bot.setDiff(2);


	// ******************* ship placement ***************************//
	player1.placeShip();
	system("CLS");

	cout << endl << endl << endl << "Bot placing ships";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";

	bot.placeShip(player1.getBoard());
	cout << ".";
	Sleep(1000);

	system("CLS");


	// ******************* turn overhead ***************************//
	while (true) {
		player1.print();

		if (player1.shoot(bot.getBoard())) {
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

		system("CLS");

		cout << endl << endl << endl << "Bot taking shot";
		Sleep(1000);
		cout << ".";
		Sleep(1000);
		cout << ".";
		Sleep(1000);
		cout << "." << endl;

		if (bot.shoot(player1.getBoard())) {
			system("CLS");
			if (bot.winCheck()) {
				cout << "Computer wins!!!!" << endl;
				return 0;
			}
			
			cout << endl << endl << endl << "Oh No, you got hit! Press enter to continue." << endl;
		}
		else {
			cout << endl << endl << endl << "That was a close miss by the Computer. Press enter to continue." << endl;
		}
		while (cin.get() != '\n') {}
		system("CLS");
		
	}
}


// initial prompt to user to choose a game mode
// then calls proper function
int main() {
	char answer;
	while (true) {
		cout << "Would you like to play BattleShip vs another player (locally) or against a computer?" << endl;
		cout << "For Computer hit \"C\" for Person hit \"P\" and then enter." << endl;
		string input;
		getline(cin, input);
		istringstream ins(input);
		ins >> answer;
		if (!ins || (answer != 'c' && answer != 'C' && answer != 'p' && answer != 'P')) {
			cout << "Bad input please try again. Press enter to continue." << endl;
			while (cin.get() != '\n') {}
			continue;
		}

		break;
	}

	if (answer == 'c' || answer == 'C')
		pvbot();
	if (answer == 'p' || answer == 'P')
		pvp();

	return 0;
}