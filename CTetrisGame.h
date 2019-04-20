//
// Created by benedikt on 4/18/19.
//

#ifndef SDLTEST_CTETRISGAME_H
#define SDLTEST_CTETRISGAME_H

#include "CWindow.h"
#include "CTexture.h"
#include "CTetrisPawn.h"

#define FIELD_WIDTH 12
#define FIELD_HEIGHT 20
#define BLOCK_SIZE 24

class CTetrisGame : public CWindow {
public:
    bool isOccupied(size_t x, size_t y) const;
    void setField(size_t x, size_t y, TetrisColor color);
    TetrisColor getField(size_t x, size_t y) const;

protected:
    void OnInit() override;
    void OnCleanup() override;
    void OnThink() override;
    void OnRender() override;
    void OnKeyboardInput(SDL_KeyboardEvent *event) override;

private:
    void checkRows();
    bool isRowComplete(int y);
    void deleteRow(int row);
private:
    CTexture *baseTexture;
    TetrisColor occupied[FIELD_WIDTH][FIELD_HEIGHT];
    CTetrisPawn *currentPawn;
};


#endif //SDLTEST_CTETRISGAME_H
