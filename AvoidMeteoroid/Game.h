#ifndef GAME_H
#define GAME_H

#include<SDL.h>
#include<vector>
#include"Math.h"
#include <unordered_map>
#include<string>


#define thickness 15
#define screen_width 1024
#define screen_height 768
#define paddle_height 128
#define player01 0
#define player02 1
#define spawn_width 40

using namespace std;

class Game {
public:
	template<class T>
	T* SpawnActor() {
		T* actor = new T(this);
		AddActor(actor);
		return actor;
	}

	template<class T>
	T* DestroyActor();

	Game() {};
	bool Initialize(); // 초기화
	void RunLoop(); // 게임 루프
	void Shutdown(); // 게임 종료

	void AddActor(class Actor* actor); // 액터 추가
	void RemoveActor(class Actor* actor); // 액터 제거

	virtual void OnActorCreated(Actor*) {} // game.h 기반 game에서만 가진 actor에 추가합니다.
	virtual void OnActorDestroyed(Actor*) {} // game.h 기반 game에서만 가진 actor를 제거합니다.

	void AddSprite(class SpriteComponent* component); // 스프라이트 추가
	void RemoveSprite(class SpriteComponent* component); // 스프라이트 제거
	void ReorderSprite(class SpriteComponent* component); // 스프라이트 재정렬
	void AddCollider(class CollisionComponent* component);
	void RemoveCollider(class CollisionComponent* component);

	void AddText(class TextComponent* text);
	void RemoveText(class TextComponent* text);

	void CheckCollision(); // 충돌 처리

	class TTF_Font* GetFont() const { return mFont; } // 포트 리턴

	SDL_Renderer* GetRenderer()const { return mRenderer; } // 랜더러 리턴
	SDL_Texture* GetTexture(const string& fileName); // 텍스처 리턴

protected:
	virtual void LoadData() {} // 데이터 로드
	void UnLoadData();// 데이터 언로드
	virtual void UpdateGame(); // 게임 업데이트


private:
	void ProcessInput(); // 입력 처리
	void GenerateOutput(); // 게임 갱신

	SDL_Window* mWindow; // 창
	SDL_Renderer* mRenderer; // 랜더러

	TTF_Font* mFont; // 폰트

	unordered_map<string, SDL_Texture*> mTextures; //텍스처 집합체
	// 형태
	vector<class Actor*> mActors; // 액터 집합체
	vector<class Actor*> mPendingActors; // 임의 액터 집합체

	// 갱신 및 로직
	vector<class SpriteComponent*> mSprites; // 스프라이트 집합체
	vector<class CollisionComponent*> mColliders; // 충돌 컴포넌트 집합체
	vector<class TextComponent*> mTexts;

	Uint32 mTicksCount; // 틱 카운터
	bool mIsRunning; // 루프 가능 유무
	bool mUpdateActors; // 액터 업데이트 가능 유무


};

#endif // !Game_H
