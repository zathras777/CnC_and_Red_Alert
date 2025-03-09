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
	// this one line doubles by skipping every other line
	auto old_dest = dest_ptr;

	auto interp_table_flat = (uint8_t *)PaletteInterpolationTable;

	do
	{
		int width_counter = 0;
		int pixel_count = (src_width - 2) / 2; // we copy two at a time, so this isn't actually a pixel count

		auto out_ptr = old_dest;

		// convert 2 pixels of source into 4 pixels of destination
		do
		{
			// read four pixels (we use three)
			auto in_pixels = *(uint32_t *)src_ptr;
			src_ptr += 2;

			auto interped = interp_table_flat[in_pixels & 0xFFFF];
			auto interped2 = interp_table_flat[(in_pixels >> 8) & 0xFFFF];
			
			auto out_pixels = (in_pixels & 0xFF) | interped << 8 | (in_pixels & 0xFF00) << 8 | interped2 << 24;

			*(uint32_t *)out_ptr = out_pixels;
			out_ptr += 4;

		}
		while(--pixel_count);

		// do the last three pixels and a blank
		auto in_pixels = *(uint16_t *)src_ptr;
		src_ptr += 2;
		*out_ptr++ = in_pixels & 0xFF;
		*out_ptr++ = interp_table_flat[in_pixels];
		*out_ptr++ = in_pixels >> 8;
		*out_ptr++ = 0;

		old_dest += dest_width; // skip every other line
	}
	while(--lines);
}

extern "C" void Asm_Interpolate_Line_Double(unsigned char* src_ptr, unsigned char* dest_ptr, int lines, int src_width, int dest_width)
{
	auto old_dest = dest_ptr;

	auto interp_table_flat = (uint8_t *)PaletteInterpolationTable;

	do
	{
		int width_counter = 0;
		int pixel_count = (src_width - 2) / 2; // we copy two at a time, so this isn't actually a pixel count

		auto out_ptr = old_dest;
		auto out2_ptr = old_dest + dest_width / 2; // dest width is 2x the actual width...

		// convert 2 pixels of source into 4 pixels of destination
		do
		{
			// read four pixels (we use three)
			auto in_pixels = *(uint32_t *)src_ptr;
			src_ptr += 2;

			auto interped = interp_table_flat[in_pixels & 0xFFFF];
			auto interped2 = interp_table_flat[(in_pixels >> 8) & 0xFFFF];
			
			auto out_pixels = (in_pixels & 0xFF) | interped << 8 | (in_pixels & 0xFF00) << 8 | interped2 << 24;

			*(uint32_t *)out_ptr = out_pixels;
			out_ptr += 4;
			*(uint32_t *)out2_ptr = out_pixels;
			out2_ptr += 4;
		}
		while(--pixel_count);

		// do the last three pixels and a blank
		auto in_pixels = *(uint16_t *)src_ptr;
		src_ptr += 2;
		*out_ptr++ = *out2_ptr++ = in_pixels & 0xFF;
		*out_ptr++ = *out2_ptr++ = interp_table_flat[in_pixels];
		*out_ptr++ = *out2_ptr++ = in_pixels >> 8;
		*out_ptr++ = *out2_ptr++ = 0;

		old_dest += dest_width;
	}
	while(--lines);
}

extern "C" void Asm_Interpolate_Line_Interpolate(unsigned char* src_ptr, unsigned char* dest_ptr, int lines, int src_width, int dest_width)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}
