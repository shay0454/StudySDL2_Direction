#pragma once
#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H
#include "Component.h"
#include <SDL_ttf.h>
class TextComponent : public Component {
	public:
		TextComponent(Actor* owner, int drawOrder = 100);
		~TextComponent();

		void SetText(const string& text);// 텍스트 설정
		void SetColor(SDL_Color color) { mColor = color; }// 색 설정
		void Draw(SDL_Renderer* renderer) override;// Draw

	private:
		string mText;
		SDL_Color mColor;
		SDL_Texture* mTexture;
		TTF_Font* mFont;
};
#endif // !TEXTCOMPONENT_H
