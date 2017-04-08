#ifndef Tile_H
#define Tile_H

#ifdef __APPLE__
    #include <GLUT/glut.h>
#elif _WIN32
    #include <GL\glut.h>
#elif __linux__
    #include <GL/glut.h>
#endif
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
	Tile(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _angle, float _rotX, float _rotY, float _rotZ);
	~Tile();
	void Draw();
	void setCurrentState(State _state);
	void setLastState(State _state);
	void initPoints();
	void drawWater();
	void makeRipple();
private:
	State currentState = State::FREE;
	State lastState = State::FREE;	
	int x;
	int y;
    float float_x;
    float float_y;
    float float_xb;
    float float_yb;
	float points[45][45][3];   // the array for the points on the grid of our "wave"
	int wiggle_count = 0;
};
#include "aggregateFuncs.hpp"
#endif
