// more portable replacements for winstub

#include "function.h"

#include "ww_win.h"

#include <SDL.h> // sdl includes leaking into the rest of the code is bad

void Focus_Loss(void);
void Focus_Restore(void);

void WWDebugString (char *string)
{}

void Check_For_Focus_Loss(void)
{}

void Memory_Error_Handler(void)
{
	VisiblePage.Clear();
	CCPalette.Set();
	while (Get_Mouse_State()) {Show_Mouse();};
	WWMessageBox().Process(TEXT_MEMORY_ERROR, TEXT_ABORT);

	ReadyToQuit = 1;

	do
	{
		Keyboard->Check();
	}while (ReadyToQuit == 1);

	exit(0);
}


#if (ENGLISH)
#define WINDOW_NAME		"Red Alert"
#endif

#if (FRENCH)
#define WINDOW_NAME		"Alerte Rouge"
#endif

#if (GERMAN)
#define WINDOW_NAME		"Alarmstufe Rot"
#endif

void Create_Main_Window(HANDLE instance, int command_show, int width, int height)
{
	SDL_Create_Main_Window(WINDOW_NAME, width, height);

	//Audio_Focus_Loss_Function = &Focus_Loss;
	Misc_Focus_Loss_Function = &Focus_Loss;
	Misc_Focus_Restore_Function = &Focus_Restore;
	//Gbuffer_Focus_Loss_Function = &Focus_Loss;
}

void SDL_Event_Handler(SDL_Event *event)
{
	if(Keyboard->Event_Handler(event))
		return;

	switch(event->type)
	{
		case SDL_WINDOWEVENT:
		{
			switch(event->window.event)
			{
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					GameInFocus = true;
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					GameInFocus = false;
					break;
			}
			break;
		}
		case SDL_QUIT:
			Prog_End();
			VisiblePage.Un_Init();
			HiddenPage.Un_Init();

			exit(0);
			break;
	}
}

// these are in winasm.asm
extern "C" void ModeX_Blit(GraphicBufferClass * source)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}

extern "C" void Asm_Interpolate(unsigned char* src_ptr, unsigned char* dest_ptr, int lines, int src_width, int dest_width)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}

extern "C" void Asm_Interpolate_Line_Double(unsigned char* src_ptr, unsigned char* dest_ptr, int lines, int src_width, int dest_width)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}

extern "C" void Asm_Interpolate_Line_Interpolate(unsigned char* src_ptr, unsigned char* dest_ptr, int lines, int src_width, int dest_width)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}
