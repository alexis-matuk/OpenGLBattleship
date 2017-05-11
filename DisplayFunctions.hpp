/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

/*
	====== START DISPLAY FUNCTIONS ======
*/
/*
    Display function for picking ship positions
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

/*
    Display that renders the menu with the rotating ship and the 2 buttons
*/
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
        setPanelViewPort();
            UI->drawPanelByName("Title", false);
            UI->drawActivePopups();
        setButtonViewPort();
            UI->drawButtonByName("start");
            UI->drawButtonByName("credits");
        setWorldViewPort();
    enableUIParams();
    glFlush();
    glutSwapBuffers();
}

/*
    Display that renders the credits
*/
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

/*
    Display that renders the ending scene, showing how many ships you destroyed
    and how many ships the opponent destroyed
*/
void endingDisplay()
{
    glLoadIdentity();
    gluLookAt(0, 0, START_Z+camZ, 0, 0, camZ, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        updateMatrices();
        client->drawEnemyShips();
        client->drawFriendlyShips();
    glPopMatrix();

    disableUIParams();
        setPanelViewPort();
            if(debug)
                UI->drawDebugLines();
            UI->drawPanelByName("enemyShips", false);
            UI->drawPanelByName("friendlyShips", false);
            UI->drawPanelByName("result", false);
        setButtonViewPort();
            UI->drawButtonByName("ending");
        setWorldViewPort();
    enableUIParams();
    glFlush();
    glutSwapBuffers();
}

/*
    Display for choosing where to attack the opponent
*/
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

/*
    Display that shows the animation of finding game...
*/
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
  Display that shows your map being hit by the opponent  
*/
void myMapBeingHitDisplay()
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

/*
	====== END DISPLAY FUNCTIONS ======
*/


/*
    ====== START IDLE FUNCTIONS ======
*/

/*
  Idle function while you are ingame  
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

/*
    Default idle function
*/
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

/*
    Idle function when on main menu
*/
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

/*
    Idle function that handles the Finding Game... animation
*/
void findingGameIdle()
{
    frame++;
    currenttime = glutGet(GLUT_ELAPSED_TIME);
    if(sceneStartTime == -1)
        sceneStartTime = currenttime;
    if(!waitingForServer)
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

/*
  Setup function for going to picking ships scene  
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

/*
    Setup function for going to the menu scene
*/
void menuScene()
{
    UI->deactivateButtons();
    UI->findButtonByName("credits")->setActive(true);
    UI->findButtonByName("start")->setActive(true);
    UI->findButtonByName("acceptShips")->setActive(true);
	glutKeyboardFunc(KeyboardMenu);

    glutMouseFunc(mouseButtonMenu);
    glutMotionFunc(mouseMotionMenu);
    glutPassiveMotionFunc(MousePassiveMotion);

    glutIdleFunc(menuIdle);
    glutDisplayFunc(MenuDisplay);
}

/*
    Setup function for ingame scene
*/
void pickingScene()
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

/*
    Setup function for credits scene
*/
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

/*
    Setup function for ending scene
*/
void endingScene()
{
    UI->deactivateButtons();
    UI->findButtonByName("ending")->setActive(true);
    glutKeyboardFunc(KeyboardMenu);

    glutMouseFunc(mouseButtonMenu);
    glutMotionFunc(mouseMotionMenu);
    glutPassiveMotionFunc(MousePassiveMotion);

    glutDisplayFunc(endingDisplay);
}

/*
    Setup function for finding game scene
*/
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
    Setup function for returning to main menu after game ended
*/
void myMapBeingHitScene()
{
    UI->deactivateButtons();
    glutKeyboardFunc(&Keyboard);
    glutKeyboardUpFunc(&KeyboardUp);
    glutSpecialFunc(SpecialInput);
    glutSpecialUpFunc(SpecialInputUp);

    glutMouseFunc(NULL);
    glutMotionFunc(NULL);
    glutPassiveMotionFunc(NULL);

    glutIdleFunc(idle);
    glutDisplayFunc(myMapBeingHitDisplay);
}

/*
	====== END OF CALLBACK FUNCTIONS FOR SCENE MANAGEMENT ======
*/


/*
	====== START OF CALLBACK FUNCTIONS FOR UI ======
*/

/*
    Function that transitions to the game start
    Checks if every ship is placed before sending to the server
*/
void toIngameFunc()
{
    // Scene->changeScene("Menu");
    if(!map->everyShipPlaced())
    	UI->activatePopup("warning");
    else
    {
        map->setReadyToSend(true);
        map->centerMap();
        while(!hasOrder)
        {
            ;//BLOCK
        }
        if(attacking)
            Scene->changeScene("InGame");
        else
            Scene->changeScene("BeingHit");
    }

}

/*
  Function for transition to picking ships scene  
*/
void toGameFunc()
{
    Scene->changeScene("PickShips");
}

/*
  Function for transition to credits scene  
*/
void toCreditsFunc()
{
    Scene->changeScene("Credits");
}

/*
  Function for transition to ending scene  
*/
void toEndingFunc()
{
    Scene->changeScene("Ending");
}

/*
  Function for transition to menu scene  
*/
void toMenuFunc()
{
    Scene->changeScene("Menu");
}

/*
  Function for transition to main menu after game ended  
  Resets both maps before going to main menu
  Resets client connection to find another server
*/
void toMenuFromEndingFunc()
{
    map->reset();
    map->unCenterMap();
    std::cout << "RESET MY MAP" << std::endl;
    opponentMap->reset();
    opponentMap->setDrawShips(false);
    std::cout << "RESET OPPONENT MAP" << std::endl;
    if(client)
    {
        delete client;
        client = nullptr;
    }
    waitingForServer = true;
    Scene->changeScene("Menu");
}

/*
    Function for transition to finding game scene
    This transition function creates the client and makes the connection with the server.
    If the server is not up, there will be a popup letting you know the server was not found.
    If it finds the server it will create a client and wait for another player to play with.
    The thread for the client's main loop and communication with the server is also created
*/
void toFindGameFunc()
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    client = new UIClient(PORT, globalHostname, &hints, map, opponentMap);
    if(!client->isValid())
    {
        UI->activatePopup("serverWarning");
        delete client;
        client = nullptr;
        std::cerr << "Couldn't create client" << std::endl;
    }
    else
    {
        client->setww(ww);
        client->setwh(wh);
        pthread_t thread;
        int r = pthread_create(&thread, NULL, &clientThread, NULL);
        if(r != 0)
        {
            std::cerr << "Couldn't create client" << std::endl;
            exit(-1);
        }

        Scene->changeScene("FindGame");
    }
}
/*
	====== END OF CALLBACK FUNCTIONS FOR UI ======
*/
