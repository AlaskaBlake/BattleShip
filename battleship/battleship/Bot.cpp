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

#include <algorithm>
using std::find;
using std::shuffle;

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

bool Bot::randomGuess(Board& p2) {
	while (true) {
		auto package = getRowColDir();
		char row = get<0>(package);
		int col = get<1>(package);

		int index = (row - 'A') * 10 + col;

		if (index >= 0 && index <= 99 && _guessBoard.getPos(index) != 'M' && _guessBoard.getPos(index) != 'H') {
			if (p2.getPos(index) == 'S') {
				p2.writeShot(index, 'H');
				_guessBoard.writeShot(index, 'H');
				if(_difficulty == 1)
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

Bot::Bot(const int& diff) : _difficulty(diff) {}

void Bot::setDiff(const int& diff) {
	_difficulty = diff;
}

void Bot::placeShip(Board& p2) {
	if (_difficulty == 2) {
		for (int i = 0; i < p2.getSize(); ++i) {
			if (p2.getPos(i) == 'S')
				_hitList.push_back(i);
		}

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int>
			randval(0, 99);

		for (int i = 0; i < 17; ++i) {
			int temp = randval(gen);
			if (find(_hitList.begin(), _hitList.end(), temp) == _hitList.end())
				_hitList.push_back(temp);
		}

		shuffle(_hitList.begin(), _hitList.end(), gen);
	}

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
	if (_difficulty == 2) {
		int index = _hitList.size() - 1;
		int last = _hitList[index];
		_hitList.pop_back();

		if (p2.getPos(last) == 'S') {
			p2.writeShot(last, 'H');
			_guessBoard.writeShot(last, 'H');
			return true;
		}
		else {
			p2.writeShot(last, 'M');
			_guessBoard.writeShot(last, 'M');
			return false;
		}
	}
	else if (_difficulty == 1) {
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

		return randomGuess(p2);
	}
	else {
		return randomGuess(p2);	
	}
}

bool Bot::winCheck() {
	return _guessBoard.totalHit();
}


Board& Bot::getBoard() {
	return _myBoard;
}