void mouseHandlerPickingScene(int button, int state, int x, int y)
{
    //Code from http://nehe.gamedev.net/article/using_gluunproject/16013/    
    GLfloat winX, winY, winZ;    
    GLdouble near[3];
    GLdouble far[3];
    std::vector<float> res;    
    
    /*Obtenido de http://stackoverflow.com/questions/113352/opengl-projecting-mouse-click-onto-geometry*/

    winX = (float)x;
    winY = viewport[1] + (float)viewport[3] - (float)y;
    
    // 0.1 is for giving a depth offset from the eye position
    gluUnProject( winX, winY, 0, modelview, projection, viewport, &near[0], &near[1], &near[2]);
    gluUnProject( winX, winY, 1, modelview, projection, viewport, &far[0], &far[1], &far[2]);    

    glm::vec3 vec_near(near[0], near[1], near[2]);
    glm::vec3 vec_far(far[0], far[1], far[2]);

    Ship * hit = map->getShipHit(vec_near, vec_far);

    if(debug)
    {
        nx = near[0];
        ny = near[1];
        nz = near[2];
        fx = far[0];
        fy = far[1];
        fz = far[2];
    }   

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
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

        float winX = (float)x;
        float winY = viewport[1] + (float)viewport[3] - (float)y;

        GLdouble near[3], far[3];  // already computed as above
        // 0.1 is for giving a depth offset from the eye position
        gluUnProject( winX, winY, 0, modelview, projection, viewport, &near[0], &near[1], &near[2]);
        gluUnProject( winX, winY, 1, modelview, projection, viewport, &far[0], &far[1], &far[2]);   

        if(near[2] == far[2])     // this means we have no solutions
           return;

        GLfloat t = (near[2] - z) / (near[2] - far[2]);

        // so here are the desired (x, y) coordinates
        GLfloat world_x = near[0] + (far[0] - near[0]) * t,
                world_y = near[1] + (far[1] - near[1]) * t;
        currentShipSelected->setTranslation(world_x, world_y, z);
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
        //Code from http://nehe.gamedev.net/article/using_gluunproject/16013/    
        GLfloat winX, winY, winZ;    
        GLdouble near[3];
        GLdouble far[3];
        std::vector<float> res;    
        
        /*Obtenido de http://stackoverflow.com/questions/113352/opengl-projecting-mouse-click-onto-geometry*/

        winX = (float)x;
        winY = viewport[1] + (float)viewport[3] - (float)y;
        
        // 0.1 is for giving a depth offset from the eye position
        gluUnProject( winX, winY, 0, modelview, projection, viewport, &near[0], &near[1], &near[2]);
        gluUnProject( winX, winY, 1, modelview, projection, viewport, &far[0], &far[1], &far[2]);    

        glm::vec3 vec_near(near[0], near[1], near[2]);
        glm::vec3 vec_far(far[0], far[1], far[2]);

        Tile * clickedTile = opponentMap->getTileHit(vec_near, vec_far);
        // Tile * clickedTile = map->getTileHit(vec_near, vec_far);

        if(debug)
        {
            nx = near[0];
            ny = near[1];
            nz = near[2];
            fx = far[0];
            fy = far[1];
            fz = far[2];
        }   

        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {         
            if(clickedTile !=  nullptr)
            {      
                std::cout << "I clicked on tile: " << clickedTile->getName() << std::endl;
                if(clickedTile->getValidTile())
                {
                    if(missile == nullptr)
                    {
                        missile = new Missile(clickedTile);
                        shooting = true;
                    } 
                }                               
            }
            UI->buttonPress(x, y);
        } 
        if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {                      
            UI->buttonRelease(x, y);
        }    
        glutPostRedisplay();
    }    
}
