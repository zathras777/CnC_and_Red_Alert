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

/***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Westwood Keyboard Library                                    *
 *                                                                                             *
 *                    File Name : KEYBOARD.H                                                   *
 *                                                                                             *
 *                   Programmer : Philip W. Gorrow                                             *
 *                                                                                             *
 *                   Start Date : 10/16/95                                                     *
 *                                                                                             *
 *                  Last Update : October 16, 1995 [PWG]                                       *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef KEYBOARD_H
#define KEYBOARD_H
 
#include "wwstd.h"

union SDL_Event;

typedef enum {
	WWKEY_SHIFT_BIT	= 0x100,
	WWKEY_CTRL_BIT		= 0x200,
	WWKEY_ALT_BIT		= 0x400,
	WWKEY_RLS_BIT		= 0x800,
	WWKEY_VK_BIT		= 0x1000,
	WWKEY_DBL_BIT		= 0x2000,
	WWKEY_BTN_BIT		= 0x8000,
} WWKey_Type;

class WWKeyboardClass
{
	public:
		/*===================================================================*/
		/* Define the base constructor and destructors for the class			*/
		/*===================================================================*/
		WWKeyboardClass();

		/*===================================================================*/
		/* Define the functions which work with the Keyboard Class				*/
		/*===================================================================*/
		bool 	Check(void);															// checks keybuff for meta key
		int 	Get(void);																// gets a meta key from the keybuffer
		bool 	Put(int key);															// dumps a key into the keybuffer
		bool	Put_Key_Message(unsigned vk_key, bool release = false);					// handles keyboard related message
																						//   and mouse clicks and dbl clicks
		int 	To_ASCII(int num);													// converts keynum to ascii value
		void 	Clear(void);															// clears all keys from keybuffer
		int 	Down(int key);															// tests to see if a key is down

		/*===================================================================*/
		/* Define the main hook for the message processing loop.					*/
		/*===================================================================*/
		//void Message_Handler(HWND hwnd, UINT message, UINT wParam, long lParam);

		/*===================================================================*/
		/* Define public routines which can be used on keys in general.		*/
		/*===================================================================*/
		bool Is_Mouse_Key(int key);

		bool Event_Handler(SDL_Event *event);

		/*===================================================================*/
		/* Define the public access variables which are used with the			*/
		/*   Keyboard Class.																	*/
		/*===================================================================*/
		int				MouseQX;
		int				MouseQY;

	private:
		/*===================================================================*/
		/* Define the private access functions which are used by keyboard		*/
		/*===================================================================*/
		int  Buff_Get(void);


		/*===================================================================*/
		/* Define the private access variables which are used with the			*/
		/*   Keyboard Class.																	*/
		/*===================================================================*/
		unsigned short Buffer[256];		// buffer which holds actual keypresses
		long				Head;					// the head position in keyboard buffer
		long				Tail;					// the tail position in keyboard buffer
};

// these are (mostly) SDL_SCANCODE_x values
#define	VK_NONE				  	0
#define	VK_LBUTTON          	1
#define	VK_RBUTTON          	2
#define	VK_MBUTTON          	3

#define	VK_A					4
#define	VK_B					5
#define	VK_C					6
#define	VK_D					7
#define	VK_E					8
#define	VK_F					9
#define	VK_G					10
#define	VK_H					11
#define	VK_I					12
#define	VK_J					13
#define	VK_K					14
#define	VK_L					15
#define	VK_M					16
#define	VK_N					17
#define	VK_O					18
#define	VK_P					19
#define	VK_Q					20
#define	VK_R					21
#define	VK_S					22
#define	VK_T					23
#define	VK_U					24
#define	VK_V					25
#define	VK_W					26
#define	VK_X					27
#define	VK_Y					28
#define	VK_Z					29

#define	VK_1					30
#define	VK_2					31
#define	VK_3					32
#define	VK_4					33
#define	VK_5					34
#define	VK_6					35
#define	VK_7					36
#define	VK_8					37
#define	VK_9					38
#define	VK_0					39

