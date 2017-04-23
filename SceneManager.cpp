#include "SceneManager.hpp"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}


void SceneManager::addCallback(std::string _levelName, void(*func)())
{
	sceneChangeFunctions[_levelName] = func;
}

void SceneManager::changeScene(std::string _levelName)
{
	sceneChangeFunctions[_levelName]();
}
