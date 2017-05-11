/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#include "SceneManager.hpp"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

/*
  Add callback function to the scene manager
*/
void SceneManager::addCallback(std::string _levelName, void(*func)())
{
	sceneChangeFunctions[_levelName] = func;
}

/*
  Change scene given a string
*/
void SceneManager::changeScene(std::string _levelName)
{
	sceneChangeFunctions[_levelName]();
}
