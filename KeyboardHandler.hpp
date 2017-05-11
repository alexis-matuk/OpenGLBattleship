/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

/*
    Function that checks keyboard input when picking ship positions
*/
void Keyboard(unsigned char key, int x, int y)
{

    switch (key) 
    {
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
            rotatingXUp = true;
            break;
            case 's':
            rotatingXDown = true;
            break; 
            case 'a':
            rotatingYLeft = true;
            break;
            case 'd':
            rotatingYRight = true;
            break; 
            case 'e':
            rotatingZLeft = true;
            break; 
            case 'q':
            rotatingZRight = true;
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
           }
       }    
       glutPostRedisplay();
   }

/*
    Function that detects key press for map rotation
*/
   void inGameKeyboard(unsigned char key, int x, int y)
   {

    switch (key) 
    {   
        case 'w':
        rotatingXUp = true;
        break;
        case 's':
        rotatingXDown = true;
        break; 
        case 'a':
        rotatingYLeft = true;
        break;
        case 'd':
        rotatingYRight = true;
        break; 
        case 'e':
        rotatingZLeft = true;
        break; 
        case 'q':
        rotatingZRight = true;
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
        }
    }    
    glutPostRedisplay();
}

/*
    Function that detects key onrelease for map rotation 
*/
void KeyboardUp(unsigned char key, int x, int y)
{
    switch (key) 
    {   
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
        }
    }
    glutPostRedisplay();
}

/*
    Function that detects arroy key press
*/
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

/*
    Function that detects arrow key onrelease
*/
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

/*
    Function that detects escape key while in menu scene
*/
void KeyboardMenu(unsigned char key, int x, int y)
{
    switch (key) 
    {
        case 27:
        exit(0);
        break;
        default:{
            break;
        }
    }    
    glutPostRedisplay();
}
#endif