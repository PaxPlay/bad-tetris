//
// Created by benedikt on 4/18/19.
//

#include "CTexture.h"
#include "CTetrisGame.h"

#include <iostream>

CTexture::CTexture(const char *file, SDL_Renderer *renderer) : renderer(renderer) {
    SDL_Surface *tmp = SDL_LoadBMP(file);

    if (!tmp) {
        std::cout << SDL_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    if (!texture) {
        std::cout << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(tmp);
}

CTexture::~CTexture() {
    SDL_DestroyTexture(texture);
}

void CTexture::draw(int x, int y, int w, int h) {
    SDL_Rect dst = { x, y, w, h };
    if (SDL_RenderCopy(renderer, texture, nullptr, &dst)) {
        std::cout << SDL_GetError() << std::endl;
    }
}

void CTexture::draw(int textureIndex, int x, int y) {
    SDL_Rect src = { textureIndex * 16, 0, 16, 16 };
    SDL_Rect dst = { x * BLOCK_SIZE, (FIELD_HEIGHT - y - 1) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE };
    if (SDL_RenderCopy(renderer, texture, &src, &dst)) {
        std::cout << SDL_GetError() << std::endl;
    }
}
