/*
**	Command & Conquer Red Alert(tm)
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

/* $Header: /CounterStrike/FUNCTION.H 2     3/13/97 2:05p Steve_tall $*/
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : FUNCTION.H                                                   *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : May 27, 1994                                                 *
 *                                                                                             *
 *                  Last Update : May 27, 1994   [JLB]                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef FUNCTION_H
#define FUNCTION_H

/*
**	!!!DEFINE!!!  "NDEBUG" if the assertion code is to be !!!REMOVED!!! from the project.
*/
//#define	NDEBUG

#pragma warn -hid

/*
Map (screen) class heirarchy.

 MapeditClass (most derived class) -- scenario editor
        │
   MouseClass -- handles mouse animation and display control
        │
  ScrollClass -- map scroll handler
        │
    HelpClass -- pop-up help text handler
        │
     TabClass -- file folder tab screen mode control dispatcher
        │
 SidebarClass -- displays and controls construction list sidebar
        │
   PowerClass -- display power production/consumption bargraph
        │
   RadarClass -- displays and controls radar map
        │
 DisplayClass -- general tactical map display handler
        │
     MapClass -- general tactical map data handler
        │
 GScreenClass (pure virtual base class) -- generic screen control

                          AbstractClass
                                  │
                                  │
                                  │
                                  │
                            ObjectClass
                                  │
       ┌──────┬──────────┬────────┼────────┬────────────────┬───────────┐
   AnimClass  │  TemplateClass    │        ├─ FuseClass     │    TerrainClass
              │                   │        ├─ FlyClass      │
              │                   │  BulletClass            │
       OverlayClass        MissionClass               SmudgeClass
                                  │
                             RadioClass
                                  │
                                  ├─ CrewClass
                                  ├─ FlasherClass
                                  ├─ StageClass
                                  ├─ CargoClass
                            TechnoClass
                                  │
                       ┌──────────┴────────────────────────────┐
                   FootClass                           BuildingClass
                       │
         ┌─────────────┴┬─────────────┐
    DriveClass  InfantryClass         ├─ FlyClass
         │                      AircraftClass
       ┌─┴─────────┐
       │           │
       │     VesselClass
       │
    UnitClass


                            AbstractTypeClass
                                    │
                              ObjectTypeClass
                                    │
             ┌──────────────────────┼────────────┬─────────────────┐
             │                      │            │                 │
       TechnoTypeClass              │            │                 │
             │                BulletTypeClass    │                 │
             │                           TemplateTypeClass         │
    ┌────────┴─────┬───────────┬──────────────┬────────┐    TerrainTypeClass
    │              │           │              │        │
UnitTypeClass      │   BuildingTypeClass      │  VesselTypeClass
                   │                          │
           AircraftTypeClass          InfantryTypeClass
*/


#include	"watcom.h"
#include "lint.h"


#ifdef WIN32
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include	<windows.h>
#endif
#define WWFILE_H
#define RAWFILE_H
#define MONOC_H

#define	_MAX_NAME	_MAX_FNAME

#endif

#include <algorithm>

using std::min;

#ifndef BITMAPCLASS
#define BITMAPCLASS
class BitmapClass
{
	public:
		BitmapClass(int w, int h, unsigned char * data) :
			Width(w), Height(h), Data(data) {};

		int Width;
		int Height;
		unsigned char * Data;
};

class TPoint2D
{
	public:
		TPoint2D(int xx, int yy) : x(xx), y(yy) {};
		TPoint2D(void) : x(0), y(0) {};

		int x;
		int y;
};
#endif


/**********************************************************************
**	This class is solely used as a parameter to a constructor that does
**	absolutely no initialization to the object being constructed. By using
**	this method, it is possible to load and save data directly from a
**	class that has virtual functions. The construction process automatically
**	takes care of initializing the virtual function table pointer and the
**	rest of the constructor doesn't initialize any data members. After loading
**	into a class object, simply perform an in-place new operation.
*/
#ifndef NOINITCLASS
#define NOINITCLASS
struct NoInitClass {
	public:
		void operator () (void) const {};
};
#endif