#define	VK_RETURN           	40
#define	VK_ESCAPE           	41
#define	VK_BACK             	42
#define	VK_TAB              	43
#define	VK_SPACE            	44

#define VK_OEM_MINUS			45
#define VK_OEM_PLUS				46 // =
#define VK_OEM_4                47 // [
#define VK_OEM_6                48 // ]
#define VK_OEM_5                49 // backslash
#define VK_OEM_1                51 // ;
#define VK_OEM_7                52 // '
#define VK_OEM_3                53 // `
#define VK_OEM_COMMA			54
#define VK_OEM_PERIOD           55
#define VK_OEM_2				56

#define	VK_CAPITAL          	57

#define	VK_F1               	58
#define	VK_F2               	59
#define	VK_F3               	60
#define	VK_F4               	61
#define	VK_F5               	62
#define	VK_F6               	63
#define	VK_F7               	64
#define	VK_F8               	65
#define	VK_F9               	66
#define	VK_F10              	67
#define	VK_F11              	68
#define	VK_F12              	69

#define	VK_SNAPSHOT         	70
#define	VK_SCROLL           	71
#define	VK_PAUSE            	72
#define	VK_INSERT           	73

#define	VK_HOME             	74
#define	VK_PRIOR            	75
#define	VK_DELETE           	76
#define	VK_END              	77
#define	VK_NEXT             	78
#define	VK_RIGHT            	79
#define	VK_LEFT             	80
#define	VK_UP               	81
#define	VK_DOWN             	82

#define	VK_NUMLOCK          	83

#define	VK_DIVIDE               84
#define	VK_MULTIPLY             85
#define	VK_SUBTRACT             86
#define	VK_ADD                  87
#define	VK_NUMPAD1              89
#define	VK_NUMPAD2              90
#define	VK_NUMPAD3              91
#define	VK_NUMPAD4              92
#define	VK_NUMPAD5              93
#define	VK_NUMPAD6              94
#define	VK_NUMPAD7              95
#define	VK_NUMPAD8              96
#define	VK_NUMPAD9              97
#define	VK_NUMPAD0              98
#define	VK_DECIMAL          	99

#define	VK_CLEAR            	VK_NUMPAD5

#define	VK_SELECT           	119
#define	VK_CONTROL          	224
#define	VK_SHIFT            	225
#define	VK_MENU             	226

#define	VK_UPLEFT			  	VK_HOME
#define	VK_UPRIGHT			  	VK_PRIOR
#define	VK_DOWNLEFT			  	VK_END
#define	VK_DOWNRIGHT		  	VK_NEXT
#define	VK_ALT				  	VK_MENU

