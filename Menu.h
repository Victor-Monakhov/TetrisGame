#pragma once

class Menu {
private:
	int _level;
	int _lines;
	int _figures;
	int _score;
public:
	Menu() :
		_level{1},
		_lines{},
		_figures{},
		_score{}
	{}
	int getLevel()const {
		return _level;
	}
	int getLines()const {
		return _lines;
	}
	int getFigures()const {
		return _figures;
	}
	int getScore()const {
		return _score;
	}
	void setLevel( int level) {
		_level = level;
	}
	void setLines( int lines) {
		_lines = lines;
	}
	void setFigures(int figures) {
		_figures = figures;
	}
	void setScore( int score) {
		_score = score;
	}
};

