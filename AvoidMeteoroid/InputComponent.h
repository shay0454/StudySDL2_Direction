#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H
#include"MoveComponent.h"

class InputComponent : public MoveComponent {
	public:
		InputComponent(class Actor* owner);

		void ProcessInput(const uint8_t* keyState)override;

		float GetMaxForward() const { return mMaxForwardSpeed; }
		float GetMaxAngular() const { return mMaxAngularSpeed; }
		int GetForwardKey() const { return mForwardKey; }
		int GetBackKey() const { return mBackKey; }
		int GetClockwiseKey() const { return mClockwiseKey; }
		int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }

		void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
		void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
		void SetForwardKey(int key) { mForwardKey = key; }
		void SetBackKey(int key) { mBackKey = key; }
		void SetClockwiseKey(int key) { mClockwiseKey = key; }
		void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }

		void SetActive(bool active) { mActive = active; }

	private:
		bool mActive = true;

		float mMaxForwardSpeed;
		float mMaxAngularSpeed;

		float mCurrentForwardSpeed = 0;
		float mCurrentAngularSpeend = 0;

		int mForwardKey;
		int mBackKey;

		int mClockwiseKey;
		int mCounterClockwiseKey;
};
#endif // !INPUTCOMPONENT_H
