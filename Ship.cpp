/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#include "Ship.hpp"

/*
  Initialize the ship object with a default boat model
*/
Ship::Ship():Object(), startPos(2,-1), endPos(2,-1)
{
	model = loadModel("Objects/Carrier/carrier.obj");
	life = 0;
	type = "Ship";
	initBoundingBox();
	updateBoundingBoxToTransforms();
}

/*
  Initialize ship given a .obj file path
*/
Ship::Ship(const char * filename) : Object(filename), startPos(2,-1), endPos(2,-1)
{		
	life = 0;	
	type = "Ship";
	std::cout << "center: " << centerX << ", " << centerY << ", " << centerZ << std::endl;
}

/*
  Initialize ship given a file path and a center offset
*/
Ship::Ship(const char * filename, float _centerX, float _centerY, float _centerZ) : Object(filename), startPos(2,0), endPos(2,0)
{	
	centerX = _centerX;
	centerY = _centerY;
	centerZ = _centerZ;
	life = 0;
	type = "Ship";	
}

/*
  Set ship's top anchor
*/
void Ship::setTopAnchor(glm::vec3 _topAnchor)
{
	topAnchor = _topAnchor;
}

/*
  Set ship's left anchor
*/
void Ship::setLeftAnchor(glm::vec3 _leftAnchor)
{
	leftAnchor = _leftAnchor;
}

/*
  Implement the update of reference points.
  Change the centroid's position to be on the bottom, but update top and left anchor separately of the bounding box vertices
*/
void Ship::updateReferencePoints()
{
	centroid = glm::vec3((vertexArray[2][0]+vertexArray[4][0])/2, (vertexArray[2][1]+vertexArray[4][1])/2, (vertexArray[2][2]+vertexArray[4][2])/2);

	glm::vec4 vec_left(leftAnchor.x, leftAnchor.y, leftAnchor.z, 1.0f);
	vec_left = transformationMatrix * vec_left;
	leftAnchor.x = vec_left.x;
	leftAnchor.y = vec_left.y;
	leftAnchor.z = vec_left.z;

	glm::vec4 vec(topAnchor.x, topAnchor.y, topAnchor.z, 1.0f);
	vec = transformationMatrix * vec;
	topAnchor.x = vec.x;
	topAnchor.y = vec.y;
	topAnchor.z = vec.z;
}

/*
  Set ship's life
*/
void Ship::setLife(int _life)
{
	life = _life;
}

/*
  Get ship's life
*/
int Ship::getLife()
{
	return life;
}

/*
  Hit ship
*/
void Ship::hitShip()
{
	life--;
}

/*
  Set starting position
*/
void Ship::setStartPos(std::vector<int> _startPos)
{
	startPos = _startPos;
}

/*
  Set ending position
*/
void Ship::setEndPos(std::vector<int> _endPos)
{
	endPos = _endPos;
}

/*
  Get starting position
*/
std::vector<int> Ship::getStartPos()
{
	return startPos;
}

/*
  Get ending position
*/
std::vector<int> Ship::getEndPos()
{
	return endPos;
}

/*
  Get direction
*/
Map::Direction Ship::getDirection()
{
	return dir;
}

/*
  Set direction
*/
void Ship::setDirection(Map::Direction _dir)
{
	dir = _dir;
}

/*
  Check if the ship is placed in map
*/
bool Ship::isPlaced()
{
	return placed;
}

/*
  Set the ship placed
*/
void Ship::setPlaced(bool _placed)
{
	placed = _placed;
}

/*
  Get ship id
*/
char Ship::getShipId()
{
	return shipId;
}

/*
  Set ship id
*/
void Ship::setShipId(char _id)
{
	shipId = _id;
}

/*
  Set drawing mode of the ship
*/
void Ship::setDrawing(bool _isDrawing)
{
	isDrawing = _isDrawing;
}

/*
  Get drawing mode of the ship
*/
bool Ship::getDrawing()
{
	return isDrawing;
}

Ship::~Ship()
{

}
