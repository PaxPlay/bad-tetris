//
// Created by benedikt on 4/18/19.
//

#include "CTetrisPawn.h"
#include "CTetrisGame.h"

CTetrisPawn::CTetrisPawn(TetrisColor color, std::initializer_list<Vector2D<int8_t>> blocks) : color(color), blocks(blocks), position(FIELD_WIDTH / 2, FIELD_HEIGHT - 2) {
}

void CTetrisPawn::tryRotate(bool right, const CTetrisGame *game) {
    static const Matrix2D<int8_t> rotateRight { 0, -1, 1, 0 };
    static const Matrix2D<int8_t> rotateLeft { 0, 1, -1, 0 };

    auto blocksCopy = blocks;
    for (auto &d : blocksCopy) {
        d = d * (right ? rotateRight : rotateLeft);
        auto pos = position + d;
        if (game->isOccupied(pos.x, pos.y)) {
            return;
        }
    }

    blocks = blocksCopy;
}

void CTetrisPawn::draw(CTexture *texture) const {
    draw(texture, position);
}

void CTetrisPawn::draw(CTexture *texture, Vector2D<int8_t> origin) const {
    for (auto &block : blocks) {
        Vector2D<int8_t> pos = origin + block;
        texture->draw(color, pos.x, pos.y);
    }
}

bool CTetrisPawn::canMoveDown(const CTetrisGame *game) const {
    for (auto &block : blocks) {
        Vector2D<int8_t> pos = position + block;
        if (pos.y == 0 || game->isOccupied(pos.x, pos.y - 1)) {
            return false;
        }
    }
    return true;
}

void CTetrisPawn::moveDown() {
    position.y -= 1;
}

void CTetrisPawn::copyToArray(CTetrisGame *game) const {
    for (auto &block : blocks) {
        Vector2D<int8_t> pos = position + block;
        game->setField(pos.x, pos.y, color);
    }
}

bool CTetrisPawn::canMoveSideways(const CTetrisGame *game, bool right) const {
    for (auto &block : blocks) {
        Vector2D<int8_t> pos = position + block + (right ? Vector2D<int8_t>(1, 0) : Vector2D<int8_t>(-1, 0));
        if (pos.x < 0 || pos.x >= FIELD_WIDTH || game->isOccupied(pos.x, pos.y)) {
            return false;
        }
    }
    return true;
}

void CTetrisPawn::moveSideways(bool right) {
    position.x += (right ? 1 : -1);
}

bool CTetrisPawn::collides(const CTetrisGame *game) const {
    for (auto &d : blocks) {
       auto pos = position + d;
       if (game->isOccupied(pos.x, pos.y)) {
           return true;
       }
    }
    return false;
}

const CTetrisPawn pawns[7] = {
        { LIGHTBLUE, {
            { -2, 0 }, { -1, 0 }, { 0, 0 }, { 1, 0 }
        } },
        { BLUE, {
            { -1, 1 }, { -1, 0 }, { 0, 0 }, { 1, 0 }
        } },
        { ORANGE, {
            { -1, 0 }, { 0, 0 }, { 1, 0 }, { 1, 1 }
        } },
        { YELLOW, {
            { 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 0 }
        } },
        { GREEN, {
            { -1, 0 }, { 0, 0 }, { 0, 1 }, { 1, 1 }
        } },
        { RED, {
            { -1, 1 }, { 0, 1 }, { 0, 0 }, { 1, 0 }
        } },
        { PURPLE, {
            { -1, 0 }, { 0, 0 }, { 0, 1 }, { 1, 0 }
        } }
};