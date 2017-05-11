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