#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include "Component.h"


class SpriteComponent : public Component {
	public:
		SpriteComponent(class Actor* owner, int drawOrder = 100);
		~SpriteComponent();
		virtual void Draw(SDL_Renderer* renderer);//Draw
		virtual void SetTexture(SDL_Texture* texture);//텍스처 설정
		void SetDrawOrder(int drawOrder);
		int GetDrawOrder() const { return mDrawOrder; }
		void SetTexHeight(int height) { mTexHeight = height;}
		int GetTexHeight() const { return mTexHeight * mOwner->GetScale(); }
		void SetTexWidth(int width) { mTexWidth = width; }
		int GetTexWidth() const { return mTexWidth * mOwner->GetScale(); }

		void SetFlip(SDL_RendererFlip flip) { mFlip = flip; }

		void SetSourceRect(SDL_Rect srcRect);
		void SourceRectClear() { mUseSourceRect = false; }


	protected:
		SDL_Texture* mTexture;
		int mDrawOrder;
		int mTexWidth;
		int mTexHeight;
		SDL_RendererFlip mFlip = SDL_FLIP_NONE;

		SDL_Rect mSrcRect;

		bool mUseSourceRect;
};

#endif