#include "Ship.hpp"

Ship::Ship():Object(), startPos(2,0), endPos(2,0)
{
	model = loadModel("Objects/Carrier/carrier.obj");
	life = 0;
	type = "Ship";
	initBoundingBox();
	updateBoundingBoxToTransforms();
}

Ship::Ship(const char * filename) : Object(filename), startPos(2,0), endPos(2,0)
{		
	life = 0;	
	type = "Ship";
	std::cout << "center: " << centerX << ", " << centerY << ", " << centerZ << std::endl;
}

Ship::Ship(const char * filename, float _centerX, float _centerY, float _centerZ) : Object(filename), startPos(2,0), endPos(2,0)
{	
	centerX = _centerX;
	centerY = _centerY;
	centerZ = _centerZ;
	life = 0;
	type = "Ship";
	std::cout << "center: " << centerX << ", " << centerY << ", " << centerZ << std::endl;	
}

void Ship::setTopAnchor(glm::vec3 _topAnchor)
{
	topAnchor = _topAnchor;
}

void Ship::setLeftAnchor(glm::vec3 _leftAnchor)
{
	leftAnchor = _leftAnchor;
}

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

Ship::~Ship()
{

}
