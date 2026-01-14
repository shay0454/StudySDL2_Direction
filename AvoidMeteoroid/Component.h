#ifndef COMPONENT_H
#define COMPONENT_H

#include<SDL.h>
#include "Actor.h"

using namespace std;

class Component {
public:
	Component(class Actor* owner, int updateOrder = 100);
	Actor* GetOwner() const { return mOwner; }
	virtual ~Component();
	virtual void Update(float deltaTime);//업데이트
	virtual void Draw(SDL_Renderer* renderer);//Draw
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};

#endif // !COMPONENT_H
