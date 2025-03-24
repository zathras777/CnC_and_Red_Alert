#ifndef TOOLS_MIX_MIXFILE_H
#define TOOLS_MIX_MIXFILE_H

#include <stdint.h>
#include <sys/types.h>

#define MAXDRIVE 3
#define MAXDIR 256
#define MAXFILE 256
#define MAXEXT 256
#define MAXPATH 256

/********************************************************************
**	This is the data block controlling class.  It is used for every data
**	file as well as processing the entire data file list.
*/
class DataClass {
	public:
		int32_t CRC;

		static uint16_t Count;   // 16-bit number, cannot be negative.
		static uint32_t TotalSize;     // 32-bit number, cannot be negative.
		static char *ExtFrom[10];
		static char *ExtTo[10];
		static int ExtCount;
		static char *AltPath[10];
		static int AltPathCount;

		DataClass(char const *filename);
		~DataClass(void);

		static void Process_Input(char const *infile, bool quiet, bool paths);
		static void Process_Output(char const *outfile);

		char const * Output_Filename(void);
		char const * Input_Filename(void);

	private:
        char		*Filename;	// Raw original filename.
        uint32_t	Size;		// Size of data element. 32-bit value.
        uint32_t	Offset;		// Offset within mixfile for data start. 32-bit value.
		int			Index;		// Write order number.

        DataClass	*Next;		// Pointer to next file in chain.

        static DataClass *First;
        static bool Quiet;
        static bool Paths;
};

void fnmerge(char *dest, const char *drive, const char *path, const char *file, const char *ext);
void fnsplit(const char *path, char *drive, char *dir, char *fname, char *ext);
int32_t Calculate_CRC(void const * buffer, long len);

#endif