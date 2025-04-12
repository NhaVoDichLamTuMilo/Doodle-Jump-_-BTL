#ifndef _GAME_H
#include _GAME_H
#include <SDL.h>
#include "bot.h"
#include "platform.h"

const PLATFORM_NUM = 10;

class Game{
public:
    Game(); //khoi tao
    ~Game(); // delete

    bool init(const char* title, int width, int height);
    void run();
    void clean();

private:
    void handleEvents();
    void update(float deltaTime);
    void render();
    void reset();

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* botTexture; // load BOT
    SDL_Texture* platformTexture; // load PLatform
    bool isRunning;

    Bot bot;
    Platform platforms[PLATFORM_NUM];
    uint32_t lastTime; //for timing

};

#endif // _GAME_H
