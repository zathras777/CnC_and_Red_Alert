#include <stdio.h>

#include <SDL.h>

#include "ww_win.h"
#include "gbuffer.h"

unsigned int WinX;
unsigned int WinY;
unsigned int Window;

SDL_Renderer *SDLRenderer;

int Change_Window(int windnum)
{
    printf("%s\n", __func__);
    return 0;
}

void SDL_Create_Main_Window(const char *title, int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    MainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    SDLRenderer = SDL_CreateRenderer((SDL_Window *)MainWindow, -1, 0);

    SDL_RenderSetLogicalSize(SDLRenderer, width, height);
    SDL_RenderSetIntegerScale(SDLRenderer, SDL_TRUE);

    // sometimes the window won't be created until it has content
    // so we get stuck waiting for focus, which it'll never get because it doesn't exist
    SDL_RenderClear(SDLRenderer);
    SDL_RenderPresent(SDLRenderer);
}

void SDL_Event_Loop()
{
    SDL_Event event;
	while(SDL_PollEvent(&event)) {
		SDL_Event_Handler(&event);
	}
}

void SDL_Send_Quit()
{
    SDL_Event quit_event;
    quit_event.type = SDL_QUIT;
    SDL_PushEvent(&quit_event);
}