// re-implemented from assembly in 2keyfbuf.asm
#include "function.h"

// should match 2keyfram.cpp
struct ShapeHeaderType
{
	unsigned draw_flags; // only 16 bits used
	char *shape_data; // really an offset
	int shape_buffer; // 0 or 1
};

enum BlitFlags
{
	BLIT_TRANSPARENT = 1,
	BLIT_GHOST = 2,
	BLIT_FADING = 4,
	BLIT_PREDATOR = 8,

	BLIT_SKIP = 16,

	BLIT_OLD = BLIT_TRANSPARENT | BLIT_GHOST | BLIT_FADING | BLIT_PREDATOR, // the first four, used for "old" draw
	BLIT_ALL = BLIT_TRANSPARENT | BLIT_GHOST | BLIT_FADING | BLIT_PREDATOR | BLIT_SKIP
};

// the one in jshell isn't const enough
inline constexpr BlitFlags operator |(BlitFlags t1, BlitFlags t2)
{
	return((BlitFlags)((int)t1 | (int)t2));
}

#define PRED_MASK 0xE

extern "C" bool UseOldShapeDraw;
extern "C" char *BigShapeBufferStart;
extern "C" char	*TheaterShapeBufferStart;
extern "C" bool	UseBigShapeBuffer;

static int BFPredOffset;
static int BFPartialCount;
static int BFPartialPred;
static int16_t BFPredNegTable[]
{
	-1, -3, -2, -5, -2, -4, -3, -1,
	// calculated
	0, 0, 0, 0, 0, 0, 0, 0
};

// copied from blit funcs
inline int Make_Code(int x, int y, int w, int h)
{
    return (x < 0 ? 0b1000 : 0) | (x >= w ? 0b0100 : 0) | (y < 0 ? 0b0010 : 0) | (y >= h ? 0b0001 : 0);
}

static void Setup_Shape_Header(int pixel_width, int pixel_height, char *src, ShapeHeaderType *headers, uint flags, uint8_t *Translucent, uint8_t *IsTranslucent)
{
	headers->draw_flags = flags & (SHAPE_TRANS | SHAPE_FADING | SHAPE_PREDATOR | SHAPE_GHOST);
	auto ptr = (uint8_t *)headers + sizeof(ShapeHeaderType);
	do
	{
		int line_flags = 0;
		int trans_count = 0;
		int x_count = pixel_width;
		do
		{
			int pixel = *src;
			src = src + 1;
			if(!pixel && (flags & SHAPE_TRANS))
			{
				line_flags = BLIT_TRANSPARENT;
				trans_count++; // keep track of number of transparent pixels
			}
			else
			{
				if(flags & SHAPE_PREDATOR)
					line_flags |= BLIT_PREDATOR;

				if((flags & SHAPE_GHOST) && IsTranslucent[pixel] != 0xFF)
					line_flags |= BLIT_GHOST;

				if(flags & SHAPE_FADING)
					line_flags |= BLIT_FADING;
			}
		}
		while(--x_count);

		// all pixels in the line were transparent so we dont need to draw it at all
		if((line_flags & BLIT_TRANSPARENT) && trans_count == pixel_width)
			line_flags = BLIT_SKIP;

		*ptr++ = line_flags;
	} while (--pixel_height != 0);
}

// single helper that handles all combinations
// templated on flags to avoid writing every combination
template<int flags>
inline void Do_Old_Blit(int line_count, int pixel_count, uint8_t *src_offset, uint8_t *dst_offset, int src_adjust_width, int dst_adjust_width,
    uint8_t *Translucent, uint8_t *IsTranslucent, int FadingNum, uint8_t *FadingTable)
{
    do
    {
        // original asm unrolled this 32 times
        for(int x = 0; x < pixel_count; x++)
        {
            uint8_t pixel = *src_offset++;
            if(pixel || !(flags & BLIT_TRANSPARENT))
            {
                if(flags & BLIT_GHOST)
                {
                    uint8_t is_trans = IsTranslucent[pixel];
                    if(is_trans != 0xFF) // is it a translucent color?
                        pixel = Translucent[is_trans << 8 | *dst_offset];
                }

                if(flags & BLIT_FADING)
                {
                    // run color through fading table
                    for(int f = 0; f < FadingNum; f++)
                        pixel = FadingTable[pixel];
                }

                *dst_offset = pixel;
            }
            dst_offset++;
        }

        src_offset += src_adjust_width;
        dst_offset += dst_adjust_width;
    }
    while(--line_count);
}

