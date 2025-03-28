/*
**	Command & Conquer(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* $Header:   F:\projects\c&c\vcs\code\wwalloc.h_v   2.18   16 Oct 1995 16:47:52   JOE_BOSTIC  $ */


#ifdef __cplusplus
extern "C" {
#endif


/*
**	This should be located in the wwlib32.h file, but is located here for
**	test purposes.
*/
#ifdef __FLAT__
#define	PRIVATE	static
#endif

typedef enum MemoryFlagType {
	MEM_NORMAL = 0x0000,		// Default memory (normal).
	MEM_PUBLIC = 0x0000,		// Default memory (normal).
	MEM_CHIP   = 0x0000,		// Graphic & sound buffer memory (Amiga).
	MEM_UNUSED = 0x0001,		// <unused>
	MEM_SYSTEM = 0x0002,		// Allocate out of system heap (XMS or EMS only).
	MEM_RELAXED= 0x0004,		// Don't worry about page conservation in EMS.
	MEM_TEMP   = 0x0008,		// Temporary allocation (used by library only).
	MEM_CLEAR  = 0x0010,		// Fill memory with '\0' characters.
	MEM_PARA   = 0x0020,		// Paragraph aligned (IBM only).
	MEM_XMS    = 0x0040,		// XMS memory.
	MEM_EMS    = 0x0080,		// EMS memory (not implemented).
	MEM_X      = 0x8000		// Here to force this enum to be unsigned sized.
} MemoryFlagType;
MemoryFlagType operator |(MemoryFlagType, MemoryFlagType);
MemoryFlagType operator &(MemoryFlagType, MemoryFlagType);
MemoryFlagType operator ~(MemoryFlagType);


/* Prototypes for functions defined in this file */
void * __cdecl Alloc(unsigned long bytes_to_alloc, MemoryFlagType flags);
void __cdecl Free(void const *pointer);
void * __cdecl Resize_Alloc(void const *original_ptr, unsigned long new_size_in_bytes);
long __cdecl Ram_Free(MemoryFlagType flag);
long __cdecl Total_Ram_Free(MemoryFlagType flag);
long __cdecl Heap_Size(MemoryFlagType flag);

extern unsigned long __cdecl MinRam;		// Record of least memory at worst case.
extern unsigned long __cdecl MaxRam;		// Record of total allocated at worst case.

#ifdef __cplusplus
}
#endif

