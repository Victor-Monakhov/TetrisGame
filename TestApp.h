// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once
#include <string>
#include "BaseApp.h"
#include "Figure.h"

#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32

class TestApp : public BaseApp
{
private:
	Field _field;
	Figure _figure;
	int _iterationCounter;
public:
	TestApp();
	void showMenuScore();
	void showMenuLevel();
	void showMenuLines();
	void showMenuFigures();
	void showNextFigure(bool flag);
	void showField();
	void showFigure(bool flag);
	virtual void KeyPressed(int btnCode);
	virtual bool UpdateF();
};