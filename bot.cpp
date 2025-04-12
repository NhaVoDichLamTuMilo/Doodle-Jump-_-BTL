#include "bot.h"

const float GRAVITY = 750.0f;
const float JUMP_V = -500.0f;

void Bot::update(float dt){
  vy += GRAVITY*dt;
  y += vy*dt;
  x += vx*dt;
}
void Bot::render(SDL_Renderer* renderer){
  SDL_Rect dst = { static_cast<int>(x), static_cast<int>(y), width, heigth };
  SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void Bot::jump(){
  vy = JUMP_V;
}

SDL_Rect Bot::getRect() const{
  return { static_cast<int>(x), static_cast<int>(y), width, height };
}

void Bot::reset(){
  x = 100;
  y = 500;
  vx = 0;
  vy = 0;
}