typedef enum KeyASCIIType {

	KA_NONE				= 0,
	KA_MORE 				= 1,
	KA_SETBKGDCOL 		= 2,
	KA_SETFORECOL 		= 6,
	KA_FORMFEED 		= 12,
	KA_SPCTAB 			= 20,
	KA_SETX 				= 25,
	KA_SETY 				= 26,

	KA_SPACE				= 32,					/*   */
	KA_EXCLAMATION,							/* ! */
	KA_DQUOTE,									/* " */
	KA_POUND,									/* # */
	KA_DOLLAR,									/* $ */
	KA_PERCENT,									/* % */
	KA_AMPER,									/* & */
	KA_SQUOTE,									/* ' */
	KA_LPAREN,									/* ( */
	KA_RPAREN,									/* ) */
	KA_ASTERISK,								/* * */
	KA_PLUS,										/* + */
	KA_COMMA,									/* , */
	KA_MINUS,									/* - */
	KA_PERIOD,									/* . */
	KA_SLASH,									/* / */

	KA_0, KA_1, KA_2, KA_3, KA_4, KA_5, KA_6, KA_7, KA_8, KA_9,
	KA_COLON,									/* : */
	KA_SEMICOLON,								/* ; */
	KA_LESS_THAN,								/* < */
	KA_EQUAL,									/* = */
	KA_GREATER_THAN,							/* > */
	KA_QUESTION,								/* ? */

	KA_AT,										/* @ */
	KA_A,											/* A */
	KA_B,											/* B */
	KA_C,											/* C */
	KA_D,											/* D */
	KA_E,											/* E */
	KA_F,											/* F */
	KA_G,											/* G */
	KA_H,											/* H */
	KA_I,											/* I */
	KA_J,											/* J */
	KA_K,											/* K */
	KA_L,											/* L */
	KA_M,											/* M */
	KA_N,											/* N */
	KA_O,											/* O */

	KA_P,											/* P */
	KA_Q,											/* Q */
	KA_R,											/* R */
	KA_S,											/* S */
	KA_T,											/* T */
	KA_U,											/* U */
	KA_V,											/* V */
	KA_W,											/* W */
	KA_X,											/* X */
	KA_Y,											/* Y */
	KA_Z,											/* Z */
	KA_LBRACKET,								/* [ */
	KA_BACKSLASH,								/* \ */
	KA_RBRACKET,								/* ] */
	KA_CARROT,									/* ^ */
	KA_UNDERLINE,								/* _ */

	KA_GRAVE,									/* ` */
	KA_a,											/* a */
	KA_b,											/* b */
	KA_c,											/* c */
	KA_d,											/* d */
	KA_e,											/* e */
	KA_f,											/* f */
	KA_g,											/* g */
	KA_h,											/* h */
	KA_i,											/* i */
	KA_j,											/* j */
	KA_k,											/* k */
	KA_l,											/* l */
	KA_m,											/* m */
	KA_n,											/* n */
	KA_o,											/* o */

	KA_p,											/* p */
	KA_q,											/* q */
	KA_r,											/* r */
	KA_s,											/* s */
	KA_t,											/* t */
	KA_u,											/* u */
	KA_v,											/* v */
	KA_w,											/* w */
	KA_x,											/* x */
	KA_y,											/* y */
	KA_z,											/* z */
	KA_LBRACE,									/* { */
	KA_BAR,										/* | */
	KA_RBRACE,									/* ] */
	KA_TILDA,									/* ~ */

	KA_ESC 				= '\x1b',
	KA_RETURN 			= '\r',
	KA_BACKSPACE 		= '\b',
	KA_TAB 				= '\t' ,

	KA_SHIFT_BIT 		= WWKEY_SHIFT_BIT,
	KA_CTRL_BIT  		= WWKEY_CTRL_BIT,
	KA_ALT_BIT   		= WWKEY_ALT_BIT,
	KA_RLSE_BIT  		= WWKEY_RLS_BIT,
} KeyASCIIType;


