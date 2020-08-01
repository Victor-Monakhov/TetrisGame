#pragma once
#include<windows.h>
#include"Menu.h"

enum  back_id {
	_field_id,
	_wall_id,
	_figure_id,
	_star_id
};

class Field {
private:
	Menu _menu;
	int _windowWidth;
	int _windowHeight;
	int _gameFieldHeight;
	int _gameFieldWidth;
	int** _window;
public:
	Field(int windowWidth, int windowHeight);
	int** getWindow()const;
	int getGameFieldWidth()const;
	int getGameFieldHeight()const;
	Menu* getMenuPointer();
	void changeElement(int indexRow, int indexColumn, int value);
	void deleteLine();
	~Field();
};

