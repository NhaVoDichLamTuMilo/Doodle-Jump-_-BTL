#include "platform.h"
#include <SDL.h>

void Platform::render(SDL_Renderer* renderer){
   SDL_Rect dst = { static_cast<int>(x),static_cast<int>(y), width, height};
   SDL_RenderCopy(render,texture, NULL, &dst);
}

void Platform::reset(float newX, float newY, int w, int h){
  x = newX; // x moi
  y = newY; // y moi
  //update vi tri moi cua platform

  width = (w > 0 ) ? w : 60;
  height = (h > 0) ? h : 20;
}
