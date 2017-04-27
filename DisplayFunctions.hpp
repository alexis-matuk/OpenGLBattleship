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
            UI->drawButtonByName("acceptShips");            
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

    glPushMatrix();
        glRotatef(menuShipRot, 0, 1, 0);
        updateMatrices();                                         
        menuShip->Draw(textureMode);               
    glPopMatrix();

    disableUIParams();         
        setButtonViewPort();                            
            UI->drawButtonByName("start"); 
            UI->drawButtonByName("credits"); 
        setPanelViewPort();   
            UI->drawPanelByName("Title", false);                    
            UI->drawActivePopups(); 
        setWorldViewPort();        
    enableUIParams(); 
    glFlush();
    glutSwapBuffers();
}

void creditsDisplay()
{
    glLoadIdentity();   
    gluLookAt(0, 0, START_Z+camZ, 0, 0, camZ, 0, 1, 0); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    disableUIParams();         
        setPanelViewPort();   
            UI->drawPanelByName("credits", true);
        setButtonViewPort();
            UI->drawButtonByName("menu");
    enableUIParams(); 
    glFlush();
    glutSwapBuffers();
}

void inGameDisplay()
{
    glLoadIdentity();   
    gluLookAt(0, 0, START_Z+camZ_opponent, 0, 0, camZ_opponent, 0, 1, 0); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       
    glPushMatrix();
        if (wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Activar wireframe
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);        
        glRotatef(xRot_opponent,1,0,0);  
        glRotatef(yRot_opponent,0,1,0);  
        glRotatef(zRot_opponent,0,0,1);
        updateMatrices();                                  
        opponentMap->Draw(); 
        // map->Draw();   
        if(missile != nullptr)
        {            
            if(!missile->DrawMissile(textureMode))
            {                
                delete missile;
                missile = nullptr;     
            shooting = false;
            }
        }
        if(debug)        
            drawRaycast();              
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void findingGameDisplay()
{
    glLoadIdentity();   
    gluLookAt(0, 0, START_Z+camZ, 0, 0, camZ, 0, 1, 0); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    disableUIParams();         
        setPanelViewPort();   
            UI->drawPanelByName("findingGame", false);
    enableUIParams(); 
    glFlush();
    glutSwapBuffers();
}

/*
	====== END DISPLAY FUNCTIONS ======
*/


/*
    ====== START IDLE FUNCTIONS ======
*/

void inGameIdle()
{
    frame++;
   currenttime = glutGet(GLUT_ELAPSED_TIME);
   if (currenttime - timebase > 0.5) 
   {
        modifyCameraInGame();
        timebase = currenttime;    
        frame = 0;        
        glutPostRedisplay();        
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

void menuIdle()
{    
    frame++;
    currenttime = glutGet(GLUT_ELAPSED_TIME);
    if (currenttime - timebase > 0.5) 
    {        
        menuShipRot += 0.1 * (currenttime - timebase);
        timebase = currenttime;    
        frame = 0;        
        glutPostRedisplay();        
    }  
}

void findingGameIdle()
{    
    frame++;
    currenttime = glutGet(GLUT_ELAPSED_TIME);
    if(sceneStartTime == -1)
        sceneStartTime = currenttime;

    /*FOUND SERVER*/
    if((float)(currenttime - sceneStartTime)/1000 >= 5)
        Scene->changeScene("PickShips");

    if (currenttime - timebase > 500) 
    {        
        if(animationCounter == 0)
            UI->findPanelByName("findingGame")->setContent("Finding Game");
        else if(animationCounter == 1)
            UI->findPanelByName("findingGame")->setContent("Finding Game.");
        else if(animationCounter == 2)        
            UI->findPanelByName("findingGame")->setContent("Finding Game..");
        else if(animationCounter >= 3)     
        {
            UI->findPanelByName("findingGame")->setContent("Finding Game...");
            animationCounter = -1;
        }               
        
        animationCounter++;
        timebase = currenttime;    
        frame = 0;        
        glutPostRedisplay();        
    }  
}


/*
    ====== END IDLE FUNCTIONS ======
*/

/*
	====== START OF CALLBACK FUNCTIONS FOR SCENE MANAGEMENT ======
*/

void inGameScene()
{
    UI->deactivateButtons();
    glutKeyboardFunc(&inGameKeyboard);
    glutKeyboardUpFunc(&KeyboardUp);
    glutSpecialFunc(SpecialInput);
    glutSpecialUpFunc(SpecialInputUp);

    glutMouseFunc(mouseInGame);    
    glutPassiveMotionFunc(MousePassiveMotion);

    glutIdleFunc(inGameIdle);
    glutDisplayFunc(inGameDisplay);
}

void menuScene()
{	    
    UI->deactivateButtons();
    UI->findButtonByName("credits")->setActive(true);
    UI->findButtonByName("start")->setActive(true);    
	glutKeyboardFunc(KeyboardMenu);

    glutMouseFunc(mouseButtonMenu);
    glutMotionFunc(mouseMotionMenu); 
    glutPassiveMotionFunc(MousePassiveMotion);

    glutIdleFunc(menuIdle);
    glutDisplayFunc(MenuDisplay);
}

void pikcingScene()
{	
    UI->deactivateButtons();
    UI->findButtonByName("acceptShips")->setActive(true);    
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

void creditsScene()
{
    UI->deactivateButtons();
    UI->findButtonByName("menu")->setActive(true);
    glutKeyboardFunc(KeyboardMenu);

    glutMouseFunc(mouseButtonMenu);
    glutMotionFunc(mouseMotionMenu); 
    glutPassiveMotionFunc(MousePassiveMotion);

    glutDisplayFunc(creditsDisplay);
}

void findingGameScene()
{
    UI->deactivateButtons();
    glutKeyboardFunc(KeyboardMenu);

    glutMouseFunc(mouseButtonMenu);
    glutMotionFunc(mouseMotionMenu); 
    glutPassiveMotionFunc(MousePassiveMotion);

    glutIdleFunc(findingGameIdle);
    glutDisplayFunc(findingGameDisplay);
}

/*
	====== END OF CALLBACK FUNCTIONS FOR SCENE MANAGEMENT ======
*/


/*
	====== START OF CALLBACK FUNCTIONS FOR UI ======
*/

void toIngameFunc()
{    
    // Scene->changeScene("Menu");
    if(!map->everyShipPlaced())
    	UI->activatePopup("warning");
    else
    {    
        char ** test = map->exportMapToServer();
        for(int i = 0; i < 11; i++)
        {
            for(int j = 0; j < 11; j++)
            {
                std::cout << test[i][j] << ", ";
            }
            std::cout << std::endl;
        }
        Scene->changeScene("InGame");
    }

}

void toGameFunc()
{  
	Scene->changeScene("PickShips");
}

void toCreditsFunc()
{
    Scene->changeScene("Credits");    
}

void toMenuFunc()
{
    Scene->changeScene("Menu");  
}

void toFindGameFunc()
{
    Scene->changeScene("FindGame");      
}
/*
	====== END OF CALLBACK FUNCTIONS FOR UI ======
*/