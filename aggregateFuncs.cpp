#include "aggregateFuncs.hpp"

GLuint viewMode = 0;
GLuint texture[1];

/* Función para dibujar un modelo con rotación, traslación y escala */
void DrawModel(GLMmodel* model, float centerX, float centerY, float centerZ, float scaleX, float scaleY, float scaleZ, float x, float y, float z, float angle, float rotX, float rotY, float rotZ)
{    
    viewMode = GLM_SMOOTH | GLM_MATERIAL | GLM_2_SIDED;		/* reset mode */
    glPushMatrix(); 
    glPushAttrib(GL_ALL_ATTRIB_BITS);   
    glTranslatef(x,y,z);  
    glRotatef(angle, rotX, rotY, rotZ);  
    glScalef(scaleX, scaleY, scaleZ);     
    glTranslatef(centerX, centerY, centerZ);
    if (model)
		glmDraw(model, viewMode);
    glPopAttrib();	
    glPopMatrix();    
}

void DrawModel(GLMmodel* model, float scaleX, float scaleY, float scaleZ, float x, float y, float z, float angle, float rotX, float rotY, float rotZ)
{    
    viewMode = GLM_SMOOTH | GLM_MATERIAL | GLM_2_SIDED;       /* reset mode */
    glPushMatrix(); 
    glPushAttrib(GL_ALL_ATTRIB_BITS);   
    glTranslatef(x,y,z);   
    glRotatef(angle, rotX, rotY, rotZ);  
    glScalef(scaleX, scaleY, scaleZ);     
    if (model)
        glmDraw(model, viewMode);
    glPopAttrib();  
    glPopMatrix();    
}


/* Función para cagar un modelo */
GLMmodel* loadModel(const char* filename)
{
	GLMmodel* model = nullptr;
    if (!model) {		/* load up the model */
	model = glmReadOBJ(filename);
	if (!model) {
	    std::cout << "\nUsage: objviewV2 <-s> <obj filename>\n" << std::endl;
	    exit(0);
	}
	glmUnitize(model);
	glmVertexNormals(model, 90.0, GL_TRUE);
    }
    return model;
}

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