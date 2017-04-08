#ifdef __APPLE__
    #include <GLUT/glut.h>
#elif _WIN32
    #include <GL\glut.h>
#elif __linux__
    #include <GL/glut.h>
#endif

#include "glm.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "SOIL.h"

extern GLuint viewMode;//Modo de visualización
extern GLuint texture[1];
void DrawModel(GLMmodel* model);
void DrawModel(GLMmodel* model, float centerX, float centerY, float centerZ, float scaleX, float scaleY, float scaleZ, float x, float y, float z, float angle, float rotX, float rotY, float rotZ);
GLMmodel* loadModel(const char* filename);
void LoadGLTextures();