#ifndef Missile_H
#define Missile_H

#include "HeaderInclude.hpp"
#include "Object.hpp"
class Tile;
class Missile : public Object{		
public:
	~Missile();
	Missile(Tile * _targetTile);	
	bool DrawMissile(GLuint _mode);
	glm::vec3 tileCentroid;
	float zPos;
private:	
	int startTime;
	int timeBase = 0;
	float missileSpeed = 0.008f;
	Tile * tile = nullptr;
};
#endif

#include "Tile.hpp";
#include "aggregateFuncs.hpp"