#define WWMEM_H

#ifndef WIN32
#define TIMER_H
#endif

#ifdef WIN32
#include	"key.h"
#endif

#include <wwlib32.h>
#include	"mpu.h"
#include	"bench.h"
#include	"rect.h"
#include	"jshell.h"
#include	"buff.h"
#include	"face.h"
#include	"random.h"
#include	"crc.h"
#include "compat.h"
#include	"fixed.h"
#include	"base64.h"
#include	"pipe.h"
#include	"xpipe.h"
#include	"ramfile.h"
#include	"lcw.h"
#include	"lzw.h"
#include	"lcwpipe.h"
#include	"lzwpipe.h"
#include	"lzopipe.h"
#include	"crcpipe.h"
#include	"shapipe.h"
#include	"b64pipe.h"
#include	"straw.h"
#include	"xstraw.h"
#include	"b64straw.h"
#include	"lcwstraw.h"
#include	"lzwstraw.h"
#include	"lzostraw.h"
#include	"crcstraw.h"
#include	"shastraw.h"
#include	"rndstraw.h"

// Should be part of WWLIB.H. This is used in JSHELL.CPP.
typedef struct {
	unsigned char	SourceColor;
	unsigned char	DestColor;
	unsigned char	Fading;
	unsigned char	reserved;
} TLucentType;


#include	<string.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<stddef.h>
#ifdef PORTABLE
#include    "ex_string.h"
#else
#include	<mem.h>
#include	<dos.h>
#include	<direct.h>
#include	<process.h>
#endif
#include	<stdarg.h>
#include	<ctype.h>
#include	<assert.h>
#include	<new>



#ifdef WIN32
#define	int386x(a,b,c,d)	0
#define	int386(a,b,c)	0
#endif


/*
**	VQ player specific includes.
*/
#include <vqa32/vqaplay.h>
#include <vqa32/vqafile.h>

extern bool GameActive;
extern long LParam;

#include	<assert.h>
#include	"vector.h"
#include	"heap.h"
#include	"ccfile.h"
#include	"monoc.h"
#include	"conquer.h"
#include	"debug.h"
#include "special.h"
#include	"defines.h"
#include	"ccini.h"
#include	"ccptr.h"
#include	"bar.h"

#ifndef PORTABLE
/*
**	Greenleaf specific includes.
*/
#include <modem.h>
#include <fast.h>
#endif

extern long Frame;
CELL Coord_Cell(COORDINATE coord);

