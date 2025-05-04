#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Menu{
public:
    Menu();
    ~Menu();

    bool init (SDL_Renderer* renderer, int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer);
    bool handleEvent(SDL_Event &e);
    bool StartGame() const;
    bool QuitGame() const;

private:
    SDL_Texture* menuTexture;
    SDL_Texture* playButtonTexture;
    SDL_Rect playButtonRect;

    bool start;
};
