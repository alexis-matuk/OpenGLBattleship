#ifdef __APPLE__
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#elif _WIN32
    #include <GL\glut.h>
#elif __linux__
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif	// Header File For The OpenGL32 Library

#include "glm/glm/glm.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <map>
#include <sstream>
#include <utility>
#include <algorithm>
#include "SOIL.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <FTGL/ftgl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <pthread.h>

#define START_Z 6.7
#define SPEED_MULT 0.5
#define FONT_FILE "Arial.ttf"
#define MIN_CAM_Z -5
#define MAX_CAM_Z 7

#define ACT_HIT "hit"
#define ACT_MISS "miss"
#define ACT_DESTROY "destroy"
#define ACT_SEND "send"
#define ACT "act"
#define ACT_SHOOT "shoot"
#define ACT_LOST "lost"
#define ACT_WIN "win"
#define BUFFER_SIZE 1024

#define ROWS 11
#define COLS 11

#define PORT "3912"
