//
// Created by benedikt on 4/17/19.
//

#include <iostream>
#include "CWindow.h"

CWindow::CWindow() : shouldRender(true), running(true) {
}

int CWindow::run(int width, int height) {
    if (!init(width, height)) {
        return -1;
    }

    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            processEvent(&event);
        }

        SDL_Delay(5);

        think();

        if (shouldRender) {
            render();
            shouldRender = false;
        }
    }

    cleanup();
    return 0;
}

bool CWindow::init(int width, int height) {
    window = SDL_CreateWindow("Window title.", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (!window) {
        return false;
    }

    //renderer = SDL_GetRenderer(window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

    OnInit();

    return true;
}

void CWindow::processEvent(SDL_Event *event) {
    SDL_KeyboardEvent keyboardEvent;
    switch (event->type) {
        case SDL_KEYDOWN: case SDL_KEYUP:
            keyboardInput(&event->key);
            break;

        case SDL_QUIT:
            running = false;
    }
}

void CWindow::cleanup() {
    OnCleanup();
    SDL_Quit();
}

void CWindow::think() {
    OnThink();
}

void CWindow::render() {
    SDL_RenderClear(renderer);
    OnRender();
    SDL_RenderPresent(renderer);
}

void CWindow::keyboardInput(SDL_KeyboardEvent *event) {
    OnKeyboardInput(event);
}

SDL_Window *CWindow::getWindow() {
    return window;
}

SDL_Renderer *CWindow::getRenderer() {
    return renderer;
}

void CWindow::setRender() {
    shouldRender = true;
}

void CWindow::quit() {
    running = false;

}
