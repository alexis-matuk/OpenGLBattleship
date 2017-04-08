//
// This code was created by Jeff Molofee '99 (ported to Linux/GLUT by Richard Campbell '99)
//
// If you've found this code useful, please let me know.
//
// Visit Jeff Molofee at www.demonews.com/hosted/nehe 
// (email Richard Campbell at ulmont@bellsouth.net)
//
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

#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <unistd.h>     // needed to sleep.
#include <math.h>       // sin function.
#include "SOIL.h"
/* ascii code for the escape key */
#define ESCAPE 27

/* The number of our GLUT window */
int window; 

/* floats for x rotation, y rotation, z rotation */
float xrot, yrot, zrot;

float points[45][45][3];   // the array for the points on the grid of our "wave"

int wiggle_count = 0;

/* storage for one texture  */
int texture[1];

// Load Bitmaps And Convert To Textures
void LoadGLTextures() {	
 
    // Create Texture	
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    int width, height;
    unsigned char* image =SOIL_load_image("water.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
};

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
    float float_x, float_y;                     // loop counters.
    LoadGLTextures();				// Load The Texture(s) 
    glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);	// Clear The Background Color To Blue 
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window
    glMatrixMode(GL_MODELVIEW);
    for(float_x = 0.0f; float_x < 9.0f; float_x +=  0.2f )	{
    	for(float_y = 0.0f; float_y < 9.0f; float_y += 0.2f)		{
    	    points[ (int) (float_x*5) ][ (int) (float_y*5) ][0] = float_x - 4.4f;
    	    points[ (int) (float_x*5) ][ (int) (float_y*5) ][1] = float_y - 4.4f;
            // points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin(2*float_x)*cos(2*float_y))/2;
            points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin(sqrt(float_x*float_x + float_y*float_y)));
            // points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin( 10 * (float_x*float_x + float_y*float_y)/50))/5;
    	    // points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (sin( ( (float_x*5*8)/360 ) * 3.14159 * 2 ));               
    	}
    }
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
    if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
	Height=1;
    glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene()
{
    int x, y;
    float float_x, float_y, float_xb, float_yb;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
    glLoadIdentity();				// Reset The View
    glTranslatef(0.0f,0.0f,-12.0f);              // move 12 units into the screen.
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.
    glPolygonMode(GL_BACK, GL_FILL);
    glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_QUADS);
    for (x=0; x<44; x++) {
    	for (y=0; y<44; y++) {
    	    float_x  = (float) (x)/44;
    	    float_y  = (float) (y)/44;
    	    float_xb = (float) (x+1)/44;
    	    float_yb = (float) (y+1)/44;

    	    glTexCoord2f( float_x, float_y);
    	    glVertex3f( points[x][y][0], points[x][y][1], points[x][y][2] );
    			
    	    glTexCoord2f( float_x, float_yb );
    	    glVertex3f( points[x][y+1][0], points[x][y+1][1], points[x][y+1][2] );
    			
    	    glTexCoord2f( float_xb, float_yb );
    	    glVertex3f( points[x+1][y+1][0], points[x+1][y+1][1], points[x+1][y+1][2] );
    			
    	    glTexCoord2f( float_xb, float_y );
    	    glVertex3f( points[x+1][y][0], points[x+1][y][1], points[x+1][y][2] );
    	}
    }
    glEnd();

    if (wiggle_count == 2) { // cycle the sine values
	for (y = 0; y <45; y++) {
	    points[44][y][2] = points[0][y][2];
	}

	for( x = 0; x < 44; x++ ) {
	    for( y = 0; y < 45; y++) {
        points[x][y][2] = points[x+1][y][2];
	    }		
	}		
	wiggle_count = 0;
    }    
    wiggle_count++;

    xrot +=0.3f;
    yrot +=0.2f;
    zrot +=0.4f;
    // since this is double buffered, swap the buffers to display what just got drawn.
    glutSwapBuffers();
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
    /* avoid thrashing this procedure */
    usleep(100);

    /* If escape is pressed, kill everything. */
    if (key == ESCAPE) 
    { 
	/* shut down our window */
	glutDestroyWindow(window); 
      
      /* exit the program...normal termination. */
	exit(0);                   
    }
}

int main(int argc, char **argv) 
{  
    /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
       X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
    glutInit(&argc, argv);  

    /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Alpha components supported 
     Depth buffer */  
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

    /* get a 640 x 480 window */
    glutInitWindowSize(640, 480);  

    /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(0, 0);  

    /* Open a window */  
    window = glutCreateWindow("Jeff Molofee's GL Code Tutorial ... NeHe '99");  

    /* Register the function to do all our OpenGL drawing. */
    glutDisplayFunc(&DrawGLScene);  

    /* Go fullscreen.  This is as soon as possible. */
    glutFullScreen();

    /* Even if there are no events, redraw our gl scene. */
    glutIdleFunc(&DrawGLScene);

    /* Register the function called when our window is resized. */
    glutReshapeFunc(&ReSizeGLScene);

    /* Register the function called when the keyboard is pressed. */
    glutKeyboardFunc(&keyPressed);

    /* Initialize our window. */
    InitGL(640, 480);
  
    /* Start Event Processing Engine */  
    glutMainLoop();  

    return 1;
}

