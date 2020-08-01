#include "Figure.h"


//constructor
Figure::Figure(Field* field) :
	_field{ field },
	_quantity{ 7 },
	_turnQuantity{ 4 },
	_random{ rand() % 7 },
	_nextRandom{ rand() % 7 },
	_turn{},
	_levelSpeed{ 3 },
	_speed{ _levelSpeed },
	_currPos{ (short)field->getGameFieldWidth() / 2, 4 } 
{
	_figuresOptions = new int***[_quantity];
	for (int i{}; i < _quantity; ++i) {
		_figuresOptions[i] = new int**[_turnQuantity];
		for (int j{}; j < _turnQuantity; ++j) {
			_figuresOptions[i][j] = new int*[_turnQuantity];
		}
	}
	static int LineV[4][2] = { { 0,0 },{ 0,1 },{ 0,1 },{ 0,1 } };
	static int LineG[4][2] = { { 0,0 },{ 1,0 },{ 1,0 },{ 1,0 } };
	static int ZagV[4][2] = { { 0,0 },{ 0,1 },{ 1,0 },{ 0,1 } };
	static int ZagG[4][2] = { { 1,0 },{ 1,0 },{ -2, 1 },{ 1,0 } };
	static int ZigV[4][2] = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,1 } };
	static int ZigG[4][2] = { { 0,0 },{ 1,0 },{ 0,1 },{ 1,0 } };
	static int Cube[4][2] = { { 0,0 },{ 1,0 },{ -1,1 },{ 1,0 } };
	static int TV0[4][2] = { { 0,0 },{ 0,1 },{ 1,0 },{ -1,1 } };
	static int TG1[4][2] = { { 0,0 },{ 1,0 },{ 1,0 },{ -1,1 } };
	static int TV2[4][2] = { { 1,0 },{ -1,1 },{ 1,0 },{ 0,1 } };
	static int TG3[4][2] = { { 1,0 },{ -1,1 },{ 1,0 },{ 1,0 } };
	static int HookRV0[4][2] = { { 0,0 },{ 1,0 },{ -1,1 },{ 0,1 } };
	static int HookRG1[4][2] = { { 0,0 },{ 1,0 },{ 1,0 },{ 0,1 } };
	static int HookRV2[4][2] = { { 1,0 },{ 0,1 },{ -1,1 },{ 1,0 } };
	static int HookRG3[4][2] = { { 0,0 },{ 0,1 },{ 1,0 },{ 1,0 } };
	static int HookLV0[4][2] = { { 0,0 },{ 1,0 },{ 0,1 },{ 0,1 } };
	static int HookLG1[4][2] = { { 2,0 },{ -2,1 },{ 1,0 },{ 1,0 } };
	static int HookLV2[4][2] = { { 0,0 },{ 0,1 },{ 0,1 },{ 1,0 } };
	static int HookLG3[4][2] = { { 0,0 },{ 1,0 },{ 1,0 },{ -2,1 } };
	_currCoords = new COORD[5];
	_pastCoords = new COORD[5];
	for (int i{}; i < 5; i++) {
		if (i < 4) {
			_figuresOptions[0][0][i] = _figuresOptions[0][2][i] = LineV[i];
			_figuresOptions[0][1][i] = _figuresOptions[0][3][i] = LineG[i];
			_figuresOptions[1][0][i] = _figuresOptions[1][2][i] = ZagV[i];
			_figuresOptions[1][1][i] = _figuresOptions[1][3][i] = ZagG[i];
			_figuresOptions[2][0][i] = _figuresOptions[2][2][i] = ZigV[i];
			_figuresOptions[2][1][i] = _figuresOptions[2][3][i] = ZigG[i];
			_figuresOptions[3][0][i] = _figuresOptions[3][1][i] = _figuresOptions[3][2][i] = _figuresOptions[3][3][i] = Cube[i];
			_figuresOptions[4][0][i] = TV0[i];
			_figuresOptions[4][1][i] = TG1[i];
			_figuresOptions[4][2][i] = TV2[i];
			_figuresOptions[4][3][i] = TG3[i];
			_figuresOptions[5][0][i] = HookRV0[i];
			_figuresOptions[5][1][i] = HookRG1[i];
			_figuresOptions[5][2][i] = HookRV2[i];
			_figuresOptions[5][3][i] = HookRG3[i];
			_figuresOptions[6][0][i] = HookLV0[i];
			_figuresOptions[6][1][i] = HookLG1[i];
			_figuresOptions[6][2][i] = HookLV2[i];
			_figuresOptions[6][3][i] = HookLG3[i];
		}
		_currCoords[i] = { 0, 0 };
		_pastCoords[i] = { 0, 0 };
	}
}
//getters
COORD Figure::getCurrPosition()const {
	return _currPos;
}
int Figure::getLevelSpeed()const {
	return _levelSpeed;
}
int** Figure::getFigure()const {
	return _figuresOptions[_random][_turn];
}
int** Figure::getNextFigure()const {
	return _figuresOptions[_nextRandom][0];
}
COORD* Figure::getCurrCoords()const {
	return _currCoords;
}
COORD* Figure::getPastCoords()const {
	return _pastCoords;
}
int Figure::getSpeed()const {
	return _speed;
}
//setters
void Figure::setCurrPosition(int X, int Y) {
	_currPos.X = (short)X;
	_currPos.Y = (short)Y;
}
void Figure::setTurn(int turn) {
	_turn = turn;
}
void Figure::setRandom(int random) {
	_random = random;
}
void Figure::setCurrCoords(int index, COORD value) {
	if (index >= 0 && index < 5) _currCoords[index] = value;
}
void Figure::setSpeed(int speed) {
	_speed = speed;
}
//functions
//public
void Figure::coordMemory() {
	for (int i{}; i < 5; ++i)
		_pastCoords[i] = _currCoords[i];
}
void Figure::checkWalls(int leftWall, int rightWall) {
	if (_currPos.X < (short)leftWall) _currPos.X = leftWall;
	if (_random == 0) {
		if (_currPos.X > (short)rightWall + 1 && (_turn == 0 || _turn == 2)) _currPos.X = rightWall + 1;
		if (_currPos.X > (short)rightWall - 2 && (_turn == 1 || _turn == 3)) _currPos.X = rightWall - 2;
	}
	else {
		if (_currPos.X > (short)rightWall && (_turn == 0 || _turn == 2)) _currPos.X = rightWall;
		if (_currPos.X > (short)rightWall - 1 && (_turn == 1 || _turn == 3)) _currPos.X = rightWall - 1;
	}
}
void Figure::rotate() {
	if (_random != 3) ++_turn;
	if (checkSideCollision(true) || checkRotateCollision()) --_turn;
	if (_turn >= 4) _turn = 0;
	if (_turn < 0) _turn = 3;
}
void Figure::goToNextFigure() {
	if (_currCoords[4].Y + 1 == _field->getGameFieldHeight() || checkLowerCollision()) {
		_currPos = { (short)_field->getGameFieldWidth() / 2, 2 };
		for (int i{}; i < 4; ++i) {
			_field->changeElement(_currCoords[i + 1].Y, _currCoords[i + 1].X, 2);
		}
		_random = _nextRandom;
		_nextRandom = rand() % 7;
		_turn = 0;
		_field->deleteLine();
		_field->getMenuPointer()->setFigures(_field->getMenuPointer()->getFigures() + 1);
		_levelSpeed = _field->getMenuPointer()->getLevel() * 4;
		_speed = _levelSpeed;
	}
}
bool Figure::checkSideCollision(bool flag) {
	bool temp = false;
	for (int i{ 1 }; i < 5; ++i) {
		if (flag) temp = _field->getWindow()[_currCoords[i].Y][_currCoords[i].X + 1] == back_id::_figure_id;
		else temp = _field->getWindow()[_currCoords[i].Y][_currCoords[i].X - 1] == back_id::_figure_id;
		if (temp == true)  return true;
	}
	return false;
}
Figure::~Figure() {
	if (_figuresOptions != nullptr) {
		for (int i{}; i < 7; ++i) {
			delete[] _figuresOptions[i];
		}
		delete[] _figuresOptions;
	}
	if (_currCoords != nullptr) delete[] _currCoords;
	if (_pastCoords != nullptr) delete[] _pastCoords;
}
//private
bool Figure::checkLowerCollision() {
	for (int i{ 1 }; i < 5; ++i) {
		if (_field->getWindow()[_currCoords[i].Y + 1][_currCoords[i].X] == back_id::_figure_id) {
			return true;
		}
	}
	return false;
}
bool Figure::checkRotateCollision() {
	for (int i{ 1 }; i < 5; ++i) {
		switch (_random) {
		case 0: {
			if (_field->getWindow()[_currCoords[i].Y + 1][_currCoords[i].X] == back_id::_figure_id ||
				_field->getWindow()[_currCoords[i].Y + 2][_currCoords[i].X] == back_id::_figure_id ||
				_field->getWindow()[_currCoords[i].Y + 3][_currCoords[i].X] == back_id::_figure_id) {
				return true;
			}
			break;
		}
		case 1:
		case 2:
		case 4:
		case 5:
		case 6: {
			if (_field->getWindow()[_currCoords[i].Y + 1][_currCoords[i].X] == back_id::_figure_id ||
				_field->getWindow()[_currCoords[i].Y + 2][_currCoords[i].X] == back_id::_figure_id) {
				return true;
			}
			break;
		}
		}
	}
	return false;
}