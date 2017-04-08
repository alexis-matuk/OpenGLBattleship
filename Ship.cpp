#include "Ship.hpp"

Ship::Ship():Object(), startPos(2,0), endPos(2,0)
{
	model = loadModel("Objects/Carrier/carrier.obj");
	life = 0;
}

Ship::Ship(const char * filename) : Object(filename), startPos(2,0), endPos(2,0)
{	
	life = 0;
	std::cout << "center: " << centerX << ", " << centerY << ", " << centerZ << std::endl;
}

Ship::Ship(const char * filename, float _centerX, float _centerY, float _centerZ) : Object(filename), startPos(2,0), endPos(2,0)
{	
	centerX = _centerX;
	centerY = _centerY;
	centerZ = _centerZ;
	life = 0;
	std::cout << "center: " << centerX << ", " << centerY << ", " << centerZ << std::endl;	
}

Ship::~Ship()
{

}
