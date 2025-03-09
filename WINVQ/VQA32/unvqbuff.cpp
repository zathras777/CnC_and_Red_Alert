#include <stdint.h>

#include "vqa32/unvq.h"

void UnVQ_4x2(unsigned char *codebook, unsigned char *pointers,
    unsigned char *buffer, unsigned long blocksperrow,
    unsigned long numrows, unsigned long bufwidth)
{
    // Compute the offset to the next row of blocks
    auto rowoffset = bufwidth * 2; 

    // Compute the end address of the pointer data
    auto entries = numrows * blocksperrow;
    auto data_end = pointers + entries;

    auto src_ptr = pointers;
    auto dst_ptr = buffer;
    auto dst_ptr_start = dst_ptr;

    // Drawing loop
    do
    {
        int count = blocksperrow; // Number of blocks in a line
        do
        {
            int v = *src_ptr;
            int cb = src_ptr[entries]; // Get the codebook pointer value
            src_ptr++;

            if(cb == 0xF) // Is it a one color block?
            {
                // Draw 1-color block
                uint32_t col32 = v | v << 8 | v << 16 | v << 24; // Duplicate colour
                *(uint32_t *)dst_ptr = col32; // Write 1st row to dest
                *(uint32_t *)(dst_ptr + bufwidth) = col32; // Write 2st row to dest
            }
            else
            {
                // Draw multi-color block
                int index = (cb << 8 | v) * 8;
                auto row1 = *(uint32_t *)(codebook + index); // Read 1st row of codeword
                auto row2 = *(uint32_t *)(codebook + index + 4); // Read 2nd row of codeword
                *(uint32_t *)dst_ptr = row1; // Write 1st row to dest
                *(uint32_t *)(dst_ptr + bufwidth) = row2; // Write 2st row to dest
            }

            // edi += 2;
            dst_ptr += 4;
        }
        while(--count);

        dst_ptr = dst_ptr_start + rowoffset;
        dst_ptr_start = dst_ptr;
    }
    while(src_ptr < data_end);
}