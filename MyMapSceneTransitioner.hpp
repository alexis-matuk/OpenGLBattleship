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