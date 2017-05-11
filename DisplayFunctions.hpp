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
    UI->findButtonByName("acceptShips")->setActive(true);
	glutKeyboardFunc(KeyboardMenu);

    glutMouseFunc(mouseButtonMenu);
    glutMotionFunc(mouseMotionMenu);
    glutPassiveMotionFunc(MousePassiveMotion);

    glutIdleFunc(menuIdle);
    glutDisplayFunc(MenuDisplay);
}

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

void toIngameFunc()
{
    // Scene->changeScene("Menu");
    if(false)
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

void toGameFunc()
{
    Scene->changeScene("PickShips");
}

void toCreditsFunc()
{
    Scene->changeScene("Credits");
}

void toEndingFunc()
{
    Scene->changeScene("Ending");
}

void toMenuFunc()
{
    Scene->changeScene("Menu");
}

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
