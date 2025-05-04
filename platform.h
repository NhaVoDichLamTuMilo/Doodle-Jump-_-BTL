#ifndef _PLATFORM_H
#define _PLATFORM_H
#include <SDL.h>
#include <SDL_image.h>

struct Platform{
  float x,y;
  int width, height;
  SDL_Texture* texture;

  void render(SDL_Renderer* renderer, float cameraY);
  SDL_Rect getRect() const;
  void reset(float newX, float newY, int w = 60, int h = 20);
};

#endif // _PLATFORM_H
