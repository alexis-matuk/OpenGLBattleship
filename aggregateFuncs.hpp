#include "HeaderInclude.hpp"
class Map;
class Ship;
class Object;
class Tile;
class UIHandler;
class SceneManager;
class Missile;
class UIClient;

extern int frame;
extern int currenttime;
extern int timebase;
extern bool rotatingXUp;
extern bool rotatingXDown;
extern bool rotatingYLeft;
extern bool rotatingYRight;
extern bool rotatingZLeft;
extern bool rotatingZRight;
extern bool zoomingIn;
extern bool zoomingOut;
extern float xSpeed;
extern float ySpeed;
extern float zSpeed;
extern float camSpeed;
extern double _left;
extern double _right;
extern double _bottom;
extern double _top;
extern double _zNear;
extern double _zFar;
extern double fovy;
extern double prev_z;
extern int ww, wh;
extern float xRot;
extern float yRot;
extern float zRot;
extern float camZ;

extern float xRot_opponent;
extern float yRot_opponent;
extern float zRot_opponent;
extern float camZ_opponent;

extern int wireframe;
extern Map * map;
extern Map * opponentMap;
extern GLfloat light_ambient[4];
extern GLfloat light_diffuse[4];
extern GLfloat light_specular[4];
extern GLfloat light_position[4];
extern GLfloat mat_ambient[4];
extern GLfloat mat_diffuse[4];
extern GLfloat mat_specular[4];
extern GLfloat high_shininess[1];
extern int window; 
extern bool down;
extern float lastx;
extern float lasty;
extern std::vector<std::vector<float>> points;
extern GLint viewport[4];
extern GLdouble modelview[16];
extern GLdouble projection[16];
extern float nx;
extern float ny;
extern float nz;
extern float fx;
extern float fy;
extern float fz;
extern bool valid;

extern UIHandler* UI;
extern SceneManager * Scene;

extern GLuint viewMode;//Modo de visualización
extern GLuint texture[1];
extern bool debug;

extern char const* fontFile; // Just a string with the path to the font file 
extern Ship * menuShip;   

extern float menuShipRot;

extern int animationCounter;
extern int sceneStartTime;

extern Object * object;

extern GLuint textureMode;
extern GLuint noTextureMode;

extern GLMmodel * shipModel;

extern GLMmodel * whitePinModel;
extern GLMmodel * redPinModel;

extern GLMmodel * missileModel;
extern Missile * missile;

extern bool shooting;

extern UIClient * client;

void DrawModel(GLMmodel* model, GLuint _mode);
void DrawModel(GLMmodel* model, float centerX, float centerY, float centerZ, float scaleX, float scaleY, float scaleZ, float x, float y, float z, float angle, float rotX, float rotY, float rotZ);
GLMmodel* loadModel(const char* filename);
void LoadGLTextures();
void enableParams();
void disableParams();
void drawRaycast();
void disableUIParams();
void enableUIParams();
void setPanelViewPort();
void setButtonViewPort();
void setWorldViewPort();

/*
========= FUNCTION DECLARATION FOR THE PROGRAM =========
*/
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void Display();
void SpecialInput(int key, int x, int y);
void SpecialInputUp(int key, int x, int y);
void LoadGLTextures();
void mouseHandlerPickingScene(int button, int state, int x, int y);
void updateMatrices();
void shipMotion(int x, int y);
void MousePassiveMotion(int x, int y);
void MouseMotion(int x, int y);
void MouseButton(int button,int state,int x, int y);
void Resize(int w, int h);
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