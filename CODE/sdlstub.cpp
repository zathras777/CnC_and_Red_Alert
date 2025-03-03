// more portable replacements for winstub

#include "function.h"

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


void Create_Main_Window(HANDLE instance, int command_show, int width, int height)
{
	printf("%s\n", __PRETTY_FUNCTION__);

	//Audio_Focus_Loss_Function = &Focus_Loss;
	Misc_Focus_Loss_Function = &Focus_Loss;
	Misc_Focus_Restore_Function = &Focus_Restore;
	//Gbuffer_Focus_Loss_Function = &Focus_Loss;
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

// this is in 2keyfbuf.asm
long Buffer_Frame_To_Page(int x, int y, int w, int h, void *Buffer, GraphicViewPortClass &view, int flags, ...)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	return 0;
}
