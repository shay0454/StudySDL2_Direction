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
using namespace std;

//�ʱ�ȭ
bool Game::Initialize() {
	// SDL �ʱ�ȭ �� ����
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) { SDL_Log("Unable to initialize SL : %s", SDL_GetError()); }

	//â ����
	mWindow = SDL_CreateWindow("Game Programming in C++", 100, 100, screen_width, screen_height, 0);
	if (!mWindow) {
		SDL_Log("Failed to create window : %s ", SDL_GetError());
		return false;
	}

	//������ ����
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		SDL_Log("Failed to create Renderer : %s", SDL_GetError());
		return false;
	}
	mIsRunning = true;

	//�̹��� �ʱ�ȭ
	int flag = IMG_INIT_PNG;
	int imageResult = IMG_Init(IMG_INIT_PNG);
	if ((imageResult & flag) != flag) { SDL_Log("Failed to initalize PNG : %s", SDL_GetError()); }

	//�ؽ�Ʈ�� ttf �ʱ�ȭ
	if (TTF_Init() == -1) {
		SDL_Log("TTF_Init : %s", TTF_GetError());
		return false;
	}

	//�ؽ�Ʈ ����
	mFont = TTF_OpenFont("Font/OpenSans-Regular.ttf", 20);
	if (!mFont) {
		SDL_Log("Failed to load Font : %s", TTF_GetError());
		return false;
	}
	// ��� �ؽ�ó �ε�
	LoadData();
	return true;
}

//����
void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}
//����
void Game::Shutdown() {
	TTF_CloseFont(mFont); // ��Ʈ ����
	TTF_Quit(); // TTF �Ҹ�
	SDL_DestroyRenderer(mRenderer);// ������ �Ҹ�
	SDL_DestroyWindow(mWindow);// â �Ҹ�
	IMG_Quit(); // �̹��� �Ҹ�
	SDL_Quit(); // SDL �Ҹ�
}

//���� �߰�
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

//��������Ʈ �߰�
void Game::AddSprite(SpriteComponent* sprite) {
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter) {
		if (myDrawOrder < (*iter)->GetUpdateOrder()) { break; }
	}

	mSprites.insert(iter, sprite);
}

//��������Ʈ ����
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

//�浹 ������Ʈ �߰�
void Game::AddCollider(CollisionComponent* collider) {
	mColliders.emplace_back(collider);
}

//�浹 ������Ʈ ����
void Game::RemoveCollider(CollisionComponent* collider) {
	auto iter = find(mColliders.begin(), mColliders.end(), collider);
	if (iter != mColliders.end()) {
		mColliders.erase(iter);
	}
}

//�ؽ�Ʈ ����
void Game::AddText(TextComponent* text) {
	mTexts.emplace_back(text);
}

//�ؽ�Ʈ ����
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

//�ؽ�ó ����
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

//�Է�ó��
void Game::ProcessInput() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL); // �Է� ��������
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
}

//���� ������Ʈ
void Game::UpdateGame() {
	//FPS ����
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	deltaTime = (deltaTime > 0.05f ? 0.05f : deltaTime);

	mTicksCount = SDL_GetTicks();

	//���� ������Ʈ
	mUpdateActors = true;
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdateActors = false;

	//�е����� ���ͷ�
	for (auto pending : mPendingActors) {
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	CheckCollision();

	//���� ���� Ȯ��
	vector<Actor*> deadActor;
	for (auto actor : mActors) {
		if (actor->GetState() == Actor::EDead) {
			deadActor.emplace_back(actor);
		}
	}

	//���� ���� ó��
	for (auto actor : deadActor) {
		delete actor;
	}

}

//���� ó��
void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255); // ����� �� ����
	SDL_RenderClear(mRenderer); // �׸� ���� Ŭ����

	for (auto sprite : mSprites) {
		sprite->Draw(mRenderer);
	}

	for (auto text : mTexts) {
		text->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer); // �׸� ���۸� ���� ���۷� ����
}

//��� ������ �ε�
void Game::LoadData() {

	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.f, 384.0f));
	BGSpriteComponent* bg = new BGSpriteComponent(temp);

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