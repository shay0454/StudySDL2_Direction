#include "TextComponent.h"
//텍스트 설정
TextComponent::TextComponent(Actor* owner, int drawOrder):Component(owner,drawOrder){
	mOwner->GetGame()->AddText(this);
	mFont = mOwner->GetGame()->GetFont();
	mColor = { 255,255,255,255 };
}

TextComponent::~TextComponent() {
	mOwner->GetGame()->RemoveText(this);
	if (mTexture) {
		SDL_DestroyTexture(mTexture);
	}
}

void TextComponent::SetText(const string& text) {
	mText = text;
	
	if (mTexture != nullptr)
		SDL_DestroyTexture(mTexture);

	SDL_Surface* surf = TTF_RenderUTF8_Blended(mFont, mText.c_str(), mColor);
	if (!surf) {
		SDL_Log("Failed to render text surface : %s", SDL_GetError());
		return;
	}
	
	mTexture = SDL_CreateTextureFromSurface(mOwner->GetGame()->GetRenderer(), surf);
	SDL_FreeSurface(surf);
}

//Draw
void TextComponent::Draw(SDL_Renderer* renderer) {
	if (mTexture) {
		int w, h;
		SDL_QueryTexture(mTexture, nullptr, nullptr, &w, &h);
		SDL_Rect rect = { static_cast<int>(mOwner->GetPosition().x),static_cast<int>(mOwner->GetPosition().y),w,h };
		SDL_RenderCopy(renderer, mTexture, nullptr, &rect);
	}
}