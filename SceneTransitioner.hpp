/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#ifndef SCENETRANSITIONER_H
#define SCENETRANSITIONER_H
	
class SceneTransitioner {
public:
	virtual void toTransition() = 0;
	virtual void fromTransition() = 0;
};

#endif