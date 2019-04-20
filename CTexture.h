//
// Created by benedikt on 4/18/19.
//

#ifndef SDLTEST_CTEXTURE_H
#define SDLTEST_CTEXTURE_H

#include <SDL2/SDL.h>

class CTexture {
public:
    CTexture(const char *file, SDL_Renderer *renderer);
    ~CTexture();

    void draw(int x, int y, int w, int h);
    void draw(int textureIndex, int x, int y);
private:
    SDL_Texture *texture;
    SDL_Renderer *renderer;
};


#endif //SDLTEST_CTEXTURE_H
