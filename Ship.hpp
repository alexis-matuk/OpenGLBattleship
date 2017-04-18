#ifndef Ship_H
#define Ship_H

#ifdef __APPLE__
    #include <GLUT/glut.h>
#elif _WIN32
    #include <GL\glut.h>
#elif __linux__
    #include <GL/glut.h>
#endif

#include "Object.hpp"
#include "Map.hpp"

class Ship : public Object{	
	int life;
	std::vector<int> startPos;
	std::vector<int> endPos;
	Map::Direction dir = Map::Direction::TOP_BOTTOM;	
	bool placed = false;
public:	
	Ship();
	Ship(const char * filename);
	Ship(const char * filename, float _centerX, float _centerY, float _centerZ);
	void setTopAnchor(glm::vec3 _topAnchor);
	void setLeftAnchor(glm::vec3 _leftAnchor);
	void updateReferencePoints();	
	void setLife(int _life);
	int getLife();
	void hitShip();	
	void setStartPos(std::vector<int> _startPos);
	void setEndPos(std::vector<int> _endPos);
	std::vector<int> getStartPos();
	std::vector<int> getEndPos();
	Map::Direction getDirection();
	void setDirection(Map::Direction _dir);
	bool isPlaced();
	void setPlaced(bool _placed);
	~Ship();
};

#endif
