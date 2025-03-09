// don't need much from VQM32, and it's all asm
#include <stdio.h>

#include "vqm32/compress.h"
#include "vqm32/soscomp.h"

long AudioUnzap(void *source, void *dest, long)
{
    printf("%s\n", __func__);
    return 0;
}

void VQA_sosCODECInitStream(_SOS_COMPRESS_INFO *)
{
    printf("%s\n", __func__);
}

unsigned long VQA_sosCODECDecompressData(_SOS_COMPRESS_INFO *,unsigned long)
{
    printf("%s\n", __func__);
    return 0;
}
