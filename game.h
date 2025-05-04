#ifndef _GAME_H
#define _GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "bot.h"
#include "menu.h"

#include "platform.h"

const int PLATFORM_NUM = 10;
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;


enum GameState{
  PLAYING,
  GAMEOVER
};


class Game{
public:
    Game(); //khoi tao
    ~Game(); // delete

    bool init(const char* title, int width, int height);
    void run();
    void clean();

private:
    void handleEvents(SDL_Event& event);
    void update(float deltaTime);
    void checkPlatformCollision(Bot& bot);
    void render();
    void reset();
    void resetGame();

    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    SDL_Texture* botTexture; // load BOT
    SDL_Texture* platformTexture; // load PLatform
    SDL_Texture* gameOverTexture;
    bool isRunning;

    Bot bot;
    Platform platforms[PLATFORM_NUM];
    uint32_t lastTime; //for timing

    int screenHeight;
    int screenWidth;

    GameState state;


    TTF_Font* font;
    SDL_Color textColor;
    SDL_Texture* restartTextTexture;
    SDL_Rect restartTextRect;

    Mix_Music* backgroundMusic;
    Mix_Chunk* jumpSound;
    Mix_Chunk* gameOverSound;

    float cameraY;

    Menu menu;
    bool inMenu = true;

};

#endif // _GAME_H
