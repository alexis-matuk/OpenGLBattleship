#include "aggregateFuncs.hpp"
#include "Map.hpp"
#include "Ship.hpp"
#include "KeyboardHandler.hpp"
#include "UIHandler.hpp"
#include "SceneManager.hpp"

/* Funciones de GLUT */
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
void menuScene();
void toMenuFunc();
void toGameFunc();
void pikcingScene();

void mouseMotionMenu(int x, int y);
void mouseButtonMenu(int button, int state, int x, int y);
void KeyboardMenu(unsigned char key, int x, int y);

void updateMatrices()
{
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
}

void modifyCamera()
{
    if(rotatingXUp)
    {
        xRot -= xSpeed * (currenttime - timebase);
    }
    if(rotatingXDown)
    {
        xRot += xSpeed * (currenttime - timebase);            
    }
    if(rotatingYLeft)
    {
        yRot -= ySpeed * (currenttime - timebase);
    }
    if(rotatingYRight)
    {
        yRot += ySpeed * (currenttime - timebase);            
    }
    if(rotatingZLeft)
    {
        zRot -= zSpeed * (currenttime - timebase);
    }
    if(rotatingZRight)
    {
        zRot += zSpeed * (currenttime - timebase);            
    }
    if(zoomingIn)
    {
        if(camZ >= MIN_CAM_Z)
            camZ -= camSpeed * (currenttime - timebase);            
    }
    if(zoomingOut)
    {
        if(camZ <= MAX_CAM_Z)
            camZ += camSpeed * (currenttime - timebase);            
    }    
}

void idle()
{
   frame++;
   currenttime = glutGet(GLUT_ELAPSED_TIME);
   if (currenttime - timebase > 0.5) 
   {
        modifyCamera();
        timebase = currenttime;    
        frame = 0;        
        glutPostRedisplay();        
   }  
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
    glutDisplayFunc(MenuDisplay);

    glutKeyboardFunc(KeyboardMenu);
    glutMouseFunc(mouseButtonMenu);
    glutMotionFunc(mouseMotionMenu); 
    glutPassiveMotionFunc(MousePassiveMotion);

    glutFullScreen();       
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
    Scene = new SceneManager();
    Scene->addCallback("Menu", menuScene);
    Scene->addCallback("PickShips", pikcingScene);
    UI = new UIHandler();
    UI->createButton(900, 720, 200, 50, "Accept", toMenuFunc, "start", GLUT_BITMAP_HELVETICA_18);
    UI->createButton(350, 334, 200, 50, "Start", toGameFunc, "toGame", GLUT_BITMAP_HELVETICA_18);
    UI->createPanel(20, 20, 600, "Title", "BATTLESHIP", 60, 255, 255, 255, FTGL::ALIGN_LEFT);     
    UI->createPopup(20, 20, 400, "warning", "Place every ship before continuing", 30, 255, 255, 255, FTGL::ALIGN_CENTER);     
    map = new Map();    
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
    UI->setButtonPositionByName("start", ww-200, wh-50); 
    UI->setButtonPositionByName("toGame", (int) (ww/2)-100, (int)(wh/2)-25);   

    Panel * p = UI->findPanelByName("Title"); 
    p->setww(ww);
    p->setwh(wh);
    FTBBox bbox = p->getLayout()->BBox(p->getContent().c_str());       
    p->addPositionFromCenter((float)ww/2-bbox.Upper().Xf()/2, 4*(float)wh/5);

    Popup * pop = UI->findPopupByName("warning"); 
    pop->setww(ww);
    pop->setwh(wh);
    FTBBox bbox1 = pop->getLayout()->BBox(pop->getContent().c_str());       
    pop->addPositionFromCenter((float)ww/2-bbox1.Upper().X()/2, 4*(float)wh/5);

}


#include "Mousehandler.hpp"
#include "DisplayFunctions.hpp"