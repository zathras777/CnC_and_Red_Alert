#include <stdio.h>

#include "../WINVQ/INCLUDE/vqa32/vqaplay.h"

void VQA_DefaultConfig(VQAConfig *config)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

VQAHandle *VQA_Alloc(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

void VQA_Free(VQAHandle *vqa)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

void VQA_Init(VQAHandle *vqa, long(*iohandler)(VQAHandle *vqa, long action, void *buffer, long nbytes))
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

long VQA_Open(VQAHandle *vqa, char const *filename, VQAConfig *config)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void VQA_Close(VQAHandle *vqa)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

long VQA_Play(VQAHandle *vqa, long mode)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void VQA_PauseAudio(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
}