typedef enum KeyNumType {
	KN_NONE				= 0,

	KN_0 					= VK_0,
	KN_1 					= VK_1,
	KN_2 					= VK_2,
	KN_3 					= VK_3,
	KN_4 					= VK_4,
	KN_5 					= VK_5,
	KN_6 					= VK_6,
	KN_7 					= VK_7,
	KN_8 					= VK_8,
	KN_9 					= VK_9,
	KN_A 					= VK_A,
	KN_B 					= VK_B,
	KN_BACKSLASH		= VK_OEM_5,
	KN_BACKSPACE		= VK_BACK,
	KN_C 					= VK_C,
	KN_CAPSLOCK			= VK_CAPITAL,
	KN_CENTER			= VK_CLEAR,
	KN_COMMA 			= VK_OEM_COMMA,
	KN_D 					= VK_D,
	KN_DELETE			= VK_DELETE,
	KN_DOWN				= VK_DOWN,
	KN_DOWNLEFT			= VK_END,
	KN_DOWNRIGHT		= VK_NEXT,
	KN_E 					= VK_E,
	KN_END				= VK_END,
	KN_EQUAL 			= VK_OEM_PLUS,
	KN_ESC				= VK_ESCAPE,
	KN_E_DELETE 		= VK_DELETE,
	KN_E_DOWN			= VK_NUMPAD2,
	KN_E_END				= VK_NUMPAD1,
	KN_E_HOME			= VK_NUMPAD7,
	KN_E_INSERT			= VK_INSERT,
	KN_E_LEFT			= VK_NUMPAD4,
	KN_E_PGDN   		= VK_NUMPAD3,
	KN_E_PGUP			= VK_NUMPAD9,
	KN_E_RIGHT			= VK_NUMPAD6,
	KN_E_UP				= VK_NUMPAD8,
	KN_F 					= VK_F,
	KN_F1					= VK_F1,
	KN_F10				= VK_F10,
	KN_F11				= VK_F11,
	KN_F12				= VK_F12,
	KN_F2					= VK_F2,
	KN_F3					= VK_F3,
	KN_F4					= VK_F4,
	KN_F5					= VK_F5,
	KN_F6					= VK_F6,
	KN_F7					= VK_F7,
	KN_F8					= VK_F8,
	KN_F9					= VK_F9,
	KN_G 					= VK_G,
	KN_GRAVE 			= VK_OEM_3,
	KN_H 					= VK_H,
	KN_HOME				= VK_HOME,
	KN_I 					= VK_I,
	KN_INSERT			= VK_INSERT,
	KN_J 					= VK_J,
	KN_K 					= VK_K,
	KN_KEYPAD_ASTERISK= VK_MULTIPLY,
	KN_KEYPAD_MINUS	= VK_SUBTRACT,
	KN_KEYPAD_PLUS		= VK_ADD,
	KN_KEYPAD_RETURN	= VK_RETURN,
	KN_KEYPAD_SLASH	= VK_DIVIDE,
	KN_L 					= VK_L,
	KN_LALT				= VK_MENU,
	KN_LBRACKET			= VK_OEM_4,
	KN_LCTRL				= VK_CONTROL,
	KN_LEFT				= VK_LEFT,
	KN_LMOUSE			= VK_LBUTTON,
	KN_LSHIFT			= VK_SHIFT,
	KN_M 					= VK_M,
	KN_MINUS 			= VK_OEM_MINUS,
	KN_N 					= VK_N,
	KN_NUMLOCK			= VK_NUMLOCK,
	KN_O 					= VK_O,
	KN_P 					= VK_P,
	KN_PAUSE				= VK_PAUSE,
	KN_PERIOD 			= VK_OEM_PERIOD,
	KN_PGDN				= VK_NEXT,
	KN_PGUP				= VK_PRIOR,
	KN_PRNTSCRN			= VK_SNAPSHOT,
	KN_Q 					= VK_Q,
	KN_R 					= VK_R,
	KN_RALT				= VK_MENU,
	KN_RBRACKET			= VK_OEM_6,
	KN_RCTRL				= VK_CONTROL,
	KN_RETURN 			= VK_RETURN,
	KN_RIGHT				= VK_RIGHT,
	KN_RMOUSE			= VK_RBUTTON,
	KN_RSHIFT			= VK_SHIFT,
	KN_S 					= VK_S,
	KN_SCROLLLOCK		= VK_SCROLL,
	KN_SEMICOLON 		= VK_OEM_1,
	KN_SLASH 			= VK_OEM_2,
	KN_SPACE 			= VK_SPACE,
	KN_SQUOTE 			= VK_OEM_7,
	KN_T 					= VK_T,
	KN_TAB				= VK_TAB,
	KN_U 					= VK_U,
	KN_UP					= VK_UP,
	KN_UPLEFT			= VK_HOME,
	KN_UPRIGHT			= VK_PRIOR,
	KN_V 					= VK_V,
	KN_W 					= VK_W,
	KN_X 					= VK_X,
	KN_Y 					= VK_Y,
	KN_Z 					= VK_Z,

	KN_SHIFT_BIT 		= WWKEY_SHIFT_BIT,
	KN_CTRL_BIT  		= WWKEY_CTRL_BIT,
	KN_ALT_BIT   		= WWKEY_ALT_BIT,
	KN_RLSE_BIT  		= WWKEY_RLS_BIT,
	KN_BUTTON    		= WWKEY_BTN_BIT,
} KeyNumType;

#endif
