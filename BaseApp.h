// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include <iostream>
#include <algorithm>
#include <time.h>
#include <conio.h>
#include <assert.h>
#include <strsafe.h>
#include<windows.h>

using namespace std;

struct Color {
private:
	friend class BaseApp;
	friend class TestApp;
	WORD _purple = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	WORD _blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	WORD _green = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	WORD _white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	WORD _black = NULL;
};

class BaseApp
{
private:
	HANDLE mConsole;
	HANDLE mConsoleIn;

	CHAR_INFO* mChiBuffer;
	COORD mDwBufferSize;
	COORD mDwBufferCoord;
	SMALL_RECT mLpWriteRegion;

	void Render();
protected:
	//������� ������� ������ �� ����������� � ��������� � ��������
	const int X_SIZE;
	const int Y_SIZE;
	Color _color;
public:
	//����������� �������� ������� ������� ������ �� ����������� � ��������� � ��������
	BaseApp(int xSize=100, int ySize=80);
	virtual ~BaseApp();

	//��������� ������� ����
	void Run();
	void setCursorPosition(COORD coord)
	{
		SetConsoleCursorPosition(mConsole, coord);
	}
	//����� ��������� x,y-������ ������ ������������ ��������, ��� ������� ���
	void SetChar(int x, int y, wchar_t c, WORD color);
	wchar_t GetChar(int x, int y);

	/*��� ������� ���������� ������ ������� ��������, � ����� ��������������, � ���������� ������.
	� �� �������� deltaTime - ������� �� ������� ����� ���������� ��������� � ����, � ��������*/
	virtual bool UpdateF() { return false; }
	/*��� ������� ���������� ��� ������� ������� �� ����������, � �� �������� ��� ������� - btnCode.
	���� ������������ ������� ��� �������������� �������, �� ������ ����� ��� ��� �����, �������� 224, � ��������� �� ��� - 
	����� ��� ��������������� ��� ����� �������, ��� ����� ��������, ������ ����� getch().
	����� KeyPressed ��� �� ����� �������������� � ����������*/
	virtual void KeyPressed (int btnCode){}
};