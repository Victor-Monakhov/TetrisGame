#include "Field.h"

Field::Field(int windowWidth, int windowHeight) :
	_windowWidth{ windowWidth },
	_windowHeight{ windowHeight },
	_gameFieldHeight{ windowHeight - 6 },
	_gameFieldWidth{ windowWidth - 10 }
{
	_window = new int*[_windowHeight];
	for (int i{}; i < _windowHeight; i++) {
		_window[i] = new int[_windowWidth];
		for (int j{}; j < _windowWidth; j++) {
			_window[i][j] = 0;
		}
	}
	for (int i{ 0 }; i < _windowHeight; i++) {
		for (int j{ 0 }; j < _windowWidth; j++) {
			_window[0][j] = back_id::_wall_id;
			_window[i][0] = back_id::_wall_id;
			_window[_windowHeight - 1][j] = back_id::_wall_id;
			_window[i][_windowWidth - 1] = back_id::_wall_id;
			if (i < _gameFieldHeight) _window[i][_gameFieldWidth] = back_id::_wall_id;
			_window[_gameFieldHeight][j] = back_id::_wall_id;
		}
	}
	for (int i = 1; i < _gameFieldHeight; i += rand() % 5 + 1) {
		for (int j = 1; j < _gameFieldWidth; j += rand() % 6 + 1) {
			_window[i][j] = back_id::_star_id;
		}
	}
}
int** Field::getWindow()const {
	return _window;
}
int Field::getGameFieldWidth()const {
	return _gameFieldWidth;
}
int Field::getGameFieldHeight()const {
	return _gameFieldHeight;
}
Menu* Field::getMenuPointer() {
	return &_menu;
}

void Field::changeElement(int indexRow, int indexColumn, int value) {
	if (indexRow >= 0 && indexColumn >= 0 && indexRow <= _gameFieldHeight && indexColumn <= _gameFieldWidth) {
		_window[indexRow][indexColumn] = value;
	}
}
void Field::deleteLine() {
	int counter;
	for (int i{ 4 }; i < _gameFieldHeight; ++i) {
		counter = 0;
		for (int j{ 1 }; j < _gameFieldWidth; ++j) {
			if (_window[i][j] == back_id::_figure_id) {
				counter++;
				if (counter == _gameFieldWidth - 1) {
					for (int c{ i }; c > 4; --c) {
						for (int k{ _gameFieldWidth - 1 }; k > 0; --k) {
							if (_window[c][k] != back_id::_star_id || _window[c - 1][k] == back_id::_figure_id) {
								_window[c][k] = _window[c - 1][k];
							}
							else {
								_window[c + 1][k] = 0;
							}
						}
					}
					_menu.setLines(_menu.getLines() + 1);
					_menu.setScore(_menu.getScore() + 100);
					if (_menu.getLines() % 3 == 0)_menu.setLevel(_menu.getLevel() + 1);
				}
			}
		}
	}
}
Field::~Field() {
	if (_window != nullptr) {
		for (int i{}; i < _windowHeight; ++i) {
			delete [] _window[i];
		}
		delete[] _window;
	}
}