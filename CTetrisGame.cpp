//
// Created by benedikt on 4/18/19.
//

#include "CTetrisGame.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

void CTetrisGame::OnInit() {
    baseTexture = new CTexture("../tetris.bmp", getRenderer());

    for (auto &column : occupied) {
        for (auto &field : column) {
            field = BACKGROUND;
        }
    }

    srand(time(nullptr));
    currentPawn = new CTetrisPawn(pawns[rand() % 7]);
}

void CTetrisGame::OnCleanup() {
    delete baseTexture;
    delete currentPawn;
}

#define LIMIT 1000
void CTetrisGame::OnThink() {
    static int lastDrop = SDL_GetTicks();
    int current_tick = SDL_GetTicks();
    int elapsed = current_tick - lastDrop;
    if (elapsed > LIMIT) {
        if (currentPawn->canMoveDown(this)) {
            currentPawn->moveDown();
        } else {
            currentPawn->copyToArray(this);
            checkRows();
            *currentPawn = CTetrisPawn(pawns[rand() % 7]);
            if (currentPawn->collides(this)) {
                quit();
            }
        }
        lastDrop = current_tick;
        setRender();
    }

}

void CTetrisGame::OnRender() {
    /*
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 20; j++) {
            baseTexture->draw((i + (j * 12)) % 7, i, j);
        }
    }
     */
    SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0x00, 0xff);
    SDL_RenderFillRect(getRenderer(), nullptr);

    SDL_SetRenderDrawColor(getRenderer(), 0x20, 0x20, 0x20, 0xff);
    SDL_Rect bg = { 0, 0, FIELD_WIDTH * BLOCK_SIZE, FIELD_HEIGHT * BLOCK_SIZE };
    SDL_RenderFillRect(getRenderer(), &bg);

    for (int i = 0; i < FIELD_WIDTH; i++) {
        for (int j = 0; j < FIELD_HEIGHT; j++) {
            baseTexture->draw(occupied[i][j], i, j);
        }
    }

    currentPawn->draw(baseTexture);
}

bool CTetrisGame::isOccupied(size_t x, size_t y) const {
    if (x > FIELD_WIDTH || y > FIELD_HEIGHT) {
        return true;
    }
    return occupied[x][y] != BACKGROUND;
}

void CTetrisGame::setField(size_t x, size_t y, TetrisColor color) {
    occupied[x][y] = color;
}

void CTetrisGame::OnKeyboardInput(SDL_KeyboardEvent *event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->keysym.sym) {
        case SDLK_RIGHT: case SDLK_d:
            if (currentPawn->canMoveSideways(this, true)) {
                currentPawn->moveSideways(true);
            }
            break;
        case SDLK_LEFT: case SDLK_a:
            if (currentPawn->canMoveSideways(this, false)) {
                currentPawn->moveSideways(false);
            }
            break;
        case SDLK_UP: case SDLK_w:
            currentPawn->tryRotate(true, this);
            break;
        case SDLK_SPACE:
            while (currentPawn->canMoveDown(this)) {
                currentPawn->moveDown();
            }
            setRender();
            break;
        default:
            return;
        }
        setRender();
    }
}

void CTetrisGame::checkRows() {
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        if (isRowComplete(y)) {
            deleteRow(y);
            y--; // repeat this row since it got deleted
        }
    }
}

bool CTetrisGame::isRowComplete(int y) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
        if (!isOccupied(x, y)) {
            return false;
        }
    }

    return true;
}

void CTetrisGame::deleteRow(int row) {
    for (int y = row; y < (FIELD_HEIGHT - 1); y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            setField(x, y, getField(x, y + 1));
        }
    }
}

TetrisColor CTetrisGame::getField(size_t x, size_t y) const {
    return occupied[x][y];
}
