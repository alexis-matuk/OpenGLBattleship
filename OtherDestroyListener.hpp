
#ifndef OTHERDESTROYLISTENER_H
#define OTHERDESTROYLISTENER_H
#include "HeaderInclude.hpp"
#include "MyDestroyListener.hpp"
#include "SceneTransitioner.hpp"
#include "Missile.hpp"
#include "Map.hpp"
class OtherDestroyListener : public MyDestroyListener {
private:
public: 
 virtual void onMiss(int row, int col) const;
 virtual void onHit(int row, int col, bool destroyed) const;
 virtual void onDestroy(char shipId, int row1, int col1, int row2, int col2);
};

#endif