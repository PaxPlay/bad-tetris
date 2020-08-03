//
// Created by benedikt on 4/18/19.
//

#ifndef SDLTEST_CTETRISPAWN_H
#define SDLTEST_CTETRISPAWN_H

#include <cstdint>
#include <list>

#include "Vector2D.h"
#include "CTexture.h"

class CTetrisGame;

enum TetrisColor {
    LIGHTBLUE,
    BLUE,
    ORANGE,
    YELLOW,
    GREEN,
    RED,
    PURPLE,
    BACKGROUND
};

class CTetrisPawn {
public:
    CTetrisPawn(TetrisColor color, std::initializer_list<Vector2D<int8_t>> blocks);
    CTetrisPawn(const CTetrisPawn& obj) = default;

    void tryRotate(bool right, const CTetrisGame *game);

    void draw(CTexture *texture) const;
    void draw(CTexture *texture, Vector2D<int8_t> origin) const;
    void drawIndicator(CTexture *texture) const;

    bool canMoveDown(const CTetrisGame *game) const;
    bool canMoveSideways(const CTetrisGame *game, bool right) const;
    void moveDown();
    void moveSideways(bool right);

    void copyToArray(CTetrisGame *game) const;

    bool collides(const CTetrisGame *game) const;
private:
    std::list<Vector2D<int8_t>> blocks;
    Vector2D<int8_t> position;
    TetrisColor color;
};

extern const CTetrisPawn pawns[7];


#endif //SDLTEST_CTETRISPAWN_H
