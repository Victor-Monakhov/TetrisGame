#pragma once
#include<ctime>
#include"Field.h"

class Figure {
private:
	Field* _field;
	const int _quantity;
	const int _turnQuantity;
	int _turn;
	int _random;
	int _nextRandom;
	int _levelSpeed;
	int _speed;
	int****_figuresOptions;
	COORD* _currCoords;
	COORD* _pastCoords;
	COORD _currPos;
	//func
	bool checkLowerCollision();
	bool checkRotateCollision();
public:
	Figure(Field* field);
	//getters
	COORD getCurrPosition()const;
	int getLevelSpeed()const;
	int**getFigure()const;
	int**getNextFigure()const;
	COORD* getCurrCoords()const;
	COORD* getPastCoords()const;
	int getSpeed()const;
	//setters
	void setCurrPosition(int X, int Y);
	void setTurn(int turn);
	void setRandom(int random);
	void setCurrCoords(int index, COORD value);
	void setSpeed(int speed);
	//functions
	void coordMemory();
	void checkWalls(int leftWall, int rightWall);
	void rotate();
	void goToNextFigure();
	bool checkSideCollision(bool flag);
	~Figure();
};
