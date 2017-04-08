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

class Ship : public Object{	
	int life;
	std::vector<int> startPos;
	std::vector<int> endPos;	
public:	
	Ship();
	Ship(const char * filename);
	Ship(const char * filename, float _centerX, float _centerY, float _centerZ);
	~Ship();
};

#endif
