//
// Created by benedikt on 4/17/19.
//

#ifndef SDLTEST_CWINDOW_H
#define SDLTEST_CWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "CTexture.h"

class CWindow {
public:
    CWindow();
    int run(int width, int height);

public:
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();

    void setRender();
    void quit();

protected:
    virtual void OnInit() {}
    virtual void OnCleanup() {}
    virtual void OnThink() {}
    virtual void OnRender() {}
    virtual void OnKeyboardInput(SDL_KeyboardEvent *event) {}

private:
    bool init(int width, int height);
    void processEvent(SDL_Event *event);
    void cleanup();
    void keyboardInput(SDL_KeyboardEvent *event);
    void think();
    void render();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
    bool shouldRender;
};


#endif //SDLTEST_CWINDOW_H
