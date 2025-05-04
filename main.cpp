
#include "game.h"
#include "defs.h"
using namespace std;

int main(int argc, char *argv[]){
  Game game;

  if (game.init(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT)){
    game.run();
  }
  return 0;
}
/*
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Test", 100, 100, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture* tex = IMG_LoadTexture(renderer, "image.png");
    if (!tex) {
        std::cout << "IMG_LoadTexture failed: " << IMG_GetError() << std::endl;
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
*/

