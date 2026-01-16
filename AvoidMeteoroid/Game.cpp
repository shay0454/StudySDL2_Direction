#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"Math.h"
#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include "TextComponent.h"
#include "CollisionComponent.h"
#include "Asteroid.h"
#include <algorithm>
#include"Ship.h"
using namespace std;

//초기화
bool Game::Initialize() {
	// SDL 초기화 및 생성
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) { SDL_Log("Unable to initialize SL : %s", SDL_GetError()); }

	//창 생성
	mWindow = SDL_CreateWindow("Game Programming in C++", 100, 100, screen_width, screen_height, 0);
	if (!mWindow) {
		SDL_Log("Failed to create window : %s ", SDL_GetError());
		return false;
	}

	//랜더러 생성
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		SDL_Log("Failed to create Renderer : %s", SDL_GetError());
		return false;
	}
	mIsRunning = true;

	//이미지 초기화
	int flag = IMG_INIT_PNG;
	int imageResult = IMG_Init(IMG_INIT_PNG);
	if ((imageResult & flag) != flag) { SDL_Log("Failed to initalize PNG : %s", SDL_GetError()); }

	//텍스트용 ttf 초기화
	if (TTF_Init() == -1) {
		SDL_Log("TTF_Init : %s", TTF_GetError());
		return false;
	}

	//텍스트 오픈
	mFont = TTF_OpenFont("Font/OpenSans-Regular.ttf", 20);
	if (!mFont) {
		SDL_Log("Failed to load Font : %s", TTF_GetError());
		return false;
	}
	// 사용 텍스처 로드
	LoadData();
	return true;
}

//루프
void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}
//종료
void Game::Shutdown() {
	TTF_CloseFont(mFont); // 폰트 제거
	TTF_Quit(); // TTF 소멸
	SDL_DestroyRenderer(mRenderer);// 랜더러 소멸
	SDL_DestroyWindow(mWindow);// 창 소멸
	IMG_Quit(); // 이미지 소멸
	SDL_Quit(); // SDL 소멸
}

//액터 추가
void Game::AddActor(Actor* actor) {
	if (mUpdateActors) {
		mPendingActors.emplace_back(actor);
	}
	else { mActors.emplace_back(actor); }
}

void Game::RemoveActor(Actor* actor) {
	auto iter = find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()) {
		iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) {
		iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

//스프라이트 추가
void Game::AddSprite(SpriteComponent* sprite) {
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter) {
		if (myDrawOrder < (*iter)->GetUpdateOrder()) { break; }
	}

	mSprites.insert(iter, sprite);
}

//스프라이트 제거
void Game::RemoveSprite(SpriteComponent* sprite) {
	auto iter = find(mSprites.begin(), mSprites.end(), sprite);
	if (iter != mSprites.end()) {
		mSprites.erase(iter);
	}
}

void Game::ReorderSprite(SpriteComponent* sprite) {
	sort(mSprites.begin(), mSprites.end(),
		[](SpriteComponent* a, SpriteComponent* b) {
			return a->GetDrawOrder() < b->GetDrawOrder();
		});
}

//충돌 컴포넌트 추가
void Game::AddCollider(CollisionComponent* collider) {
	mColliders.emplace_back(collider);
}

//충돌 컴포넌트 제거
void Game::RemoveCollider(CollisionComponent* collider) {
	auto iter = find(mColliders.begin(), mColliders.end(), collider);
	if (iter != mColliders.end()) {
		mColliders.erase(iter);
	}
}

//텍스트 삽입
void Game::AddText(TextComponent* text) {
	mTexts.emplace_back(text);
}

//텍스트 제거
void Game::RemoveText(TextComponent* text) {
	auto iter = find(mTexts.begin(), mTexts.end(), text);
	if (iter != mTexts.end()) {
		mTexts.erase(iter);
	}
}

void Game::CheckCollision() {
	for (size_t i = 0; i < mColliders.size(); ++i) {
		for (size_t j = i + 1; j < mColliders.size(); ++j) {
			CollisionComponent* c1 = mColliders[i];
			CollisionComponent* c2 = mColliders[j];
			if (c1->Intersect(c2)) {
				c1->GetOwner()->OnCollision(c2->GetOwner());
				c2->GetOwner()->OnCollision(c1->GetOwner());
			}
		}
	}
}

//텍스처 리턴
SDL_Texture* Game::GetTexture(const string& fileName) {
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end()) {
		tex = iter->second;
	}
	else {
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			SDL_Log("Failed to load texture file %s", fileName);
			return nullptr;
		}
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex) {
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}
		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

//입력처리
void Game::ProcessInput() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL); // 입력 가져오기
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
	mUpdateActors = true;
	for (auto actor : mActors) {
		actor->ProcessInput(state);
	}
	mUpdateActors = false;
}

//게임 업데이트
void Game::UpdateGame() {
	//FPS 제한
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	deltaTime = (deltaTime > 0.05f ? 0.05f : deltaTime);

	mTicksCount = SDL_GetTicks();

	//액터 업데이트
	mUpdateActors = true;
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdateActors = false;

	//패딩에서 액터로
	for (auto pending : mPendingActors) {
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	CheckCollision();

	//액터 죽음 확인
	vector<Actor*> deadActor;
	for (auto actor : mActors) {
		if (actor->GetState() == Actor::EDead) {
			deadActor.emplace_back(actor);
		}
	}

	//죽은 액터 처리
	for (auto actor : deadActor) {
		delete actor;
	}

}

//갱신 처리
void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255); // 사용할 색 결정
	SDL_RenderClear(mRenderer); // 그릴 버퍼 클리어

	for (auto sprite : mSprites) {
		sprite->Draw(mRenderer);
	}

	for (auto text : mTexts) {
		text->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer); // 그린 버퍼를 현재 버퍼로 변경
}

//사용 데이터 로드
void Game::LoadData() {

	mShip = new Ship(this);
	mShip->SetPosition(Vector2(512.f, 384.f));
	mShip->SetRotation(Math::PiOver2);

	for (int i = 0; i < 20; i++) {
		new Asteroid(this);
	}
}

void Game::UnLoadData() {
	while (!mActors.empty()) {
		delete mActors.back();
	}

	for (auto& tex : mTextures) {
		SDL_DestroyTexture(tex.second);
	}
	mTextures.clear();
}

void Game::AddAsteroid(Asteroid* ast) {
	mAsteroids.emplace_back(ast);
}

void Game::RemoveAstroid(Asteroid* ast) {
	auto iter = std::find(mAsteroids.begin(), mAsteroids.end(), ast);
	if (iter != mAsteroids.end()) {
		mAsteroids.erase(iter);
	}
}