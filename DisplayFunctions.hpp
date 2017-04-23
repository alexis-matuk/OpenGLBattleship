/*
	====== START DISPLAY FUNCTIONS ======
*/
void Display()
{				 				    
	glLoadIdentity();	
	gluLookAt(0, 0, START_Z+camZ, 0, 0, camZ, 0, 1, 0);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      
	glPushMatrix();
		if (wireframe)
		    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Activar wireframe
		else
		    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);        
		glRotatef(xRot,1,0,0);	
		glRotatef(yRot,0,1,0);	
		glRotatef(zRot,0,0,1);
        updateMatrices();                                  
        map->Draw(); 
        if(debug)        
            drawRaycast();              
    glPopMatrix();

    disableUIParams();
    	setPanelViewPort();
    		UI->drawActivePopups();  
    	setButtonViewPort();                          
        UI->drawButtonByName("start");            
        setWorldViewPort();
    enableUIParams();

    glFlush();
    glutSwapBuffers();
}

void MenuDisplay()
{
	glLoadIdentity();	
	gluLookAt(0, 0, START_Z+camZ, 0, 0, camZ, 0, 1, 0);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	disableUIParams(); 		   
		setButtonViewPort();                            
        UI->drawButtonByName("toGame"); 
        setPanelViewPort();   
        	UI->drawPanelByName("Title", false);     	        	
    		UI->drawActivePopups(); 
        setWorldViewPort();
    enableUIParams();      
    glFlush();
    glutSwapBuffers();
}

/*
	====== END DISPLAY FUNCTIONS ======
*/

/*
	====== START OF CALLBACK FUNCTIONS FOR SCENE MANAGEMENT ======
*/

void menuScene()
{	
	glutKeyboardFunc(KeyboardMenu);
    glutMouseFunc(mouseButtonMenu);
    glutMotionFunc(mouseMotionMenu); 
    glutPassiveMotionFunc(MousePassiveMotion);
    glutDisplayFunc(MenuDisplay);
}

void pikcingScene()
{	
	glutKeyboardFunc(&Keyboard);
    glutKeyboardUpFunc(&KeyboardUp);
    glutSpecialFunc(SpecialInput);
    glutSpecialUpFunc(SpecialInputUp);
    glutMouseFunc(mouseHandlerPickingScene);
    glutMotionFunc(shipMotion); 
    glutPassiveMotionFunc(MousePassiveMotion);
    glutIdleFunc(idle);
	glutDisplayFunc(Display);
}

/*
	====== END OF CALLBACK FUNCTIONS FOR SCENE MANAGEMENT ======
*/


/*
	====== START OF CALLBACK FUNCTIONS FOR UI ======
*/

void toMenuFunc()
{
    // Scene->changeScene("Menu");
    if(!map->everyShipPlaced())
    	UI->activatePopup("warning");
    
}

void toGameFunc()
{
	Scene->changeScene("PickShips");
}

/*
	====== END OF CALLBACK FUNCTIONS FOR UI ======
*/