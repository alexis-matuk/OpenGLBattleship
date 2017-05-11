/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#ifndef AGGREGATEFUNCS_H
#define AGGREGATEFUNCS_H

#include "HeaderInclude.hpp"
/*
Forward declarations for classes
*/
class Map;
class Ship;
class Object;
class Tile;
class UIHandler;
class SceneManager;
class Missile;
class UIClient;

/*
	Global variable declaration
	GLUT can't handle local variables or parameters when chaning scenes, so everything must be managed via
		global variables.
*/
extern int frame;//frame for fps counter
extern int currenttime;//current time for fps counter
extern int timebase;//timebase for fps counter
extern bool rotatingXUp;//bool for rotation
extern bool rotatingXDown;//bool for rotation
extern bool rotatingYLeft;//bool for rotation
extern bool rotatingYRight;//bool for rotation
extern bool rotatingZLeft;//bool for rotation
extern bool rotatingZRight;//bool for rotation
extern bool zoomingIn;//bool for camera zoom
extern bool zoomingOut;//bool for camera zoom
extern float xSpeed;//rotation speed on X axis
extern float ySpeed;//rotation speed on Y axis
extern float zSpeed;//rotation speed on Z axis
extern float camSpeed;//zooming speed

/*Variables for modelview projection*/
extern double _left;
extern double _right;
extern double _bottom;
extern double _top;
extern double _zNear;
extern double _zFar;
extern double fovy;
extern double prev_z;
extern int ww, wh;

/*Variables for map rotation*/
extern float xRot;
extern float yRot;
extern float zRot;
extern float camZ;

/*Variables for opponent map rotation*/
extern float xRot_opponent;
extern float yRot_opponent;
extern float zRot_opponent;
extern float camZ_opponent;

extern int wireframe;//Varialble for wireframe

/*Declaration of my map and opponent map*/
extern Map * map;
extern Map * opponentMap;

/*Variables for OpenGL environment*/
extern GLfloat light_ambient[4];
extern GLfloat light_diffuse[4];
extern GLfloat light_specular[4];
extern GLfloat light_position[4];
extern GLfloat mat_ambient[4];
extern GLfloat mat_diffuse[4];
extern GLfloat mat_specular[4];
extern GLfloat high_shininess[1];

extern int window;
extern float lastx;//mouse variable
extern float lasty;//mouse variable

/*Variables for the current matrices*/
extern GLint viewport[4];
extern GLdouble modelview[16];
extern GLdouble projection[16];

/*Variables for debugging*/
extern float nx;
extern float ny;
extern float nz;
extern float fx;
extern float fy;
extern float fz;

extern bool valid;//Variable for ship mouse picking

extern UIHandler* UI;//Global UI handler
extern SceneManager * Scene;//Gobal scene manager
extern Ship * menuShip;//Rotating menu ship
extern GLMmodel * tileModel;//Resue tile model
extern GLMmodel * whitePinModel;//Reuse white pin model
extern GLMmodel * redPinModel;//Reuse red pin model
extern GLMmodel * missileModel;//Missile model
extern Missile * missile;//Global missile for shooting and getting shot
extern UIClient * client;//Global client

extern GLuint texture[1];//Variable for water texture
extern bool debug;//Variable for build with debug or no debug
extern char const* fontFile;//Variable for font file

extern float menuShipRot;//rotation of the menu ship

extern int animationCounter;//Variable for the "Finding Game..." animation
extern int sceneStartTime;//Variable for the timer starting a scene

extern GLuint textureMode;//draw models with texture
extern GLuint noTextureMode;//draw models with no texture

extern bool shooting;//Variable for shooting animation

extern bool waitingForServer;//check if waiting for server to start
extern bool attacking;//check if you attack first
extern bool defending;//check if you defend first
extern bool hasOrder;//check if server decided order

extern char * globalHostname;//Hostname given at launch

/*
	Function that renders a model given a mode
*/
void DrawModel(GLMmodel* model, GLuint _mode);

/*
	Function that loads a model for rendering
*/
GLMmodel* loadModel(const char* filename);

/*
	Declaration of global functions
	Comments can be found in implementation of each one
*/
void LoadGLTextures();
void enableParams();
void disableParams();
void drawRaycast();
void disableUIParams();
void enableUIParams();
void setPanelViewPort();
void setButtonViewPort();
void setWorldViewPort();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void Display();
void SpecialInput(int key, int x, int y);
void SpecialInputUp(int key, int x, int y);
void mouseHandlerPickingScene(int button, int state, int x, int y);
void updateMatrices();
void shipMotion(int x, int y);
void MouseMotion(int x, int y);
void Draw();
void MenuDisplay();
void endingDisplay();
void menuScene();
void inGameScene();
void toEndingFunc();
void toMenuFromEndingFunc();
void toIngameFunc();
void toGameFunc();
void toCreditsFunc();
void toFindGameFunc();
void toMenuFunc();
void pickingScene();
void creditsScene();
void findingGameScene();
void endingScene();
void mouseMotionMenu(int x, int y);
void mouseButtonMenu(int button, int state, int x, int y);
void KeyboardMenu(unsigned char key, int x, int y);
void modifyCameraInGame();
void modifyCamera();
void idle();
void menuIdle();
void inGameIdle();
void myMapBeingHitScene();
glm::vec3 screenToWorldPoint(float winX, float winY);

#endif