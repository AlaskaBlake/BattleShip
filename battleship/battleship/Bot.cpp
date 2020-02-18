//Bot.cpp
//Blake Caldwell and Theng Yang
//Febuary 16, 2020
//cpp for bot class 

#include "Bot.hpp"

#include<random>
using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;

#include<tuple>
using std::tuple;
using std::make_tuple;
using std::get;

auto getRowColDir() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int>
		randval(0, 99);

	int rand = randval(gen);
	char row = (rand % 10) + 'A';
	int col = rand / 10;
	int dirInt = randval(gen) % 4;
	char dir;

	switch (dirInt)
	{
	case 0:
		dir = 'N';
		break;
	case 1:
		dir = 'E';
		break;
	case 2:
		dir = 'S';
		break;
	case 3:
		dir = 'W';
		break;
	}

	return make_tuple(row, col, dir);
}

Bot::Bot(const bool& diff) : _difficulty(diff) {}

void Bot::setDiff(const bool& diff) {
	_difficulty = diff;
}

void Bot::placeShip() {


	for (int i = 5; i > 1; --i) {

		while (true) {
			auto package = getRowColDir();

			char row = get<0>(package);
			int col = get<1>(package);
			char dir = get<2>(package);

			if (_myBoard.writeShip(i, row, col, dir)) {
				break;
			}
		}
	}

	while (true){
		auto package = getRowColDir();

		char row = get<0>(package);
		int col = get<1>(package);
		char dir = get<2>(package);

		if (_myBoard.writeShip(3, row, col, dir))
			break;
	}

}

bool Bot::shoot(Board& p2) {
	if (_difficulty) {
		for (int i = 0; i < _hits.size(); ++i) {
			if (!(get<1>(_hits[i]))){
				get<1>(_hits[i]) = true;
				if (get<0>(_hits[i]) - 10 >= 0 && _guessBoard.getPos(get<0>(_hits[i]) - 10) != 'M' && _guessBoard.getPos(get<0>(_hits[i]) - 10) != 'H') {
					if (p2.getPos(get<0>(_hits[i]) - 10) == 'S') {
						p2.writeShot(get<0>(_hits[i]) - 10, 'H');
							_guessBoard.writeShot(get<0>(_hits[i]) - 10, 'H');
							_hits.push_back(make_tuple(get<0>(_hits[i]) - 10, false, false, true, false));
							return true;
					}
					else {
						p2.writeShot(get<0>(_hits[i]) - 10, 'M');
							_guessBoard.writeShot(get<0>(_hits[i]) - 10, 'M');
							return false;
					}
				}
			}
			if (!(get<2>(_hits[i]))){
				get<2>(_hits[i]) = true;
				if (get<0>(_hits[i])/10 == (get<0>(_hits[i])+1) / 10 && _guessBoard.getPos(get<0>(_hits[i]) + 1) != 'M' && _guessBoard.getPos(get<0>(_hits[i]) + 1) != 'H') {
					if (p2.getPos(get<0>(_hits[i]) + 1) == 'S') {
						p2.writeShot(get<0>(_hits[i]) + 1, 'H');
						_guessBoard.writeShot(get<0>(_hits[i]) + 1, 'H');
						_hits.push_back(make_tuple(get<0>(_hits[i]) + 1, false, false, false, true));
						return true;
					}
					else {
						p2.writeShot(get<0>(_hits[i]) + 1, 'M');
						_guessBoard.writeShot(get<0>(_hits[i]) + 1, 'M');
						return false;
					}
				}
			}
			if (!(get<3>(_hits[i]))) {
				get<3>(_hits[i]) = true;
				if (get<0>(_hits[i]) + 10 < 100 && _guessBoard.getPos(get<0>(_hits[i]) + 10) != 'M' && _guessBoard.getPos(get<0>(_hits[i]) + 10) != 'H') {
					if (p2.getPos(get<0>(_hits[i]) + 10) == 'S') {
						p2.writeShot(get<0>(_hits[i]) + 10, 'H');
						_guessBoard.writeShot(get<0>(_hits[i]) + 10, 'H');
						_hits.push_back(make_tuple(get<0>(_hits[i]) + 10, true, false, false, false));
						return true;
					}
					else {
						p2.writeShot(get<0>(_hits[i]) + 10, 'M');
						_guessBoard.writeShot(get<0>(_hits[i]) + 10, 'M');
						return false;
					}
				}
			}
			if (!(get<4>(_hits[i]))){
				get<4>(_hits[i]) = true;
				if (get<0>(_hits[i]) / 10 == (get<0>(_hits[i]) - 1) / 10 && _guessBoard.getPos(get<0>(_hits[i]) - 1) != 'M' && _guessBoard.getPos(get<0>(_hits[i]) - 1) != 'H') {
					if (p2.getPos(get<0>(_hits[i]) - 1) == 'S') {
						p2.writeShot(get<0>(_hits[i]) - 1, 'H');
						_guessBoard.writeShot(get<0>(_hits[i]) - 1, 'H');
						_hits.push_back(make_tuple(get<0>(_hits[i]) - 1, false, true, false, false));
						return true;
					}
					else {
						p2.writeShot(get<0>(_hits[i]) - 1, 'M');
						_guessBoard.writeShot(get<0>(_hits[i]) - 1, 'M');
						return false;
					}
				}
			}
		}

		while (true) {

			auto package = getRowColDir();
			char row = get<0>(package);
			int col = get<1>(package);

			int index = (row - 'A') * 10 + col;

			if (index >= 0 && index <= 99 && _guessBoard.getPos(index) != 'M' && _guessBoard.getPos(index) != 'H') {
				if (p2.getPos(index) == 'S') {
					p2.writeShot(index, 'H');
					_guessBoard.writeShot(index, 'H');
					_hits.push_back(make_tuple(index, false, false, false, false));
					return true;
				}
				else {
					p2.writeShot(index, 'M');
					_guessBoard.writeShot(index, 'M');
					return false;
				}

			}
		}

	}
	else {
		while (true) {
			auto package = getRowColDir();
			char row = get<0>(package);
			int col = get<1>(package);

			int index = (row - 'A') * 10 + col;

			if (index >= 0 && index <= 99 && _guessBoard.getPos(index) != 'M' && _guessBoard.getPos(index) != 'H') {
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
	}
}

bool Bot::winCheck() {
	return _guessBoard.totalHit();
}


Board& Bot::getBoard() {
	return _myBoard;
}