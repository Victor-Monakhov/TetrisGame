// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"

TestApp::TestApp() : 
	BaseApp(27, 29),
	_field{Field(X_SIZE,Y_SIZE)},
	_figure(Figure(&_field)),
	_iterationCounter{}
{}

void TestApp::KeyPressed(int btnCode)
{
	//controls				
	switch (btnCode) {
	case KEY_LEFT: {
		if(!_figure.checkSideCollision(false))
		_figure.setCurrPosition(_figure.getCurrPosition().X - 1, _figure.getCurrPosition().Y);
		break;
	}
	case KEY_RIGHT: {
		if (!_figure.checkSideCollision(true))
		_figure.setCurrPosition(_figure.getCurrPosition().X + 1, _figure.getCurrPosition().Y);
		break;
	}
	case KEY_DOWN: {
		_figure.setSpeed(30);
		_iterationCounter = 0;
		break;
	}
	case KEY_SPACE: {
		_figure.rotate();
		break;
	}
	}
	_figure.checkWalls(1, _field.getGameFieldWidth() - 2);				
}

void TestApp::showField() {
	for (int i{}; i < Y_SIZE; ++i) {
		for (int j{}; j < X_SIZE; ++j) {
			if (_field.getWindow()[i][j] == 0) SetChar(j, i, L' ', _color._black);
			if (_field.getWindow()[i][j] == 1) SetChar(j, i, (wchar_t)30, _color._blue);
			if (_field.getWindow()[i][j] == 3) SetChar(j, i, L'.', _color._green);
			if (_field.getWindow()[i][j] == 2) SetChar(j, i, (wchar_t)10, _color._white);
		}
	}
}
void TestApp::showMenuScore() {
	wstring wstr = L"Score " + to_wstring(_field.getMenuPointer()->getScore());
	for (int i{ 2 }; i < wstr.length() + 2; ++i) {
		if (i <= 6) SetChar(i, X_SIZE - 1, wstr[i - 2], _color._white);
		if (i > 6) SetChar(i, X_SIZE - 1, wstr[i - 2], _color._green);
	}
}
void TestApp::showMenuLevel() {
	wstring wstr1 = L"Level";
	wstring wstr2 = to_wstring(_field.getMenuPointer()->getLevel());
	for (int i{ Y_SIZE - 10 }; i < wstr1.length() + Y_SIZE - 10; ++i) {
		SetChar(i, 9, wstr1[i - Y_SIZE + 10], _color._white);
	}
	for (int i{ Y_SIZE - 8 }; i < wstr2.length() + Y_SIZE - 8; ++i) {
		SetChar(i, 11, wstr2[i - Y_SIZE + 8], _color._green);
	}
}
void TestApp::showMenuLines() {
	wstring wstr1 = L"Lines";
	wstring wstr2 = to_wstring(_field.getMenuPointer()->getLines());
	for (int i{ Y_SIZE - 10 }; i < wstr1.length() + Y_SIZE - 10; ++i) {
		SetChar(i, 13, wstr1[i - Y_SIZE + 10], _color._white);
	}
	for (int i{ Y_SIZE - 8 }; i < wstr2.length() + Y_SIZE - 8; ++i) {
		SetChar(i, 15, wstr2[i - Y_SIZE + 8], _color._green);
	}
}
void TestApp::showMenuFigures() {
	wstring wstr1 = L"Figures";
	wstring wstr2 = to_wstring(_field.getMenuPointer()->getFigures());
	for (int i{ Y_SIZE - 11 }; i < wstr1.length() + Y_SIZE - 11; ++i) {
		SetChar(i, 17, wstr1[i - Y_SIZE + 11], _color._white);
	}
	for (int i{ Y_SIZE - 8 }; i < wstr2.length() + Y_SIZE - 8; ++i) {
		SetChar(i, 19, wstr2[i - Y_SIZE + 8], _color._green);
	}
}
void TestApp::showFigure(bool flag) {
	if (flag) {
		_figure.setCurrCoords(0, _figure.getCurrPosition());
	}
	for (int i{}; i < 4; ++i) {
		if (flag) {
			short tempX = _figure.getCurrCoords()[i].X + (short)_figure.getFigure()[i][0];
			short tempY = _figure.getCurrCoords()[i].Y + (short)_figure.getFigure()[i][1];
			_figure.setCurrCoords(i + 1, { tempX, tempY });
			setCursorPosition(_figure.getCurrCoords()[i + 1]);
			SetChar(_figure.getCurrCoords()[i + 1].X, _figure.getCurrCoords()[i + 1].Y, (wchar_t)10, _color._purple);
		}
		else SetChar(_figure.getPastCoords()[i + 1].X, _figure.getPastCoords()[i + 1].Y, L' ', _color._black);
	}
}
void TestApp::showNextFigure(bool flag) {
		COORD tempCoord[5] = { (short)Y_SIZE - 8, 3 };
	for (int i{}; i < 4; ++i) {
		tempCoord[i+1].X = tempCoord[i].X + (short)_figure.getNextFigure()[i][0];
		tempCoord[i+1].Y = tempCoord[i].Y + (short)_figure.getNextFigure()[i][1];	
		setCursorPosition(tempCoord[i + 1]);
		if (flag) SetChar(tempCoord[i + 1].X, tempCoord[i + 1].Y, (wchar_t)10, _color._purple);
		else SetChar(tempCoord[i + 1].X, tempCoord[i + 1].Y, L' ', _color._black);
	}
}

bool TestApp::UpdateF()
{
	showField();
	showFigure(false);
	showFigure(true);
	showNextFigure(false);
	showNextFigure(true);
	showMenuScore();
	showMenuLevel();
	showMenuLines();
	showMenuFigures();
	++_iterationCounter;
	_figure.coordMemory();
	if (_iterationCounter == 31 - _figure.getSpeed()) {
		_figure.setCurrPosition(_figure.getCurrPosition().X, _figure.getCurrPosition().Y + 1);
		_figure.goToNextFigure();
		_iterationCounter = 0;
	}
	for (int i{1}; i < _field.getGameFieldWidth(); ++i)
	if (_field.getWindow()[3][i] == back_id::_figure_id) return true;
	return false;
}
