#include <stdio.h>

#include <SDL.h>

#include "ww_win.h"
#include "gbuffer.h"

unsigned int WinX;
unsigned int WinY;
unsigned int Window;

int Change_Window(int windnum)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void SDL_Create_Main_Window(const char *title, int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);

    MainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    
    // sometimes the window won't be created until it has content
    // so we get stuck waiting for focus, which it'll never get because it doesn't exist
	SDL_GetWindowSurface((SDL_Window *)MainWindow);
	SDL_UpdateWindowSurface((SDL_Window *)MainWindow);
}

void SDL_Event_Loop()
{
    SDL_Event event;
	while(SDL_PollEvent(&event)) {
		SDL_Event_Handler(&event);
	}
}