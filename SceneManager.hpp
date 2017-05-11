/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#ifndef SceneManager_H
#define SceneManager_H

#include "HeaderInclude.hpp"

class SceneManager{	
private:
	  std::map<std::string, void (*)()> sceneChangeFunctions;
public:	
	SceneManager();
	~SceneManager();
	void addCallback(std::string _levelName, void(*)());
	void changeScene(std::string _levelName);
};

#endif
