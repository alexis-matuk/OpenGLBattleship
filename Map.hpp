#ifndef Map_H
#define Map_H

#ifdef __APPLE__
    #include <GLUT/glut.h>
#elif _WIN32
    #include <GL\glut.h>
#elif __linux__
    #include <GL/glut.h>
#endif
#include "aggregateFuncs.hpp"
#include "Ship.hpp"
#include "Tile.hpp"
#include "Object.hpp"

class Map{	
	Object A;
	Object B;
	Object C;
	Object D;
	Object E;
	Object F;
	Object G;
	Object H;
	Object I;
	Object J;
	Object K;
	Object N1;
	Object N2;
	Object N3;
	Object N4;
	Object N5;
	Object N6;
	Object N7;
	Object N8;
	Object N9;
	Object N10;
	Object N11;
	int X = 11;
	int Y = 11;
	std::vector<std::vector<Tile>> grid;
	Ship ship_2;
	Ship ship_3;
	Ship ship_3_2;
	Ship ship_4;
	Ship ship_5;
	std::vector<Ship> ships;	
public:
	Map();
	~Map();
	void drawNumbers();
	void drawLetters();
	void drawTiles();
	void initTiles();
	void drawInitialShips();
	void Draw();
	void initShips();
	void drawShips();
	Tile & getTile(int letter, int number);	
	Ship & getShip(int pos);
	static void ApplyColor(
   	GLfloat ambr, GLfloat ambg, GLfloat ambb,
   	GLfloat difr, GLfloat difg, GLfloat difb,
   	GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine);
};

#endif