#include	"utracker.h"
#include	"crate.h"
#include	"rules.h"
#include	"ini.h"
#include	"int.h"
#include	"pk.h"
#include	"pkpipe.h"
#include	"pkstraw.h"
#include	"sha.h"
#include	"blowfish.h"
#include	"blowpipe.h"
#include	"blwstraw.h"
#include	"language.h"
#include	"hsv.h"
#include	"rgb.h"
#include	"palette.h"
#include "version.h"
#include	"facing.h"
#include	"ftimer.h"
#include	"theme.h"
#include	"link.h"
#include	"gadget.h"
#include	"control.h"
#include	"toggle.h"
#include	"checkbox.h"
#include	"shapebtn.h"
#include	"textbtn.h"
#include	"statbtn.h"
#include	"slider.h"
#include "list.h"
#include	"drop.h"
#include "cheklist.h"
#include "colrlist.h"
#include	"edit.h"
#include	"gauge.h"
#include	"msgbox.h"
#include	"dial8.h"
#include	"txtlabel.h"
#include "loaddlg.h"
#include	"super.h"
#include	"house.h"
#include	"gscreen.h"
#include	"map.h"
#include	"display.h"
#include	"radar.h"
#include	"power.h"
#include	"sidebar.h"
#include	"tab.h"
#include	"help.h"
#include	"mouse.h"
#include	"help.h"
#include	"target.h"
#include	"theme.h"
#include	"team.h"				// Team objects.
#include	"warhead.h"
#include	"weapon.h"
#include	"trigtype.h"
#include	"teamtype.h"		// Team type objects.
#include	"taction.h"
#include	"tevent.h"
#include	"trigger.h"			// Trigger event objects.
#include	"mapedit.h"			// map editor class
#include	"abstract.h"
#include "object.h"
#include "mission.h"
#include	"door.h"
#include	"bullet.h"			// Bullet objects.
#include	"terrain.h"			// Terrain objects.
#include	"anim.h"				// Animation objects.
#include	"template.h"		// Icon template objects.
#include	"overlay.h"			// Overlay objects.
#include	"smudge.h"			// Stains on the terrain objects.
#include	"aircraft.h"		// Aircraft objects.
#include	"unit.h"				// Ground unit objects.
#include "vessel.h"			// Sea unit objects.
#include	"infantry.h"		// Infantry objects.
#include	"credits.h"			// Credit counter class.
#include	"score.h"			// Scoring system class.
#include	"factory.h"			// Production manager class.
#include "intro.h"
#include "ending.h"
#include	"logic.h"
#include	"queue.h"
#include	"event.h"
#include "base.h"				// defines the AI's pre-built base
#include	"carry.h"
#include	"scenario.h"
#include "msglist.h"			// Multiplayer chat message system
#include "session.h"			// Multiplayer session class
//#include "phone.h"			// Phone list manager
#include "ipxmgr.h"			// IPX connection manager
#include	"nullmgr.h"			// Modem connection manager
#include	"readline.h"
#include	"vortex.h"
#include "egos.h"
#ifdef WIN32
#include	"filepcx.h"
#endif

#if(TEN)
#include "tenmgr.h"
#endif

#if(MPATH)
#ifdef WIN32
#include "mpmgrw.h"
#else
#include "mpmgrd.h"
#endif
#endif

bool InitDDraw(void);
// Denzil 5/18/98 - Mpeg movie playback
#ifdef MPEGMOVIE
bool PlayMpegMovie(const char* name);
#endif

#include	"externs.h"


extern int Get_CD_Drive(void);
extern void Fatal(char const *message, ...);

#ifdef WIN32

/*
** For WIN32, replace the assert macro so we get an error on the debugger screen
**  where we can see it.
**
*/
#if !defined(__BORLANDC__) && !defined(__GNUC__) && !defined(_MSC_VER)
#ifdef assert
#undef assert
#endif	//assert
void Assert_Failure (char *expression, int line, char *file);

#ifdef NDEBUG
 #define assert(__ignore) ((void)0)
#else
 #define assert(expr)   ((expr)?(void)0:Assert_Failure(#expr,__LINE__,__FILE__))
#endif	//NDEBUG

#endif	//__BORLANDC__


extern void Free_Interpolated_Palettes(void);
extern int Load_Interpolated_Palettes(char const *filename, bool add=FALSE);
extern void Rebuild_Interpolated_Palette(unsigned char *interpal);
extern void Interpolate_2X_Scale( GraphicBufferClass *source, GraphicViewPortClass *dest ,char const *palette_file_name);
void Increase_Palette_Luminance (unsigned char *palette , int red_percentage , int green_percentage , int blue_percentage ,int cap);
#endif

/*
**	ADATA.CPP
*/
char const * Anim_Name(AnimType anim);

/*
**	AIRCRAFT.CPP
*/
bool Building_Check(void);

/*
**	ANIM.CPP
*/
void Shorten_Attached_Anims(ObjectClass * obj);
AnimType Anim_From_Name(char const * name);

/*
**	AUDIO.CPP
*/
VocType Voc_From_Name(char const * name);
char const * Speech_Name(VoxType speech);
char const * Voc_Name(VocType voc);
int Sound_Effect(VocType voc, fixed volume=1, int variation=1, signed short panvalue=0, HousesType house=HOUSE_NONE);
void Speak(VoxType voice);
void Speak_AI(void);
void Stop_Speaking(void);
void Sound_Effect(VocType voc, COORDINATE coord, int variation=1, HousesType house=HOUSE_NONE);
bool Is_Speaking(void);

