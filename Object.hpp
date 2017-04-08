#ifndef Object_H
#define Object_H

#ifdef __APPLE__
    #include <GLUT/glut.h>
#elif _WIN32
    #include <GL\glut.h>
#elif __linux__
    #include <GL/glut.h>
#endif
#include "aggregateFuncs.hpp"

class Object{	
protected:
	float scaleX;
	float scaleY;
	float scaleZ;
	float transX;
	float transY;
	float transZ;
	float angle;
	float rotX;
	float rotY;
	float rotZ;
	float centerX;
	float centerY;
	float centerZ;
	GLMmodel * model;	
public:	
	virtual void Draw();
	Object();
	Object(const char * filename);
	Object(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _angle, float _rotX, float _rotY, float _rotZ, const char * filename);	
	Object(float _centerX, float _centerY, float _centerZ, float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _angle, float _rotX, float _rotY, float _rotZ, const char * filename);	
	void setParams(float _centerX, float _centerY, float _centerZ, float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _angle, float _rotX, float _rotY, float _rotZ);
	void setParams(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _angle, float _rotX, float _rotY, float _rotZ);
	void DrawAxis(float scale);
	void setTranslation(float x, float y, float z);
	void setScale(float x, float y, float z);
	void setRotation(float _angle, float x, float y, float z);
	GLMmodel * getModel();
	void drawModel();
};

#endif
