// platform.cpp
#include "platform.h"

void Platform::render(SDL_Renderer* renderer, float cameraY) {
    SDL_Rect dst;
    dst.x = static_cast<int>(x);
    dst.y = static_cast<int>(y - cameraY) ;
    dst.w = width;
    dst.h = height;
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

SDL_Rect Platform::getRect() const {
    return SDL_Rect{
        static_cast<int>(x),
        static_cast<int>(y),
        width,
        height
    };
}

void Platform::reset(float newX, float newY, int w, int h) {
    x = newX;
    y = newY;
    width  = w;
    height = h;
    // texture giữ nguyên (được gán ở Game::init)
}