/*
**	CDFILE.CPP
*/
#ifdef WIN32
int harderr_handler(unsigned, unsigned, unsigned *);
#else
int harderr_handler(unsigned, unsigned, unsigned __far *);
#endif

/*
**	COMBAT.CPP
*/
int Modify_Damage(int damage, WarheadType warhead, ArmorType armor, int distance);
void Explosion_Damage(COORDINATE coord, int strength, TechnoClass * source, WarheadType warhead);
AnimType Combat_Anim(int damage, WarheadType warhead, LandType land);
void Wide_Area_Damage(COORDINATE coord, LEPTON radius, int damage, TechnoClass * source, WarheadType warhead);

/*
**	CONQUER.CPP
*/
void List_Copy(short const * source, int len, short * dest);
int Get_CD_Index (int cd_drive, int timeout);
int Owner_From_Name(char const * text);
CrateType Crate_From_Name(char const * name);
Rect const Shape_Dimensions(void const * shapedata, int shapenum);
void IPX_Call_Back(void);
bool Is_Counterstrike_Installed (void);
#ifdef FIXIT_CSII	//	checked - ajw 9/28/98
bool Is_Aftermath_Installed (void);
#endif


#if(TEN)
void Ten_Call_Back(void);
#endif	// TEN

#if(MPATH)
void MPATH_Call_Back(void);
#endif	// MPATH

void Center_About_Objects(void);
bool Force_CD_Available(int cd);
void Handle_View(int view, int action=0);
void Handle_Team(int team, int action=0);
TechnoTypeClass const * Fetch_Techno_Type(RTTIType type, int id);
char const * Fading_Table_Name(char const * base, TheaterType theater);
void Unselect_All(void);
void Play_Movie(char const * name, ThemeType theme=THEME_NONE, bool clrscrn=true);
void Play_Movie(VQType name, ThemeType theme=THEME_NONE, bool clrscrn=true);
bool Main_Loop(void);
TheaterType Theater_From_Name(char const * name);
void Main_Game(int argc, char * argv[]);
long VQ_Call_Back(unsigned char * buffer=NULL, long frame=0);
long VQ_Event_Handler(unsigned long event, void *buffer, long nbytes);
void Call_Back(void);
char const *Language_Name(char const * basename);
SourceType Source_From_Name(char const * name);
char const *Name_From_Source(SourceType source);
FacingType KN_To_Facing(int input);
void const *Get_Radar_Icon(void const * shapefile, int shapenum, int frames, int zoomfactor);
void CC_Draw_Shape(void const * shapefile, int shapenum, int x, int y, WindowNumberType window, ShapeFlags_Type flags, void const * fadingdata=0, void const * ghostdata=0, DirType rotation=DIR_N, long scale=0x0100);
void Go_Editor(bool flag);
long MixFileHandler(VQAHandle * vqa, long action, void * buffer, long nbytes);
char *CC_Get_Shape_Filename(void const * shapeptr );
void CC_Add_Shape_To_Global(void const * shapeptr, char * filename, char code );
void Bubba_Print(char * format,...);
void Heap_Dump_Check(char * string );
void Dump_Heap_Pointers(void);
void * Hires_Load(char * name);
void Shake_The_Screen(int shakes);

/*
**	COORD.CPP
*/
short const * Coord_Spillage_List(COORDINATE coord, Rect const & rect, bool nocenter=true);
void Normal_Move_Point(short &x, short &y, DirType dir, unsigned short distance);
void Move_Point(short &x, short &y, DirType dir, unsigned short distance);
COORDINATE Coord_Move(COORDINATE start, DirType facing, unsigned short distance);
COORDINATE Coord_Scatter(COORDINATE coord, unsigned distance, bool lock=false);
DirType Direction(CELL cell1, CELL cell2);
DirType Direction(COORDINATE coord1, COORDINATE coord2);
DirType Direction256(COORDINATE coord1, COORDINATE coord2);
DirType Direction8(COORDINATE coord1, COORDINATE coord2);
int Distance(COORDINATE coord1, COORDINATE coord2);
int Distance(TARGET target1, TARGET target2);
short const * Coord_Spillage_List(COORDINATE coord, int maxsize);

