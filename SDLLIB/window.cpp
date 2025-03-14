#include <stdio.h>

#include <SDL.h>

#include "ww_win.h"
#include "net_select.h"
#include "gbuffer.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

unsigned int WinX;
unsigned int WinY;
unsigned int Window;

SDL_Renderer *SDLRenderer;
Uint32 ForceRenderEventID;

int Change_Window(int windnum)
{
    printf("%s\n", __func__);
    return 0;
}

void SDL_Create_Main_Window(const char *title, int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    MainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    ForceRenderEventID = SDL_RegisterEvents(1);

    SDLRenderer = SDL_CreateRenderer((SDL_Window *)MainWindow, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderSetLogicalSize(SDLRenderer, width, height);
    SDL_RenderSetIntegerScale(SDLRenderer, SDL_TRUE);

    // sometimes the window won't be created until it has content
    // so we get stuck waiting for focus, which it'll never get because it doesn't exist
    SDL_RenderClear(SDLRenderer);
    SDL_RenderPresent(SDLRenderer);
}

void SDL_Event_Loop()
{
#ifdef __EMSCRIPTEN__
    // sometimes we loop waiting for input
    // which isn't going to happen if the browser never gets control
    emscripten_sleep(0);
#endif

    // this is replacing WSAAsyncSelect, which would send through the windows event loop
    Socket_Select();

    SDL_Event event;
	while(SDL_PollEvent(&event))
    {
        if(event.type == ForceRenderEventID)
        {
            Video_End_Frame();
            continue;
        }
		SDL_Event_Handler(&event);
	}
}

void SDL_Send_Quit()
{
    SDL_Event quit_event;
    quit_event.type = SDL_QUIT;
    SDL_PushEvent(&quit_event);
}