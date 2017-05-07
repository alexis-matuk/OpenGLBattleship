#ifndef Ship_H
#define Ship_H

#include "HeaderInclude.hpp"

#include "Object.hpp"
#include "Map.hpp"

class Ship : public Object{	
	char shipId;
	int life;
	std::vector<int> startPos;
	std::vector<int> endPos;
	Map::Direction dir = Map::Direction::TOP_BOTTOM;	
	bool placed = false;
	bool isDrawing = true;
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
	char getShipId();
	void setShipId(char _id);
	void setDrawing(bool _isDrawing);
	bool getDrawing();
	~Ship();
};

#endif