long Buffer_Frame_To_Page(int x, int y, int w, int h, void *src, GraphicViewPortClass &dest, int flags, ...)
{
	if(!src)
		return 0;

	uint8_t *IsTranslucent;
	uint8_t *Translucent;
	uint8_t *FadingTable;
	int FadingNum;
	
	ShapeHeaderType *header_pointer;
	bool use_old_draw = true;

	char *shape_buffer_start;

	// Save the line attributes pointers and
	// Modify the src pointer to point to the actual image
	if(!UseOldShapeDraw && UseBigShapeBuffer)
	{
		header_pointer = (ShapeHeaderType *)src;

		shape_buffer_start = BigShapeBufferStart;
		if(header_pointer->shape_buffer)
			shape_buffer_start = TheaterShapeBufferStart;

		src = shape_buffer_start + (uintptr_t)header_pointer->shape_data; // these are both ptrs...
		use_old_draw = false;
	}
	// else just use the old shape drawing system

	// Pull off optional arguments
	va_list args;
    va_start(args, flags);

	int jflags = 0; // clear jump flags

	// See if we need to center the frame
	if(flags & SHAPE_CENTER)
	{
		x -= w / 2;
		y -= h / 2;
	}

	if(flags & SHAPE_TRANS)
		jflags |= BLIT_TRANSPARENT;

	if(flags & SHAPE_GHOST) // are we ghosting this shape
	{
		jflags |= BLIT_GHOST;
		IsTranslucent = va_arg(args, uint8_t *);
		Translucent = IsTranslucent + 256;
	}

	// If this is the first time through for this shape then
	// set up the shape header

	bool use_all_flags = false;

	if(!UseBigShapeBuffer || UseOldShapeDraw)
		use_old_draw = true; // no big shape buffer so use old system
	// Redo the shape headers if this shape was initially set up with different flags
	else if(header_pointer->draw_flags == -1 || header_pointer->draw_flags != (flags & SHAPE_TRANS | SHAPE_FADING | SHAPE_PREDATOR | SHAPE_GHOST))
	{
		Setup_Shape_Header(w, h, (char *)src, header_pointer, flags, Translucent, IsTranslucent);
		//ShapeJumpTableAddress = AllFlagsJumpTable;
		use_all_flags = true;
	}
	else
	{
		int eax = 0;
		if(flags & SHAPE_PREDATOR)
			eax |= BLIT_PREDATOR;
		if(flags & SHAPE_FADING)
			eax |= BLIT_FADING;
		if(flags & SHAPE_TRANS)
			eax |= BLIT_TRANSPARENT;
		if(flags & SHAPE_GHOST)
			eax |= BLIT_GHOST;

		eax <<= 7;
		// ShapeJumpTableAddress = NewShapeJumpTable + eax
	}

	if(flags & SHAPE_FADING) // are we fading this shape
	{
		FadingTable = va_arg(args, uint8_t *); // save address of fading tbl
		FadingNum = va_arg(args, int) & 0x3F; // get fade num, no need for more than 63
		jflags |= BLIT_FADING;

		if(!FadingNum)
			flags &= ~SHAPE_FADING; // don't fade

		// ShapeJumpTableAddress[4] = Single_Line_Single_Fade
		// ShapeJumpTableAddress[5] = Single_Line_Single_Fade_Trans

		if(FadingNum != 1)
		{
			// ShapeJumpTableAddress[4] = Single_Line_Fading
			// ShapeJumpTableAddress[5] = Single_Line_Fading_Trans
		}
	}

	if(flags & SHAPE_PREDATOR) // is predator effect on
	{
		int offset = va_arg(args, int);
		jflags |= BLIT_PREDATOR;

		offset <<= 1;

		if(offset < 0)
			offset = ((-offset) & PRED_MASK) | 0xFFFFFF00; // will be ffffff00-ffffff0E
		else
			offset &= PRED_MASK;

		BFPredOffset = offset;
		BFPartialCount = 0; // clear the partial count
		BFPartialPred = 256; // init partial to off

		for(int off = 0; off < 8; off++)
			BFPredNegTable[off + 8] = BFPredNegTable[off] + dest.Get_Width() + dest.Get_XAdd() + dest.Get_Pitch();
	}

	if(flags & SHAPE_PARTIAL) // is this a partial pred?
		BFPartialPred = va_arg(args, int) & 0xFF;

	va_end(args);

    // clip dest
	int src_x0 = 0;
	int src_y0 = 0;

    int dst_x0 = x;
    int dst_y0 = y;
    int dst_x1 = x + w;
    int dst_y1 = y + h;

    int code0 = Make_Code(dst_x0, dst_y0, dest.Get_Width(), dest.Get_Height());
    int code1 = Make_Code(dst_x1, dst_y1, dest.Get_Width() + 1, dest.Get_Height() + 1);

    // outside
    if(code0 & code1)
        return 0;

    if(code0 | code1)
    {
		// If the shape needs to be clipped then we cant handle it with the new header systen
		// so draw it with the old shape drawer
		use_old_draw = 1;

        // apply clip
        if(code0 & 0b1000)
        {
            src_x0 -= dst_x0;
            dst_x0 = 0;
        }
        if(code1 & 0b0100)
            dst_x1 = dest.Get_Width();
        if(code0 & 0b0010)
        {
            src_y0 -= dst_y0;
            dst_y0 = 0;
        }
        if(code1 & 0b0001)
            dst_y1 = dest.Get_Height();
    }

	// do blit
    auto src_offset = (uint8_t *)src + src_x0 + src_y0 * w;
	int src_adjust_width = w - (dst_x1 - dst_x0);

    int dst_area = dest.Get_XAdd() + dest.Get_Width() + dest.Get_Pitch();
    auto dst_offset = dest.Get_Offset() + dst_x0 + dst_y0 * dst_area;
	int dst_adjust_width = dst_area - (dst_x1 - dst_x0);

	if(use_old_draw)
	{
		if(dst_x1 <= dst_x0 || dst_y1 <= dst_y0)
        	return 0;

		int pixel_count = dst_x1 - dst_x0;
		int line_count = dst_y1 - dst_y0;

		switch(jflags & BLIT_OLD)
		{

			case 0: // BF_Copy
            {
				// copy lines
				do
				{
					memcpy(dst_offset, src_offset, pixel_count);
					src_offset += w;
					dst_offset += dst_area;
				}
				while(--line_count);
				break;
            }
			case BLIT_TRANSPARENT: // BF_Trans
				Do_Old_Blit<BLIT_TRANSPARENT>(line_count, pixel_count, src_offset, dst_offset, src_adjust_width, dst_adjust_width, Translucent, IsTranslucent, FadingNum, FadingTable);
				break;
            case BLIT_GHOST: // BF_Ghost
                Do_Old_Blit<BLIT_GHOST>(line_count, pixel_count, src_offset, dst_offset, src_adjust_width, dst_adjust_width, Translucent, IsTranslucent, FadingNum, FadingTable);
                break;
            case BLIT_GHOST | BLIT_TRANSPARENT: // BF_Ghost_Trans
                Do_Old_Blit<BLIT_GHOST | BLIT_TRANSPARENT>(line_count, pixel_count, src_offset, dst_offset, src_adjust_width, dst_adjust_width, Translucent, IsTranslucent, FadingNum, FadingTable);
                break;
            case BLIT_FADING: // BF_Fading
                Do_Old_Blit<BLIT_FADING>(line_count, pixel_count, src_offset, dst_offset, src_adjust_width, dst_adjust_width, Translucent, IsTranslucent, FadingNum, FadingTable);
                break;
            case BLIT_FADING | BLIT_TRANSPARENT: // BF_Fading_Trans
                Do_Old_Blit<BLIT_FADING | BLIT_TRANSPARENT>(line_count, pixel_count, src_offset, dst_offset, src_adjust_width, dst_adjust_width, Translucent, IsTranslucent, FadingNum, FadingTable);
                break;
            case BLIT_FADING | BLIT_GHOST: // BF_Ghost_Fading
                Do_Old_Blit<BLIT_FADING | BLIT_GHOST >(line_count, pixel_count, src_offset, dst_offset, src_adjust_width, dst_adjust_width, Translucent, IsTranslucent, FadingNum, FadingTable);
                break;
            case BLIT_FADING | BLIT_GHOST | BLIT_TRANSPARENT: // BF_Ghost_Fading_Trans
                Do_Old_Blit<BLIT_FADING | BLIT_GHOST | BLIT_TRANSPARENT>(line_count, pixel_count, src_offset, dst_offset, src_adjust_width, dst_adjust_width, Translucent, IsTranslucent, FadingNum, FadingTable);
                break;

            // TODO: predator

			default:
				printf("%s old f %x\n", __func__, jflags);
		}
	}
	else
	{
		// super jump table fun!
		printf("%s new f %x all flags %i\n", __func__, header_pointer->draw_flags & BLIT_ALL, use_all_flags);
	}

	return 0;
}
