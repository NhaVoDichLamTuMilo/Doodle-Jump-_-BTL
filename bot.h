#ifndef _BOT_H
#define _BOT_H

#include <SDL.h>

struct Bot{
  float x, y; // vtri
  float vx, vy; //van toc
  int width, height; // size
  SDL_Texture* texture ;// skin
  float cameraY;
  int screenHeight;
  bool isOnPlatform;

  bool update(float dt, int screenWidth, float cameraY, int screenHeight);//update vtri
  void render(SDL_Renderer* renderer, float cameraY);//render nvat
  void jump();//nhay
  SDL_Rect getRect() const;//lay hitbox
  void reset();//reset bot
};
#endif // _BOT_H
