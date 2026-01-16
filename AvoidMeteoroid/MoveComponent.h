#ifndef MOVECOMPONENT_H
#define MOVECOMPONENT_H

#include "Component.h"
class MoveComponent : public Component {
	public:
		MoveComponent(class Actor* owner, int updateOrder = 10);

		void Update(float deltaTime)override;

		float GetAngularSpeed()const { return mAngularSpeed; }
		void SetAngularSpeed(float speed) { mAngularSpeed = speed; }

		float GetForwardSpeed()const { return mForwardSpeed; }
		void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

	private:
		// 회전율 제어(초단 라디안)
		float mAngularSpeed;
		// 진방 이동 제어(초단 단위)
		float mForwardSpeed;
};
#endif