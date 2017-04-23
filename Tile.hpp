#ifndef Tile_H
#define Tile_H

#include "HeaderInclude.hpp"
#include "Object.hpp"
class Tile : public Object{		
public:	
	enum class State{
		FREE, 
		USED,
		HIT,
		MARKED
	};
	Tile();
	Tile(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ);
	~Tile();
	void Draw();
	void updateState(State _newState);
	State getCurrentState();
	State getLastState();
	void initPoints();
	void drawWater();
	void makeRipple();
	void setGridPos(int _gridX, int _gridY);
	std::vector<int> getGridPos();
private:
	State currentState = State::FREE;
	State lastState = State::FREE;	
	int gridX;
	int gridY;
	int x;
	int y;
    float float_x;
    float float_y;
    float float_xb;
    float float_yb;
	float points[45][45][3];   // the array for the points on the grid of our "wave"
	int wiggle_count = 0;
};
#endif

#include "aggregateFuncs.hpp"