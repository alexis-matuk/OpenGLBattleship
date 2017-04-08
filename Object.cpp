#include "Object.hpp"

void Object::Draw()
{
	glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			DrawModel(model, centerX, centerY, centerZ, scaleX, scaleY, scaleZ, transX, transY, transZ, angle, rotX, rotY, rotZ);			
		glPopAttrib();
	glPopMatrix();
}

Object::Object(const char * filename):Object()
{
	model = loadModel(filename);
}

Object::Object(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _angle, float _rotX, float _rotY, float _rotZ, const char * filename) : scaleX(_scaleX), scaleY(_scaleY), scaleZ(_scaleZ), transX(_x), transY(_y), transZ(_z), angle(_angle), rotX(_rotX), rotY(_rotY), rotZ(_rotZ)
{
	model = loadModel(filename);
}

Object::Object(float _centerX, float _centerY, float _centerZ, float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _angle, float _rotX, float _rotY, float _rotZ, const char * filename) : scaleX(_scaleX), scaleY(_scaleY), scaleZ(_scaleZ), transX(_x), transY(_y), transZ(_z), angle(_angle), rotX(_rotX), rotY(_rotY), rotZ(_rotZ), centerX(_centerX), centerY(_centerY), centerZ(_centerZ)
{
	model = loadModel(filename);
}


void Object::setParams(float _centerX, float _centerY, float _centerZ, float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _angle, float _rotX, float _rotY, float _rotZ)
{
	scaleX = _scaleX;
	scaleY = _scaleY;
	scaleZ = _scaleZ;
	transX = _x;
	transY = _y;
	transZ = _z;
	angle = _angle;
	rotX = _rotX;
	rotY = _rotY;
	rotZ = _rotZ;
	centerX = _centerX;
	centerY = _centerY;
	centerZ = _centerZ;
}

void Object::setParams(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _angle, float _rotX, float _rotY, float _rotZ)
{
	scaleX = _scaleX;
	scaleY = _scaleY;
	scaleZ = _scaleZ;
	transX = _x;
	transY = _y;
	transZ = _z;
	angle = _angle;
	rotX = _rotX;
	rotY = _rotY;
	rotZ = _rotZ;
}

Object::Object()
{
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	transX = 0;
	transY = 0;
	transZ = 0;
	angle = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	centerX = 0;
	centerY = 0;
	centerZ = 0;
}

void Object::setTranslation(float x, float y, float z)
{
	transX = x;
	transY = y;
	transZ = z;
}

void Object::setScale(float x, float y, float z)
{
	scaleX = x;
	scaleY = y;
	scaleZ = z;
}

void Object::setRotation(float _angle, float x, float y, float z)
{
	angle = _angle;
	rotX = x;
	rotY = y;
	rotZ = z;
}

void Object::DrawAxis(float scale)
{
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glScalef(scale, scale, scale);

    glBegin(GL_LINES);    
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(.8f, 0.05f, 0.0);
    glVertex3f(1.0, 0.25f, 0.0);	/*  Letter X */
    glVertex3f(0.8f, .25f, 0.0);
    glVertex3f(1.0, 0.05f, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);	/*  X axis */

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);	/*  Y axis */

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);	/*  Z axis */
    glEnd();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();
}