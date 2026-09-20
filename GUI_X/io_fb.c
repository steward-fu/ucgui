#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <linux/fb.h>

#include "io_fb.h"
#include "LCDConf.h"
#include "GUIConf.h"
#include "GUI_Protected.h"

#if GUI_SDLSUPPORT
#include <SDL.h>

static int running = 0;
static pthread_t thread_id = 0;
static SDL_Surface *screen = NULL;
#else
static unsigned short *pixels = NULL;
#endif

#if GUI_SDLSUPPORT
static void* input_handler(void *param)
{
    SDL_Event event = { 0 };
    GUI_PID_STATE st = { 0 };

    running = 1;
    while (running) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                GUI_StoreKeyMsg(event.key.keysym.sym, 1);
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&st.x, &st.y);
                GUI_MOUSE_StoreState(&st);
                break;
            case SDL_MOUSEBUTTONUP:
                SDL_GetMouseState(&st.x, &st.y);
                st.Pressed = 0;
                GUI_MOUSE_StoreState(&st);

                GUI_TOUCH_StoreState(st.x, st.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&st.x, &st.y);
                st.Pressed = 1;
                GUI_MOUSE_StoreState(&st);

                GUI_TOUCH_StoreState(st.x, st.y);
                break;
            }
        }
        usleep(1000000 / 30);
    }

    return NULL;
}
#endif

void* fb_getbuffer(void)
{
#if GUI_SDLSUPPORT
    return screen->pixels;
#else
    return pixels;
#endif
}

int fb_init(void)
{
#if GUI_SDLSUPPORT
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(LCD_XSIZE, LCD_YSIZE, 16, SDL_SWSURFACE);
    SDL_ShowCursor(0);
    pthread_create(&thread_id, NULL, input_handler, NULL);
#else
    pixels = malloc(LCD_XSIZE * LCD_YSIZE * 2);
#endif

    return 0;
}

void fb_deinit(void)
{
#if GUI_SDLSUPPORT
    running = 0;
    pthread_join(thread_id, NULL);
    SDL_Quit();
#else
    if (pixels) {
        free(pixels);
        pixels = NULL;
    }
#endif
}

void fb_flip(void)
{
#if GUI_SDLSUPPORT
    SDL_Flip(screen);
#endif
}

int fb_setpixel(int width, int height, int x, int y, unsigned short color)
{
    if ((x > width) || (y > height)) {
        return -1;
    }

#if GUI_SDLSUPPORT
    unsigned short *dst = ((unsigned short *)screen->pixels + y * width + x);
    *dst = color;
#else
    unsigned short *dst = ((unsigned short *)pixels + y * width + x);
    *dst = color;
#endif

    return 0;
}

unsigned short fb_readpixel(int width, int height, int x, int y)
{
    if ((x > width) || (y > height)) {
        return -1;
    }

#if GUI_SDLSUPPORT
    unsigned short *dst = ((unsigned short *)screen->pixels + y * width + x);
    return *dst;
#else
    unsigned short *dst = ((unsigned short *)pixels + y * width + x);
    return *dst;
#endif

    return 0;
}

