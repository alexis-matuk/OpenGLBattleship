#ifndef MOUSEHANDLER_H_
#define MOUSEHANDLER_H_

void shipLogic(Ship * hit, int x, int y)
{
    valid = true;
    if(hit !=  nullptr)
    {
        if(hit->isPlaced())
        {
            std::cout << "Unclipping " << hit->getName() << std::endl;
            map->unclipShipFromGrid(hit);
        }
        map->setCurrentShipSelected(hit);
        std::cout << "I clicked: \"" << hit->getName() << "\"" << std::endl;
    }
    UI->buttonPress(x, y);
}

void clickedTileLogic(Tile * clickedTile)
{
    if(clickedTile !=  nullptr)
    {
        if(clickedTile->getValidTile())
        {
            if(missile == nullptr)
            {
                std::vector<int> pos = clickedTile->getGridPos();
                client->getEventListener().setPosition(pos[1], pos[0]);
                shooting = true;
            }
        }
    }
}

void mouseHandlerPickingScene(int button, int state, int x, int y)
{
    GLfloat winX, winY, winZ;
    GLdouble near[3];
    GLdouble far[3];
    std::vector<float> res;
    winX = (float)x;
    winY = viewport[1] + (float)viewport[3] - (float)y;
    gluUnProject( winX, winY, 0, modelview, projection, viewport, &near[0], &near[1], &near[2]);
    gluUnProject( winX, winY, 1, modelview, projection, viewport, &far[0], &far[1], &far[2]);
    glm::vec3 vec_near(near[0], near[1], near[2]);
    glm::vec3 vec_far(far[0], far[1], far[2]);
    Ship * hit = map->getShipHit(vec_near, vec_far);
    if(debug)
        nx = near[0]; ny = near[1]; nz = near[2]; fx = far[0]; fy = far[1]; fz = far[2];
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        shipLogic(hit, x, y);
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        Ship * current_ship = map->getCurrentShipSelected();
        map->clipAndUpdateShip(current_ship);
        valid = false;
        map->setCurrentShipSelected(nullptr);
        UI->buttonRelease(x, y);
    }
    glutPostRedisplay();
}

void shipMotion(int x, int y)
{
    Ship * currentShipSelected = map->getCurrentShipSelected();
    if( currentShipSelected!= nullptr && valid)
    {
        float z = currentShipSelected->getParams()["centerZ"] + currentShipSelected->getParams()["transZ"];
        glm::vec3 pos = screenToWorldPoint((float)x, (float)y);
        currentShipSelected->setTranslation(pos.x, pos.y, z);
    }
    UI->passiveButton(x,y);
}

void MousePassiveMotion(int x, int y)
{
    UI->passiveButton(x,y);
}

void mouseMotionMenu(int x, int y)
{
    UI->passiveButton(x,y);
}

void mouseButtonMenu(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        UI->buttonPress(x, y);
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        UI->buttonRelease(x, y);
    }
}

void mouseInGame(int button, int state, int x, int y)
{
    if(!shooting)
    {
        GLfloat winX, winY, winZ;
        GLdouble near[3];
        GLdouble far[3];
        std::vector<float> res;
        winX = (float)x;
        winY = viewport[1] + (float)viewport[3] - (float)y;
        gluUnProject( winX, winY, 0, modelview, projection, viewport, &near[0], &near[1], &near[2]);
        gluUnProject( winX, winY, 1, modelview, projection, viewport, &far[0], &far[1], &far[2]);
        glm::vec3 vec_near(near[0], near[1], near[2]);
        glm::vec3 vec_far(far[0], far[1], far[2]);
        Tile * clickedTile = opponentMap->getTileHit(vec_near, vec_far);
        if(debug)
            nx = near[0]; ny = near[1]; nz = near[2]; fx = far[0]; fy = far[1]; fz = far[2];
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            clickedTileLogic(clickedTile);
            UI->buttonPress(x, y);
        }
        if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
            UI->buttonRelease(x, y);
        glutPostRedisplay();
    }
}

#endif  // MOUSEHANDLER_H_
