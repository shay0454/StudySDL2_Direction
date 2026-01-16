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
	Game() {};
	bool Initialize(); // �ʱ�ȭ
	void RunLoop(); // ���� ����
	void Shutdown(); // ���� ����

	void AddActor(class Actor* actor); // ���� �߰�
	void RemoveActor(class Actor* actor); // ���� ����

	void AddSprite(class SpriteComponent* component); // ��������Ʈ �߰�
	void RemoveSprite(class SpriteComponent* component); // ��������Ʈ ����
	void ReorderSprite(class SpriteComponent* component); // ��������Ʈ ������
	void AddCollider(class CollisionComponent* component);
	void RemoveCollider(class CollisionComponent* component);

	void AddText(class TextComponent* text);
	void RemoveText(class TextComponent* text);

	void CheckCollision(); // �浹 ó��

	class TTF_Font* GetFont() const { return mFont; } // ��Ʈ ����

	SDL_Renderer* GetRenderer()const { return mRenderer; } // ������ ����
	SDL_Texture* GetTexture(const string& fileName); // �ؽ�ó ����

	void AddAsteroid(class Asteroid* ast);
	void RemoveAstroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }

private:
	void ProcessInput(); // �Է� ó��
	void UpdateGame(); // ���� ������Ʈ
	void GenerateOutput(); // ���� ����

	void LoadData(); // ������ �ε�
	void UnLoadData();// ������ ��ε�


	SDL_Window* mWindow; // â
	SDL_Renderer* mRenderer; // ������

	TTF_Font* mFont; // ��Ʈ

	unordered_map<string, SDL_Texture*> mTextures; //�ؽ�ó ����ü
	// ����
	vector<class Actor*> mActors; // ���� ����ü
	vector<class Actor*> mPendingActors; // ���� ���� ����ü

	// ���� �� ����
	vector<class SpriteComponent*> mSprites; // ��������Ʈ ����ü
	vector<class CollisionComponent*> mColliders; // �浹 ������Ʈ ����ü
	vector<class TextComponent*> mTexts;

	Uint32 mTicksCount; // ƽ ī����
	bool mIsRunning; // ���� ���� ����
	bool mUpdateActors; // ���� ������Ʈ ���� ����

	vector<class Ground*> mGrounds; // �� ���� ����ü
	std::vector<class Asteroid*> mAsteroids;
};

#endif // !Game_H
