#include "menu.h"
#include <iostream>

using namespace std;

Menu::Menu() : menuTexture(nullptr), playButtonTexture(nullptr), start(false){}

Menu::~Menu(){
    if (menuTexture){
        SDL_DestroyTexture(menuTexture);
    }
    if (playButtonTexture){
        SDL_DestroyTexture(playButtonTexture);
    }
}

bool Menu::init(SDL_Renderer* renderer, int screenWidth, int screenHeight){
    menuTexture = IMG_LoadTexture(renderer, "image/Menubg.png");
    if (!menuTexture){
        cout<<"Khong load duoc Menu "<<IMG_GetError()<<endl;
        return false;
    }

    playButtonTexture = IMG_LoadTexture(renderer, "image/playButton.png");
    if (!playButtonTexture){
        cout<<"Khong load duoc Button start "<<IMG_GetError()<<endl;
        return false;
    }

    playButtonRect = { screenWidth/2 - 100, screenHeight/2 - 40, 200, 80};
    return true;
}

void Menu::render(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, menuTexture, nullptr, nullptr);
    SDL_RenderCopy(renderer, playButtonTexture, nullptr, &playButtonRect);
}

bool Menu::handleEvent(SDL_Event& e){
    if (e.type == SDL_MOUSEBUTTONDOWN){
        int mx = e.button.x;
        int my = e.button.y;
        if (mx >= playButtonRect.x && mx <= playButtonRect.x + playButtonRect.w && my >= playButtonRect.y && my <= playButtonRect.y + playButtonRect.h){
            start = true;
            return true;
        }
    }
    return false;
}

bool Menu::StartGame() const{
    return start;
}
