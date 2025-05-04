#include "bot.h"

// Các hằng số vật lý
static constexpr float GRAVITY = 600.0f;      // Trọng lực
static constexpr float JUMP_V = -500.0f;      // Vận tốc nhảy
static constexpr float MAX_FALL = 500.0f;     // Vận tốc rơi tối đa
static constexpr float FLOOR_Y = 600.0f;      // Giới hạn dưới màn hình

bool Bot::update(float dt, int screenWidth, float cameraY, int screenHeight) {
    // Áp dụng trọng lực vào vận tốc rơi (vy)
    vy += GRAVITY * dt;
    if (vy > MAX_FALL) vy = MAX_FALL;

    // Cập nhật vị trí của bot
    x += vx * dt;
    y += vy * dt;

    if (y - cameraY > screenHeight){
        return true;
    }

  /*  // Nếu bot rơi ra ngoài màn hình, trả về true để game xử lý
    if (y > FLOOR_Y) {
        return true;
    } */

    // Nếu bot ra khỏi giới hạn trái/phải màn hình, quay lại phía đối diện
    if (x < 0) {
        x = 0;
    } else if (x + width > screenWidth) {
        x = screenWidth - width;
    }

    return false;
}

void Bot::render(SDL_Renderer* renderer, float cameraY) {
    SDL_Rect dst = {
        static_cast<int>(x),
        static_cast<int>(y - cameraY),
        width,
        height
    };
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void Bot::jump() {
    vy = JUMP_V;
}

SDL_Rect Bot::getRect() const {
    return SDL_Rect{
        static_cast<int>(x),
        static_cast<int>(y),
        width, height
    };
}

void Bot::reset() {
    x = 200.0f;
    y = 500.0f;
    vx = 0.0f;
    vy = 0.0f;
    width = 40;
    height = 40;
    isOnPlatform = false;
}