/*
**	DEBUG.CPP
*/
void Log_Event(char const *text, ...);
void Debug_Key(unsigned input);
void Self_Regulate(void);

/*
**	DIALOG.CPP
*/
void Draw_Caption(int text, int x, int y, int w);
void Draw_Caption(char const * text, int x, int y, int w);
int Format_Window_String(char * string, int maxlinelen, int & width, int & height);
extern void Dialog_Box(int x, int y, int w, int h);
void Conquer_Clip_Text_Print(char const *, unsigned x, unsigned y, RemapControlType * fore, unsigned back=(unsigned)TBLACK, TextPrintType flag=TPF_8POINT|TPF_DROPSHADOW, int width=-1, int const * tabs=0);
void Draw_Box(int x, int y, int w, int h, BoxStyleEnum up, bool filled);
int cdecl Dialog_Message(char *errormsg, ...);
void Window_Box(WindowNumberType window, BoxStyleEnum style);
void Fancy_Text_Print(char const *text, unsigned x, unsigned y, RemapControlType * fore, unsigned back, int /*TextPrintType*/ flag, ...);
void Fancy_Text_Print(int text, unsigned x, unsigned y, RemapControlType * fore, unsigned back, int /*TextPrintType*/ flag, ...);
void Simple_Text_Print(char const *text, unsigned x, unsigned y, RemapControlType * fore, unsigned back, int /*TextPrintType*/ flag);
void Plain_Text_Print(int text, unsigned x, unsigned y, unsigned fore, unsigned back, TextPrintType flag, ...);
void Plain_Text_Print(char const *text, unsigned x, unsigned y, unsigned fore, unsigned back, TextPrintType flag, ...);

/*
**	DISPLAY.CPP
*/

/*
**	ENDING.CPP
*/
void GDI_Ending(void);
void Nod_Ending(void);

/*
**	EXPAND.CPP
*/
bool Expansion_Present(void);
bool Expansion_Dialog(void);
bool Expansion_CS_Present(void);
#ifdef FIXIT_CSII	//	checked - ajw 9/28/98
bool Expansion_AM_Present(void);
#endif
/*
**	FINDPATH.CPP
*/
int Optimize_Moves(PathType *path, int (*callback)(CELL, FacingType), int threshhold);

/*
**	GOPTIONS.CPP
*/

/*
**	INI.CPP
*/
void Write_Scenario_INI(char *root);
bool Read_Scenario_INI(char *root, bool fresh=true);
int Scan_Place_Object(ObjectClass *obj, CELL cell);
void Assign_Houses(void);

/*
**	INIBIN.CPP
*/
unsigned long Ini_Binary_Version( void );
bool Read_Scenario_INB( CCFileClass *file, char *root, bool fresh );
bool Valid_Scenario_INB( CCFileClass *file );

/*
**	INICODE.CPP
*/
bool Read_Scenario_INI_Write_INB( char *root, bool fresh );

/*
**	INIT.CPP
*/
void Load_Title_Page(bool visible=false);
long Obfuscate(char const * string);
void Anim_Init(void);
bool Init_Game(int argc, char *argv[]);
bool Select_Game(bool fade = false);
bool Parse_Command_Line(int argc, char *argv[]);
void Parse_INI_File(void);

/*
** INTERPAL.CPP
*/
#define SIZE_OF_PALETTE 256
extern	"C" unsigned char *InterpolationPalette;
extern	bool	InterpolationPaletteChanged;
extern	void 	Interpolate_2X_Scale( GraphicBufferClass *source, GraphicViewPortClass *dest ,char const *palette_file_name);
void Read_Interpolation_Palette (char const *palette_file_name);
void Write_Interpolation_Palette (char const *palette_file_name);
void Increase_Palette_Luminance(unsigned char *InterpolationPalette ,	int RedPercentage ,int GreenPercentage ,int BluePercentage ,int cap);
extern "C"{
	extern unsigned char PaletteInterpolationTable[SIZE_OF_PALETTE][SIZE_OF_PALETTE];
	extern unsigned char *InterpolationPalette;
	void __cdecl Asm_Create_Palette_Interpolation_Table(void);
}

