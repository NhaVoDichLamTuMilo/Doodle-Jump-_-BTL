#include "menu.h"
#include <sdl_image.h>

bool showMenu(SDL_Renderer*renderer) {
  SDL_Texture* playButton = IMG_LoadTexture(renderer, "image//buttonplay.png")
  SDL_Texture* exitButton = IMG_LoadTexture(renderer, "image//exitbutton.png")

  //check out nut
  if (!playButton || !exitButton){
    SDL_Log("Failed to load button images: %s", SDL_GetError());
    return false;
  }

  SDL_Rect playRect = {500,300,300,100};
  SDL_Rect exitRect = {500,300,300,100};

  SDL_Event e;
  bool running = true;

  int w, h;
  while (running){
    while (SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT) return false;
        if (e.type == SDL_MOUSEBUTTONDOWN){
            int x = e.button.x;
            int y = e.button.y;

            if (x >= play.Rect.x && x <= play.Rect.x + playRect.w && y >= play.Rect.y && y <= play.Rect.y + play.Rect.h){
                SDL_DestroyTexture(playButton);
                SDL_DestroyTexture(exitButton);
                return true; //bam play
            }
            if (x >= exit.Rect.x && x <= exit.Rect.x + exitRect.w && y >= exit.Rect.y && y <= exit.Rect.y + exit.Rect.h){
                SDL_DestroyTexture(playButton);
                SDL_DestroyTexture(exitButton);
                return true; //bam exit
            }
        }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, playButton, NULL, &playRect);
    SDL_RenderCopy(renderer, exitButton, NULL, &exitRect);
  }
  SDL_DestroyTexture(playButton);
  SDL_DestroyTexture(exitButton);
  return false;
}
