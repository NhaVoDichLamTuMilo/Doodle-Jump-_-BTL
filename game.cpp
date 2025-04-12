#include "game.h"
#include "bot.h"
#include "platform.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

Game::Game() : window(nullptr), renderer(nullptr), playerTexture(nullptr), isRunning(false), lasTime(0){}

Game::Game(){
  clean();
}

bool Game::init(const* char title, int width, int height){
  if (SDL_Init(SDL_INIT_VIDEO) < 0){
    cout<<"Loi khoi chay SDL"<<SDL_GetError<<endl;
    return false;
  }


}
