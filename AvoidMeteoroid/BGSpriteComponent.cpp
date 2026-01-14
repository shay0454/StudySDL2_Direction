#include "BGSpriteComponent.h"
#include "Actor.h"
#include"DirectXMath.h"
using namespace DirectX;

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder) : SpriteComponent(owner,drawOrder),mScrollSpeed(0.0f){}

void BGSpriteComponent::SetBGTextures(const vector<SDL_Texture*>& textures) {
	int count = 0;
	for (auto tex : textures) {
		BGTexture temp;
		temp.mTextrue = tex;
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		count++;
	}
}

//업데이트
void BGSpriteComponent::Update(float deltaTime) {
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures) {
		bg.mOffset.x += mScrollSpeed * deltaTime;
		if (bg.mOffset.x < -mScreenSize.x) {
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

//Draw
void BGSpriteComponent::Draw(SDL_Renderer* renderer) {
	for (auto bg : mBGTextures) {
		SDL_Rect r;
		r.w = static_cast<int>(mScreenSize.x);
		r.h = static_cast<int>(mScreenSize.y);

		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);
		
		SDL_RenderCopyEx(renderer, bg.mTextrue, nullptr, &r, XMConvertToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}