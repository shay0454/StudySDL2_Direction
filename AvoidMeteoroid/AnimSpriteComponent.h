#ifndef ANIMSPRITECOMPONENT_H
#define ANIMSPRITECOMPONENT_H
#include "SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent {
	public:
		AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
		void Update(float deltaTime) override; // 업데이트
		void SetAnimeTextures(const vector<SDL_Texture*>& textures); //애니미 텍스처 설정
		float GetAnimFPS() const { return mAnimFPS; }
		void SetAnimFPS(float fps) { mAnimFPS = fps; }
	private:
		vector<SDL_Texture*> mAnimTextures;
		float mCurrFrame;
		float mAnimFPS;
};
#endif // !ANIMSPRITECOMPONENT_H
