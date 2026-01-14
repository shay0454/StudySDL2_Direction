#ifndef BGSpriteComponent_H
#define BGSpriteComponent_H
#include "SpriteComponent.h"
class BGSpriteComponent : public SpriteComponent {
	public:
		BGSpriteComponent(class Actor* owner, int drawOrder = 10);
		void Update(float deltaTime) override; // 업데이트
		void Draw(SDL_Renderer* renderer) override; //Draw

		void SetBGTextures(const vector<SDL_Texture*>& textures);
		void SetScreenSize(const Vector2& size) { mScreenSize = size; }
		void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
		float GetScrollSpeed() const { return mScrollSpeed; }

	private:
		struct BGTexture {	
			SDL_Texture* mTextrue;
			Vector2 mOffset;
		};

		vector<BGTexture> mBGTextures;
		Vector2 mScreenSize;
		float mScrollSpeed;
};
#endif // !BGSpriteComponent_H
