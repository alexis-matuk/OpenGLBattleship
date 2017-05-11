/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#ifndef OPPONENTMAPSCENETRANSITIONER_H
#define OPPONENTMAPSCENETRANSITIONER_H
#include "aggregateFuncs.hpp"
#include "SceneTransitioner.hpp"
class OpponentMapSceneTransitioner : public SceneTransitioner {
public:
	virtual void toTransition();
	virtual void fromTransition();
};
#endif