/*
** JSHELL.CPP
*/
int Load_Picture(char const *filename, BufferClass& scratchbuf, BufferClass& destbuf, unsigned char *palette, PicturePlaneType format);
void * Conquer_Build_Fading_Table(PaletteClass const & palette, void *dest, int color, int frac);
void * Small_Icon(void const * iconptr, int iconnum);
void Set_Window(int window, int x, int y, int w, int h);
void * Load_Alloc_Data(FileClass &file);
long Load_Uncompress(FileClass &file, BuffType &uncomp_buff, BuffType &dest_buff, void *reserved_data);
long Translucent_Table_Size(int count);
void *Build_Translucent_Table(PaletteClass const & palette, TLucentType const *control, int count, void *buffer);
void *Conquer_Build_Translucent_Table(PaletteClass const & palette, TLucentType const *control, int count, void *buffer);
void * Make_Fading_Table(PaletteClass const & palette, void * dest, int color, int frac);

/*
**	KEYFBUFF.ASM
*/
extern "C" {
	long __cdecl Buffer_Frame_To_Page(int x, int y, int w, int h, void *Buffer, GraphicViewPortClass &view, int flags, ...);
}

/*
**	KEYFRAME.CPP
*/
void *Build_Frame(void const *dataptr, unsigned short framenumber, void *buffptr);
unsigned short Get_Build_Frame_Count(void const *dataptr);
unsigned short Get_Build_Frame_X(void const *dataptr);
unsigned short Get_Build_Frame_Y(void const *dataptr);
unsigned short Get_Build_Frame_Width(void const *dataptr);
unsigned short Get_Build_Frame_Height(void const *dataptr);
bool Get_Build_Frame_Palette(void const *dataptr, void *palette);

/*
**	MAP.CPP
*/
int Terrain_Cost(CELL cell, FacingType facing);
int Coord_Spillage_Number(COORDINATE coord, int maxsize);

/*
**	MENUS.CPP
*/
void Setup_Menu(int menu, char const *text[], unsigned long field, int index, int skip);
int Check_Menu(int menu, char const *text[], char *selection, long field, int index);
int Do_Menu(char const **strings, bool blue);
extern int UnknownKey;
int Main_Menu(unsigned long timeout);

/*
** MPLAYER.CPP
*/
GameType Select_MPlayer_Game (void);
void Clear_Listbox(ListClass *list);
void Clear_Vector(DynamicVectorClass <NodeNameType *> *vector);
void Computer_Message(void);
int Surrender_Dialog(int text);
#ifdef FIXIT_VERSION_3		//	Stalemate games.
int Surrender_Dialog(const char* text);
bool Determine_If_Using_DVD();
bool Using_DVD();
#endif
int Abort_Dialog(void);

#if(TEN)
int Read_TEN_Game_Options(void);
#endif	// TEN

#if(MPATH)
int Read_MPATH_Game_Options(void);
#endif	// MPATH

#if(TEN)
/*
** CCTEN.CPP
*/
int Init_TEN(void);
void Shutdown_TEN(void);
void Connect_TEN(void);
void Destroy_TEN_Connection(int id, int error);
void Send_TEN_Win_Packet(void);
void Send_TEN_Alliance(char *whom, int ally);
void Send_TEN_Out_Of_Sync(void);
void Send_TEN_Packet_Too_Late(void);
#endif	// TEN

#if(MPATH)
/*
** CCMPATH.CPP
*/
int Init_MPATH(void);
void Shutdown_MPATH(void);
void Connect_MPATH(void);
void Destroy_MPATH_Connection(int id, int error);
#endif	// MPATH

