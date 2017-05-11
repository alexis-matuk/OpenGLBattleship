/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#ifndef MYMAPSCENETRANSITIONER_H
#define MYMAPSCENETRANSITIONER_H
#include "aggregateFuncs.hpp"
#include "SceneTransitioner.hpp"
class MyMapSceneTransitioner : public SceneTransitioner {
public:
	virtual void toTransition();
	virtual void fromTransition();
};
#endif