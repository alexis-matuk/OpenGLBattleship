#ifndef SCENETRANSITIONER_H
#define SCENETRANSITIONER_H
	
class SceneTransitioner {
public:
	virtual void toTransition() = 0;
	virtual void fromTransition() = 0;
};

#endif