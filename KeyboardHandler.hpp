void Keyboard(unsigned char key, int x, int y)
{

    switch (key) {
    case ' ':{        
        Ship * hit = map->getCurrentShipSelected();
        if(hit != nullptr)
        {
            Map::Direction current_dir = hit->getDirection();                           
            if(current_dir == Map::Direction::TOP_BOTTOM)
            {
                hit->addRotation(0, 90, 0);
                hit->setDirection(Map::Direction::LEFT_RIGHT);
            }
            else
            {
                hit->addRotation(0, -90, 0);
                hit->setDirection(Map::Direction::TOP_BOTTOM);
            }                
        }
    break;}
	case 'w':
		// xRot-=5;
        rotatingXUp = true;
	break;
	case 's':
		// xRot+=5;
        rotatingXDown = true;
	break; 
	case 'a':
        rotatingYLeft = true;
		// yRot+=5;
	break;
	case 'd':
        rotatingYRight = true;
		// yRot-=5;
	break; 
	case 'e':
        rotatingZLeft = true;
		// zRot-=5;
	break; 
	case 'q':
        rotatingZRight = true;
		// zRot+=5;
	break; 
    case 'p':{
	    wireframe = !wireframe;
	    break;
	}
    case 27:
	exit(0);
	break;
    default:{
	    break;
	}			/* flush all other input                                 */
    }    
    glutPostRedisplay();	/* redisplay afterword */
}

void KeyboardUp(unsigned char key, int x, int y)
{
    switch (key) {   
    case 'w':
        rotatingXUp = false;
    break;
    case 's':
        rotatingXDown = false;
    break; 
    case 'a':
        rotatingYLeft = false;
    break;
    case 'd':
        rotatingYRight = false;
    break; 
    case 'e':
        rotatingZLeft = false;
    break; 
    case 'q':
        rotatingZRight = false;
    break; 
    default:{
        break;
    }           /* flush all other input                                 */
    }
    glutPostRedisplay();    /* redisplay afterword */
}

/* Función para detectar las flechas */
void SpecialInput(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			zoomingIn = true;
		break;	
		case GLUT_KEY_DOWN:
			zoomingOut = true;
		break;
	}    
	glutPostRedisplay();
}

/* Función para detectar las flechas */
void SpecialInputUp(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            zoomingIn = false;
        break;  
        case GLUT_KEY_DOWN:
            zoomingOut = false;
        break;
    }
    glutPostRedisplay();
}

void KeyboardMenu(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
    exit(0);
    break;
    default:{
        break;
    }           /* flush all other input                                 */
    }    
    glutPostRedisplay();    /* redisplay afterword */
}