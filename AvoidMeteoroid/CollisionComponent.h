#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H
#include "Component.h"

class CollisionComponent : public Component {
	public:
		CollisionComponent(class Actor* owner);
		~CollisionComponent();


		virtual bool Intersects(const CollisionComponent& other) const = 0;

		virtual bool IntersectsCircle(const class CircleCollisionComponent& other)const = 0;
		virtual bool IntersectsBox(const class BoxCollisionComponent& other)const = 0;

};
#endif // !COLLISIONCOMPONENT_H
