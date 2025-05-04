#ifndef _DEFS__H
#define _DEFs__H

//cua so
#define SCREEN_WIDTH 550
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "Jack Jump"

//timing
#define FPS 60
#define FRAME_DELAY (1000 / FPS)

//nhan vat
#define BOT_WIDTH 50
#define BOT_HEIGHT 50
#define BOT_START_X (SCREEN_WIDTH/2)
#define BOT_START_Y (SCREEN_HEIGHT-100)
#define BOT_JUMP_SPEED -15
#define GRAVITY 0.5
#define MAX_FALL_SPEED 15

//platform
#define PLATFORM_WIDTH 60
#define PLATFORM_HEIGHT 12
#define PLATFORM_NUM 10

//img sound
#define BOT "image/JackBot.png"
#define BACKGROUND "image/background.png"
#define PLATFORM "image/green_platform.png"



#endif // _DEFS__H
