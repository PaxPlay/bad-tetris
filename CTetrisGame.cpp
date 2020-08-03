//
// Created by benedikt on 4/18/19.
//

#include "CTetrisGame.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

void CTetrisGame::OnInit() {
    TTF_Init();
    baseTexture = new CTexture("../tetris.bmp", getRenderer());

    for (auto &column : occupied) {
        for (auto &field : column) {
            field = BACKGROUND;
        }
    }

    srand(time(nullptr));
    next = new CTetrisPawn(pawns[rand() % 7]);
    currentPawn = new CTetrisPawn(pawns[rand() % 7]);
    stepTime = 1000.0f;
    score = 0;

    font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 48);
    if (!font) {
        std::cout << SDL_GetError() << std::endl;
    }

    std::fstream file;
    file.open("highscore.dat", std::fstream::in | std::fstream::binary);
    if (file.good()) {
        file.read((char*)&highscore, sizeof(int));
        file.close();
    }
}

void CTetrisGame::OnCleanup() {
    if (score > highscore) {
        std::fstream file;
        file.open("highscore.dat", std::fstream::out | std::fstream::binary);
        if (file.good()) {
            file.write((char*)&score, sizeof(int));
            file.close();
        }
    }
    delete baseTexture;
    delete currentPawn;
    delete next;
    TTF_CloseFont(font);
}

void CTetrisGame::OnThink() {
    static int lastDrop = SDL_GetTicks();
    int current_tick = SDL_GetTicks();
    int elapsed = current_tick - lastDrop;

    auto *state = SDL_GetKeyboardState(nullptr);
    int threshold = (int)((state[SDL_SCANCODE_DOWN]) ? (stepTime / 4) : stepTime);
    if (elapsed > threshold) {
        if (currentPawn->canMoveDown(this)) {
            currentPawn->moveDown();
        } else {
            currentPawn->copyToArray(this);
            checkRows();
            *currentPawn = *next;
            *next = CTetrisPawn(pawns[rand() % 7]);
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
    next->drawIndicator(baseTexture);

    char sscore[256];
    char shscore[256];
    sprintf(sscore, "Score: %d", score);
    sprintf(shscore, "Highscore: %d", highscore);

    SDL_Color white = { 255, 255, 255 };
    SDL_Surface *surface = TTF_RenderText_Solid(font, sscore, white);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(getRenderer(), surface);

    SDL_Rect src = { 0, 0, BLOCK_SIZE * 16, BLOCK_SIZE * 4 };
    SDL_Rect dst = { BLOCK_SIZE * 13, BLOCK_SIZE * 10, BLOCK_SIZE * 4, BLOCK_SIZE * 1 };
    SDL_RenderCopy(getRenderer(), tex, &src, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(tex);

    surface = TTF_RenderText_Solid(font, shscore, white);
    tex = SDL_CreateTextureFromSurface(getRenderer(), surface);

    dst = { BLOCK_SIZE * 13, BLOCK_SIZE * 11, BLOCK_SIZE * 4, BLOCK_SIZE * 1 };
    SDL_RenderCopy(getRenderer(), tex, &src, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(tex);
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
    int count = 0;
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        if (isRowComplete(y)) {
            deleteRow(y);
            y--; // repeat this row since it got deleted
            count++;
        }
    }
    if (count > 0) {
        score += (int)((1000 / stepTime) * (float)(count * count));
        std::cout << "Score: " << score << std::endl;
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

    stepTime *= 0.95;
}

TetrisColor CTetrisGame::getField(size_t x, size_t y) const {
    return occupied[x][y];
}
