#include "CTetrisGame.h"

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);

    CTetrisGame game = CTetrisGame();
    return game.run(FIELD_WIDTH * BLOCK_SIZE, FIELD_HEIGHT * BLOCK_SIZE);
}