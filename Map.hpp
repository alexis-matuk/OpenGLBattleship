#ifndef Map_H
#define Map_H

#include "HeaderInclude.hpp"

#include "Tile.hpp"
#include "Object.hpp"

class Ship;

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
	float mapStartX = -3;
	float mapStartY = 1.8;
	std::vector<std::vector<Tile*>> grid;
	Ship * ship_2;
	Ship * ship_3;
	Ship * ship_3_2;
	Ship * ship_4;
	Ship * ship_5;
	std::vector<Ship*> ships;	
	Ship * currentShipSelected = nullptr;	
	float tileSideLength;
	std::vector<std::string> letterArray = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K"};
public:
	enum class Direction{
		TOP_BOTTOM,
		LEFT_RIGHT
	};
	Map();
	~Map();
	void initLetters();
	void initNumbers();
	void initTiles();
	void initShips();
	void drawNumbers();
	void drawLetters();
	void drawTiles();	
	void drawInitialShips();
	void Draw();	
	void drawShips();
	void setCurrentShipSelected(Ship * _ship);
	Tile * getClosestTile(Ship * _ship, Direction _dir);
	void clipShipToTile(Direction _dir, Ship * _ship, Tile * _tile);
	void updateTileInGrid(Tile * _tile, int ship_life, Direction _dir, Tile::State _state);
	void updateShipPositions(Tile * _tile, Ship * _ship, Direction _dir);
	bool tilesUsed(Tile * _tile, Ship * _ship, Direction _dir);
	void unclipShipFromGrid(Ship * _ship);
	Ship * getCurrentShipSelected();
	void clipAndUpdateShip(Ship * current_ship);
	Tile * getTile(int letter, int number);	
	Ship * getShip(int pos);
	Tile * getTileHit(glm::vec3 near, glm::vec3 far);	
	Ship * getShipHit(glm::vec3 near, glm::vec3 far, float & distance);	
	bool everyShipPlaced();
	static void ApplyColor(
   	GLfloat ambr, GLfloat ambg, GLfloat ambb,
   	GLfloat difr, GLfloat difg, GLfloat difb,
   	GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine);   	
};

bool hitSortFunc (std::pair<Object, float> i,std::pair<Object, float> j);
#endif

#include "Ship.hpp"
#include "aggregateFuncs.hpp"