/*
** NETDLG.CPP
*/
bool Init_Network (void);
void Shutdown_Network (void);
bool Remote_Connect (void);
void Destroy_Connection(int id, int error);
bool Process_Global_Packet(GlobalPacketType *packet, IPXAddressClass *address);
uint32_t Compute_Name_CRC(char *name);
void Net_Reconnect_Dialog(int reconn, int fresh, int oldest_index, unsigned long timeval);

/*
** NULLDLG.CPP
*/
int Init_Null_Modem( SerialSettingsType *settings );
void Shutdown_Modem( void );
void Modem_Signoff( void );
int Test_Null_Modem( void );
int Reconnect_Modem( void );
void Destroy_Null_Connection(int id, int error);
GameType Select_Serial_Dialog( void );
int Com_Scenario_Dialog(bool skirmish=false);
int Com_Show_Scenario_Dialog(void);

void Smart_Printf( char *format, ... );
void Hex_Dump_Data( char *buffer, int length );
void itoh( int i, char *s);
void Log_Start_Time( char *string );
void Log_End_Time( char *string );
void Log_Time( char *string );
void Log_Start_Nest_Time( char *string );
void Log_End_Nest_Time( char *string );

/*
**	OBJECT.CPP
*/

/*
**	PROFILE.CPP
*/
int WWGetPrivateProfileInt(char const *section, char const *entry, int def, char *profile);
bool WWWritePrivateProfileInt(char const *section, char const *entry, int value, char *profile);
bool WWWritePrivateProfileString(char const *section, char const *entry, char const *string, char *profile);
char * WWGetPrivateProfileString(char const *section, char const *entry, char const *def, char *retbuffer, int retlen, char const * profile);
unsigned WWGetPrivateProfileHex (char const *section, char const *entry, char * profile);

char *Read_Bin_Buffer( void );
bool Read_Bin_Init( char *buffer, int length );
int Read_Bin_Length( char *buffer );
bool Read_Bin_Num( void *num, int length, char *buffer );
int Read_Bin_Pos( char *buffer );
int Read_Bin_PosSet( unsigned int pos, char *buffer );
bool Read_Bin_String( char *string, char *buffer );

char *Write_Bin_Buffer( void );
bool Write_Bin_Init( char *buffer, int length );
int Write_Bin_Length( char *buffer );
bool Write_Bin_Num( void *num, int length, char *buffer );
int Write_Bin_Pos( char *buffer );
int Write_Bin_PosSet( unsigned int pos, char *buffer );
bool Write_Bin_String( char *string, int length, char *buffer );

/*
** QUEUE.CPP
*/
bool Queue_Target(TargetClass whom, TARGET target);
bool Queue_Destination(TargetClass whom, TARGET target);
bool Queue_Mission(TargetClass whom, MissionType mission);
bool Queue_Mission(TargetClass whom, MissionType mission, TARGET target, TARGET destination);
bool Queue_Mission(TargetClass whom, MissionType mission, TARGET target, TARGET destination, SpeedType speed, MPHType maxspeed);
bool Queue_Options(void);
bool Queue_Exit(void);
void Queue_AI(void);
void Add_CRC(uint32_t *crc, uint32_t val);

/*
**	RANDOM.CPP
*/

/*
**	REINF.CPP
*/
bool Do_Reinforcements(TeamTypeClass const * team);
bool Create_Special_Reinforcement(HouseClass * house, TechnoTypeClass const * type, TechnoTypeClass const * another, TeamMissionType mission = TMISSION_NONE, int argument =0);
int Create_Air_Reinforcement(HouseClass *house, AircraftType air, int number, MissionType mission, TARGET tarcom, TARGET navcom, InfantryType passenger=INFANTRY_NONE);

/*
**	ROTBMP.CPP
*/
int Rotate_Bitmap(GraphicViewPortClass *srcvp,GraphicViewPortClass *destvp,int angle);

