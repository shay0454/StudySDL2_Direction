#include "SpriteComponent.h"
#include "Component.h"
#include "Game.h"
#include <DirectXMath.h>
using namespace DirectX;

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder):Component(owner), mTexture(nullptr),mDrawOrder(drawOrder),mTexWidth(0),mTexHeight(0),mUseSourceRect(false) {
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
	mOwner->GetGame()->RemoveSprite(this);
}

//Draw
void SpriteComponent::Draw(SDL_Renderer* renderer) {
	if (mTexture) {
		SDL_Rect r;
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());

		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		if (mUseSourceRect) {
			SDL_RenderCopyEx(renderer, mTexture, &mSrcRect, &r, XMConvertToDegrees(mOwner->GetRotation()), nullptr, mFlip);
		}
		else {
			SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, XMConvertToDegrees(mOwner->GetRotation()), nullptr, mFlip);
		}
	}
}

void SpriteComponent::SetDrawOrder(int drawOrder) {
	mDrawOrder = drawOrder;
	mOwner->GetGame()->ReorderSprite(this);
}

//텍스처 설정
void SpriteComponent::SetTexture(SDL_Texture* texture) {
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

void SpriteComponent::SetSourceRect(SDL_Rect srcRect) {
	mUseSourceRect = true;
	mSrcRect = srcRect;
}