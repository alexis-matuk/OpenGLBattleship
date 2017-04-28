#include "aggregateFuncs.hpp"
#include "Map.hpp"
#include "Ship.hpp"
#include "KeyboardHandler.hpp"
#include "UIHandler.hpp"
#include "SceneManager.hpp"
#include "Missile.hpp"
#include "UIClient.hpp"

void * clientThread(void* params)
{
    client->mainLoop();
}

void updateMatrices()
{
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
}


/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
     glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float float_x, float_y;                     // loop counters.
    LoadGLTextures();				// Load The Texture(s) 
    glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Clear The Background Color To Blue 
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.2f,1000.0f);	// Calculate The Aspect Ratio Of The Window
    glMatrixMode(GL_MODELVIEW);        
}

/*Función principal*/
int main(int argc, char **argv)
{	
    glutInit(&argc, argv);       
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
    glutInitWindowSize(1100, 768);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("Battleship");    
    // glutFullScreen();       
    glutReshapeFunc(&Reshape);
    InitGL(1100, 768);    
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 1);           
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);  
	glEnable(GL_LIGHTING);    
	glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    shipModel = loadModel("Objects/tile.obj");
    whitePinModel = loadModel("Objects/pin_white.obj");
    redPinModel = loadModel("Objects/pin_red.obj");
    missileModel = loadModel("Objects/missile.obj");

    Scene = new SceneManager();
    Scene->addCallback("Menu", menuScene);
    Scene->addCallback("PickShips", pickingScene);
    Scene->addCallback("InGame", inGameScene);
    Scene->addCallback("Credits", creditsScene);
    Scene->addCallback("FindGame", findingGameScene);

    UI = new UIHandler();
    UI->createButton(900, 720, 200, 50, "Accept", toIngameFunc, "acceptShips", GLUT_BITMAP_HELVETICA_18);
    UI->createButton(350, 334, 200, 50, "Start", toFindGameFunc, "start", GLUT_BITMAP_HELVETICA_18);
    UI->createButton(350, 334, 200, 50, "Credits", toCreditsFunc, "credits", GLUT_BITMAP_HELVETICA_18);
    UI->createButton(350, 334, 200, 50, "Main Menu", toMenuFunc, "menu", GLUT_BITMAP_HELVETICA_18);

    UI->createPanel(0, 0, 600, "Title", "BATTLESHIP", 60, 255, 255, 255, FTGL::ALIGN_LEFT);     
    UI->createPanel(0, 0, 600, "credits", "Alexis Matuk - A01021143\nDiego Vázquez - A01168095\nGerardo Teruel - A01018057", 40, 255, 255, 255, FTGL::ALIGN_LEFT);       
    UI->createPanel(0, 0, 600, "findingGame", "Finding Game...", 40, 255, 255, 255, FTGL::ALIGN_LEFT);       

    UI->createPopup(0, 0, 400, "warning", "Place every ship before continuing", 30, 255, 255, 255, FTGL::ALIGN_CENTER);

    menuShip = new Ship("Objects/Gunboat/Gunboat.obj", 0,0.25,0);
    menuShip->setParams(1,1,1, -0.1,0.9,0.24, 0,90,0);
    map = new Map(false);  
    opponentMap = new Map(true);   

    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    client = new UIClient(PORT, "localhost", &hints, map, opponentMap);  
    if(!client->isValid())
    {
        std::cerr << "Couldn't create client" << std::endl;
        exit(-1);
    }
    
    pthread_t thread;
    int r = pthread_create(&thread, NULL, &clientThread, NULL);
    if(r != 0)
    {
        std::cerr << "Couldn't create client" << std::endl;
        exit(-1);
    }

    menuScene();
    
    glutMainLoop();    
    return 0;        
}


/* Función de Reshape */
void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    ww = w;
    wh = h;
    _top = 1.0;
    _bottom = -1.0;
    _left = -(double) w / (double) h;
    _right = -_left;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    // gluPerspective(fovy, (double) w / (double) h, _zNear, _zFar);
    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);

    UI->setButtonPositionByName("acceptShips", ww-200, wh-50); 
    UI->setButtonPositionByName("start", (int) (ww/2) - 100, (int)(wh/2));   
    UI->setButtonPositionByName("credits", (int) (ww/2) - 100, (int)3*wh/4);
    UI->setButtonPositionByName("menu", (int) (ww/2) - 100, (int)(wh/2));   

    
    UI->findPanelByName("Title")->center(ww, wh, 6.2*(float)wh/7);

    UI->findPopupByName("warning")->center(ww, wh, 4*(float)wh/5);

    UI->findPanelByName("credits")->setWidth(ww);
    UI->findPanelByName("credits")->center(ww, wh, 3*(float)wh/4);  

    UI->findPanelByName("findingGame")->setWidth(ww);
    UI->findPanelByName("findingGame")->center(ww, wh, (float)wh/2);    

}


#include "Mousehandler.hpp"
#include "DisplayFunctions.hpp"