/*
**	SAVELOAD.CPP
*/
bool Load_Misc_Values(Straw & file);
bool Save_Misc_Values(Pipe & file);
bool Load_MPlayer_Values(Straw & file);
bool Save_MPlayer_Values(Pipe & file);
bool Get_Savefile_Info(int id, char * buf, unsigned * scenp, HousesType * housep);
bool Load_Game(int id);
bool Read_Object (void * ptr, int base_size, int class_size, FileClass & file, void * vtable);
bool Save_Game(int id, char const * descr, bool bargraph=false);
bool Write_Object (void * ptr, int class_size, FileClass & file);
void Code_All_Pointers(void);
void Decode_All_Pointers(void);
void Dump(void);

/*
** SCENARIO.CPP
*/
void Disect_Scenario_Name(char const * name, int & scenario, ScenarioPlayerType & player, ScenarioDirType & dir, ScenarioVarType & var);
void Post_Load_Game(int load_net);
bool End_Game(void);
bool Read_Scenario(char *root);
bool Start_Scenario(char *root, bool briefing=true);
HousesType Select_House(void);
void Clear_Scenario(void);
void Do_Briefing(char const * text);
void Do_Lose(void);
void Do_Win(void);
void Do_Restart(void);
void Fill_In_Data(void);
bool Restate_Mission(char const * name, int button1, int button2);
bool BGMessageBox(char const *text, int button1, int button2);

/*
**	SCORE.CPP
*/
char const * Map_Selection(void);
void Bit_It_In(int x, int y, int w, int h, GraphicBufferClass *src, GraphicBufferClass *dest, int delay=0, int dagger=0);
void Call_Back_Delay(int time);
int Alloc_Object(ScoreAnimClass *obj);

/*
**	SPECIAL.CPP
*/
void Special_Dialog(bool simple=false);
char const * Fetch_Password(int caption, int message, int btext=TXT_OK);
#ifdef FIXIT_CSII	//	checked - ajw 9/28/98
int Fetch_Difficulty(bool amath=false);
#else
int Fetch_Difficulty(void);
#endif

/*
**	STARTUP.CPP
*/
void Print_Error_End_Exit(char *string);
void Emergency_Exit ( int code );

/*
**	SUPPORT.ASM
*/

/*
** TARGET.CPP
*/
TechnoTypeClass const * As_TechnoType(TARGET target);
COORDINATE As_Movement_Coord(TARGET target);
AircraftClass * As_Aircraft(TARGET target);
AnimClass * As_Animation(TARGET target);
BuildingClass * As_Building(TARGET target);
BulletClass * As_Bullet(TARGET target);
CELL As_Cell(TARGET target);
COORDINATE As_Coord(TARGET target);
InfantryClass * As_Infantry(TARGET target);
TeamClass * As_Team(TARGET target);
TeamTypeClass * As_TeamType(TARGET target);
TechnoClass * As_Techno(TARGET target);
TriggerClass * As_Trigger(TARGET target);
TriggerTypeClass * As_TriggerType(TARGET target);
UnitClass * As_Unit(TARGET target);
VesselClass * As_Vessel(TARGET target);
inline bool Target_Legal(TARGET target) {return(target != TARGET_NONE);};
ObjectClass * As_Object(TARGET target);

/*
**	TEAMTYPE.CPP
*/
NeedType TeamMission_Needs(TeamMissionType tmtype);

/*
**	TRACKER.CPP
*/
void Detach_This_From_All(TARGET target, bool all=true);

/*
**	TRIGGER.CPP
*/
TriggerClass * Find_Or_Make(TriggerTypeClass * trigtype);

/*
** ULOGIC.CPP
*/
int Terrain_Cost(CELL cell, FacingType facing);

/*
**	VERSION.CPP
*/
char const * Version_Name(void);

/*
**	WEAPON.CPP
*/
WeaponType Weapon_From_Name(char const * name);
ArmorType Armor_From_Name(char const * name);

/*
** Winstub.cpp
*/
void Load_Title_Screen(char *name, GraphicViewPortClass *video_page, unsigned char *palette);

/*
** Egos.CPP
*/
void Show_Who_Was_Responsible (void);

#include	"inline.h"


#endif
