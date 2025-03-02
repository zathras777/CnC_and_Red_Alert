#include "wsa.h"

void *Open_Animation(char const *file_name, char *user_buffer, long user_buffer_size, WSAOpenType user_flags, unsigned char *palette)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

void Close_Animation(void *handle)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

bool Animate_Frame(void *handle, GraphicViewPortClass& view, int frame_number, int x_pixel, int y_pixel,
    WSAType flags_and_prio, void *magic_cols, void *magic)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return false;
}

int Get_Animation_Frame_Count(void *handle)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

unsigned int Apply_XOR_Delta(char *source_ptr, char *delta_ptr)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}