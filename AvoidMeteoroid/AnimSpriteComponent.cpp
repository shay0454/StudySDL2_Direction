#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner,int drawOrder):SpriteComponent(owner,drawOrder), mCurrFrame(0.0f), mAnimFPS(24.0f) {}

//업데이트
void AnimSpriteComponent::Update(float deltaTime) {
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0) {
		mCurrFrame += mAnimFPS * deltaTime;

		while (mCurrFrame >= mAnimTextures.size()) {
			mCurrFrame -= mAnimTextures.size();
		}
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

//애니미 텍스처 설정
void AnimSpriteComponent::SetAnimeTextures(const vector<SDL_Texture*>& textures) {
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0) {
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
