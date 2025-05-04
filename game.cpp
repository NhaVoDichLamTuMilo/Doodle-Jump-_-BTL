#include "game.h"
#include "bot.h"
#include "platform.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

using namespace std;

Game::Game()
    : window(nullptr), renderer(nullptr),
      backgroundTexture(nullptr), botTexture(nullptr), platformTexture(nullptr),
      gameOverTexture(nullptr), restartTextTexture(nullptr),
      isRunning(false), lastTime(0),
      screenWidth(SCREEN_WIDTH), screenHeight(SCREEN_HEIGHT),
      state(PLAYING), cameraY(0.0f),
      inMenu(true), font(nullptr)
      {}

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return false;
    }

    //for img
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "IMG_Init Error: " << IMG_GetError() << endl;
        return false;
    }

    //for chu
    if (TTF_Init() == -1) {
        cout << "TTF_Init Error: " << TTF_GetError() << endl;
        return false;
    }

    //for sounds
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        cout<<"SDL_mixer error"<<Mix_GetError()<<endl;
        return false;
    }

    screenWidth = width;
    screenHeight = height;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "CreateWindow Error: " << SDL_GetError() << endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "CreateRenderer Error: " << SDL_GetError() << endl;
        return false;
    }

    if (!menu.init(renderer, screenWidth, screenHeight)){
        cout<<"Ko upload duoc Menu open"<<endl;
        return false;
    }

    inMenu = true;

    backgroundTexture = IMG_LoadTexture(renderer, "image/background.png");
    if (!backgroundTexture) {
        cout << "Load background error: " << IMG_GetError() << endl;
        return false;
    }

    SDL_Surface* surf = IMG_Load("image/JackBot.png");
    if (!surf) {
        cout << "Load bot error: " << IMG_GetError() << endl;
        return false;
    }
    botTexture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    surf = IMG_Load("image/green_platform.png");
    if (!surf) {
        cout << "Load platform error: " << IMG_GetError() << endl;
        return false;
    }
    platformTexture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    surf = IMG_Load("image/gameover.png");
    if (surf) {
        gameOverTexture = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    font = TTF_OpenFont("font/arial.ttf", 24);
    if (!font) {
        cout << "Load font error: " << TTF_GetError() << endl;
        return false;
    }

    backgroundMusic = Mix_LoadMUS("sound/backgroundMusic.mp3");
    if (!backgroundMusic){
        cout<<"Loi phat nhac nen"<<Mix_GetError()<<endl;
    }

    jumpSound = Mix_LoadWAV("sound/jump.mp3");
    gameOverSound = Mix_LoadWAV("sound/gameover.mp3");

    Mix_PlayMusic(backgroundMusic, -1);

    textColor = {255, 255, 255, 255};//render chu mau trang cho text cuoi

    bot.texture = botTexture;
    bot.width = 40;
    bot.height = 40;

    platforms[0].reset(50, screenHeight - 40, 60, 20);
    platforms[0].texture = platformTexture;

    bot.x = platforms[0].x + (platforms[0].width - bot.width) / 2;
    bot.y = platforms[0].y - bot.height;

    for (int i = 1; i < PLATFORM_NUM; ++i) {
        float x = static_cast<float>(rand() % (screenWidth - 60));
        float y = static_cast<float>(rand() % (screenHeight - 100));
        platforms[i].reset(x, y, 60, 20);
        platforms[i].texture = platformTexture;
    }

    isRunning = true;
    lastTime = SDL_GetTicks();
    return true;
}

void Game::run() {
    while (isRunning) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            handleEvents(event);
        }

        if (inMenu) {
            SDL_RenderClear(renderer);
            menu.render(renderer);
            SDL_RenderPresent(renderer);
        } else {
            update(deltaTime);
            render();
        }

        SDL_Delay(16); // Tương đương với 60 FPS
    }
}

void Game::handleEvents(SDL_Event& event) {
    const Uint8* keys = SDL_GetKeyboardState(NULL);


    //de click start
    if (inMenu){
    if (menu.handleEvent(event)){
        cout<<"Go"<<endl;
        inMenu = false;
        state = PLAYING;
    }
}

    if (event.type == SDL_KEYDOWN && state == GAMEOVER) {
        if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q) {
            isRunning = false;
        } else if (event.key.keysym.sym == SDLK_r) {
            resetGame();
        }
    }

    bot.vx = 0;
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) bot.vx = -200.0f;
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) bot.vx = 200.0f;
}

void Game::update(float dt) {
    if (state != PLAYING) return;

    bool fall = bot.update(dt, screenWidth, cameraY, screenHeight);
    bot.isOnPlatform = false;

    SDL_Rect botRect = bot.getRect();
    for (int i = 0; i < PLATFORM_NUM; ++i) {
        SDL_Rect platformRect = platforms[i].getRect();
        SDL_Rect intersection;
        if (SDL_IntersectRect(&botRect, &platformRect, &intersection)) {
            if (bot.vy > 0 && (bot.y + bot.height) <= (platforms[i].y + bot.vy)) {
                bot.jump();
                Mix_PlayChannel(-1, jumpSound, 0);
                bot.isOnPlatform = true;
            }
        }
    }

    float threshold = screenHeight / 3.0f;
    if (bot.y < threshold && bot.vy < 0) {
        float cameraSpeed = -bot.vy * dt;
        cameraY += cameraSpeed;

       float deltaY = threshold - bot.y;

        cameraY -= deltaY;//day camera len

        // Tạo lại platform khi chúng vượt khỏi màn hình
        for (int i = 0; i < PLATFORM_NUM; ++i) {
           platforms[i].y += cameraSpeed;

           if (platforms[i].y > screenHeight){
            platforms[i].y = cameraY - static_cast<float>(rand()%100 + 50);
            platforms[i].x = static_cast<float>(rand() % (screenWidth - platforms[i].width));
           }
    }
    bot.y = threshold;
    }


    if (fall) {
        Mix_PlayChannel(-1, gameOverSound, 0);
        state = GAMEOVER;
        cout << "Jack cook roi !" << endl;
    }
}

void Game::resetGame() {
    bot.reset();
    bot.x = platforms[0].x + (platforms[0].width - bot.width) / 2;
    bot.y = platforms[0].y - bot.height;

    for (int i = 0; i < PLATFORM_NUM; ++i) {
        float x = static_cast<float>(rand() % (screenWidth - 60));
        float y = static_cast<float>(rand() % (screenHeight - 100));
        platforms[i].reset(x, y, 60, 20);
        platforms[i].texture = platformTexture;
    }

    cameraY = 0.0f;
    state = PLAYING;
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 135, 200, 250, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    for (int i = 0; i < PLATFORM_NUM; ++i) {
        platforms[i].render(renderer, cameraY);
    }

    bot.render(renderer, cameraY);

    if (state == GAMEOVER) {
        if (gameOverTexture) {
            SDL_RenderCopy(renderer, gameOverTexture, NULL, NULL);
        }

        if (font) {
            SDL_Surface* textSurface = TTF_RenderText_Blended(font, "        Press R to Restart, Q to Quit", textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_Rect textRect = {50, screenHeight - 50, textSurface->w, textSurface->h};
            SDL_FreeSurface(textSurface);
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
    }
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(botTexture);
    SDL_DestroyTexture(platformTexture);
    SDL_DestroyTexture(gameOverTexture);
    if (restartTextTexture) SDL_DestroyTexture(restartTextTexture);
    TTF_CloseFont(font);
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(gameOverSound);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
