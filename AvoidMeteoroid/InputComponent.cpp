#include"InputComponent.h"
#include"Actor.h"
InputComponent::InputComponent(Actor* owner):MoveComponent(owner),mForwardKey(0),mBackKey(0),mClockwiseKey(0),mCounterClockwiseKey(0) {}

void InputComponent::ProcessInput(const uint8_t* keyState) {
	if (!mActive) {
		mCurrentForwardSpeed = 0;
		mCurrentAngularSpeend = 0;
		SetForwardSpeed(0);
		SetAngularSpeed(0);
		return;
	}
	if (keyState[mForwardKey]) {
		mCurrentForwardSpeed += mMaxForwardSpeed;
	}
	if (keyState[mBackKey]) {
		mCurrentForwardSpeed -= mMaxForwardSpeed;
	}
	if (!(keyState[mForwardKey] || keyState[mBackKey])) {
		mCurrentForwardSpeed *= 0.9f;
	}
	SetForwardSpeed(SDL_clamp(mCurrentForwardSpeed, -600, 600));

	if (keyState[mClockwiseKey]) {
		mCurrentAngularSpeend += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey]) {
		mCurrentAngularSpeend -= mMaxAngularSpeed;
	}
	if (!(keyState[mClockwiseKey] || keyState[mCounterClockwiseKey])) {
		mCurrentAngularSpeend *= 0.9f;
	}
	SetAngularSpeed(SDL_clamp(mCurrentAngularSpeend,-Math::TwoPi,Math::TwoPi));
}