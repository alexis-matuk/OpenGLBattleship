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

class Map{	
	GLMmodel* A = nullptr;
	GLMmodel* B = nullptr;
	GLMmodel* C = nullptr;
	GLMmodel* D = nullptr;
	GLMmodel* E = nullptr;
	GLMmodel* F = nullptr;
	GLMmodel* G = nullptr;
	GLMmodel* H = nullptr;
	GLMmodel* I = nullptr;
	GLMmodel* J = nullptr;
	GLMmodel* K = nullptr;
	GLMmodel* N1 = nullptr;
	GLMmodel* N2 = nullptr;
	GLMmodel* N3 = nullptr;
	GLMmodel* N4 = nullptr;
	GLMmodel* N5 = nullptr;
	GLMmodel* N6 = nullptr;
	GLMmodel* N7 = nullptr;
	GLMmodel* N8 = nullptr;
	GLMmodel* N9 = nullptr;
	GLMmodel* N10 = nullptr;
	GLMmodel* N11 = nullptr;
	int X = 11;
	int Y = 11;
	std::vector<std::vector<Tile>> grid;
	Ship ship_2;
	Ship ship_3;
	Ship ship_3_2;
	Ship ship_4;
	Ship ship_5;
	std::vector<Ship> ships;
	void loadObjects();	
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
