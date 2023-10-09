/*
**  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
**  Copyright (c) 1988, 1989, 1990  John Stanback
**
**  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
**
**  Version:    1990-11-17
**
**  Include:    Resource Include (Resource.h)
**
**   Porter:    Ported to Windows 3.0 by Darly Baker
**
**   Porter:    Ported to OS/2 1.2+ by Kent Cedola
**
**   System:    OS2 1.2 using Microsoft C 6.0
**
**  License:
**
**    CHESS is distributed in the hope that it will be useful, but WITHOUT ANY
**    WARRANTY.  No author or distributor accepts responsibility to anyone for
**    the consequences of using it or for whether it serves any particular
**    purpose or works at all, unless he says so in writing.  Refer to the
**    CHESS General Public License for full details.
**
**    Everyone is granted permission to copy, modify and redistribute CHESS,
**    but only under the conditions described in the CHESS General Public
**    License.  A copy of this license is supposed to have been given to you
**    along with CHESS so you can know your rights and responsibilities.  It
**    should be in a file named COPYING.  Among other things, the copyright
**    notice and this notice must be preserved on all copies.
*/


/*
**  Define Window Resource ID's
*/
#define IDR_PMCHESS             32
#define IDR_EDIT                33

/*
**
*/
#define IDB_PAWNBASE            34
#define IDB_PAWN                35
#define IDB_KNIGHT              36
#define IDB_BISHOP              37
#define IDB_ROOK                38
#define IDB_QUEEN               39
#define IDB_KING                40
#define IDB_PAWNM               41
#define IDB_KNIGHTM             42
#define IDB_BISHOPM             43
#define IDB_ROOKM               44
#define IDB_QUEENM              45
#define IDB_KINGM               46
#define IDB_PAWNO               47
#define IDB_KNIGHTO             48
#define IDB_BISHOPO             49
#define IDB_ROOKO               50
#define IDB_QUEENO              51
#define IDB_KINGO               52

/*
**  Define Dialog Resource ID's
*/
#define	IDD_ABOUT	        64
#define	IDD_COLORS              65
#define	IDD_PROMOTE             66
#define	IDD_STATS               67
#define	IDD_TEST                68
#define	IDD_NUMDLG              69
#define IDD_SKILL_TIME          70

/*
**  Define File Menu ID's
*/
#define IDM_FILE                0x0100
#define IDM_FILE_NEW            0x0101
#define IDM_FILE_OPEN           0x0102
#define IDM_FILE_SAVE           0x0103
#define IDM_FILE_SAVEAS         0x0104
#define IDM_FILE_LIST           0x0105
#define IDM_FILE_EXIT           0x0106

/*
**  Define Edit Menu ID's
*/
#define IDM_EDIT                0x0200
#define IDM_EDIT_BOARD          0x0201
#define IDM_EDIT_GAME           0x0202
#define IDM_EDIT_UNDO           0x0203
#define IDM_EDIT_REMOVE         0x0204
#define IDM_EDIT_FORCE          0x0205
#define IDM_EDIT_DONE           0x0206

/*
**  Define Options Menu ID's
*/
#define IDM_OPTIONS             0x0300
#define IDM_OPTIONS_TONE        0x0301
#define IDM_OPTIONS_COOR        0x0302
#define IDM_OPTIONS_STATS       0x0303
#define IDM_OPTIONS_SPEED       0x0304
#define IDM_OPTIONS_HASH        0x0305
#define IDM_OPTIONS_BOTH        0x0306
#define IDM_OPTIONS_BOOK        0x0307
#define IDM_OPTIONS_AWINDOW     0x0308
#define IDM_OPTIONS_BWINDOW     0x0309
#define IDM_OPTIONS_CONTEMP     0x030A

/*
**  Define Skill Menu ID's
*/
#define IDM_SKILL               0x0400
#define IDM_SKILL_TIME          0x0401
#define IDM_SKILL_RANDOM        0x0402
#define IDM_SKILL_EASY          0x0403
#define IDM_SKILL_DEPTH         0x0404

/*
**  Define Side Menu ID's
*/
#define IDM_SIDE                0x0500
#define IDM_SIDE_REVERSE        0x0501
#define IDM_SIDE_SWITCH         0x0502
#define IDM_SIDE_BLACK          0x0503
#define IDM_SIDE_WHITE          0x0504

/*
**  Define Colors Menu ID's
*/
#define IDM_COLORS              0x0600
#define IDM_COLORS_BACKGROUND   0x0601
#define IDM_COLORS_BSQUARES     0x0602
#define IDM_COLORS_WSQUARES     0x0603
#define IDM_COLORS_BPIECES      0x0604
#define IDM_COLORS_WPIECES      0x0605
#define IDM_COLORS_TEXT         0x0606
#define IDM_COLORS_DEFAULT      0x0607

/*
**  Define Colors Menu ID's
*/
#define IDM_HINT                0x0700

/*
**  Define Help Menu ID's
*/
#define IDM_HELP                0x0800
#define IDM_HELP_DISPLAY        0x0801
#define IDM_HELP_EXT            0x0802
#define IDM_HELP_KEYS           0x0803
#define IDM_HELP_INDEX          0x0804
#define IDM_HELP_ABOUT          0x0805


/*
**  Define General Purpose Dialog Control Item ID's
*/
#define IDC_NULL 	   -1
#define IDC_OK              1
#define IDC_CANCEL          2
#define IDC_EDIT 	    3
#define IDC_INFO            4
#define IDC_HELP            5
#define IDC_ADD             6
#define IDC_CHANGE          7
#define IDC_DELETE          8
#define IDC_RESET           9
#define IDC_LISTBOX         10
#define IDC_FILE            11
#define IDC_PATH            12
#define IDC_TYPE            13
#define IDC_DRIVE           14
#define IDC_FILELIST        15
#define IDC_PATHLIST        16


/*
**  File Menu Item Dialog ID's.
*/
#define IDC_FILE_WIDTH              0x1000
#define IDC_FILE_HEIGHT             0x1001
#define IDC_FILE_COLORS             0x1002
#define IDC_FILE_CM                 0x1003
#define IDC_FILE_IN                 0x1004
#define IDC_FILE_PX                 0x1005
#define IDC_FILE_SCREEN             0x1006
#define IDC_FILE_PRINTER            0x1007

/*
**  Define IDD_COLORS Dialog Control Item ID's
*/
#define IDC_COLORS_HEADER           0x2100
#define IDC_COLORS_BLACK            0x2101
#define IDC_COLORS_BLUE             0x2102
#define IDC_COLORS_GREEN            0x2103
#define IDC_COLORS_CYAN             0x2104
#define IDC_COLORS_RED              0x2105
#define IDC_COLORS_PINK             0x2106
#define IDC_COLORS_YELLOW           0x2107
#define IDC_COLORS_PALEGRAY         0x2108
#define IDC_COLORS_DARKGRAY         0x2109
#define IDC_COLORS_DARKBLUE         0x210A
#define IDC_COLORS_DARKGREEN        0x210B
#define IDC_COLORS_DARKCYAN         0x210C
#define IDC_COLORS_DARKRED          0x210D
#define IDC_COLORS_DARKPINK         0x210E
#define IDC_COLORS_BROWN            0x210F
#define IDC_COLORS_WHITE            0x2110

/*
**  Define IDD_PROMOTE Dialog Control Item ID's
*/
#define IDC_PROMOTE_QUEEN           0x2200
#define IDC_PROMOTE_ROOK            0x2201
#define IDC_PROMOTE_BISHOP          0x2202
#define IDC_PROMOTE_KNIGHT          0x2203

/*
**  Define IDD_TEST Dialog Control Item ID's
*/
#define IDC_TEST_MOVELIST           0x2300
#define IDC_TEST_CAPTURELIST        0x2301

/*
**  Define IDD_STATS Dialog Control Item ID's
*/
#define IDC_STATS_DEPTH             0x2400
#define IDC_STATS_POSITION          0x2401
#define IDC_STATS_SCORE             0x2402
#define IDC_STATS_NODES             0x2403
#define IDC_STATS_RATE              0x2404
#define IDC_STATS_BEST              0x2405

/*
**  Define IDD_SKILL_TIME Dialog Control Item ID's
*/
#define IDC_SKILL_T5            0x0405
#define IDC_SKILL_T15           0x0406
#define IDC_SKILL_T30           0x0407
#define IDC_SKILL_T60           0x0408
#define IDC_SKILL_T600          0x0409
#define IDC_SKILL_M1            0x040A
#define IDC_SKILL_M10           0x040B
#define IDC_SKILL_M20           0x040C
#define IDC_SKILL_M40           0x040D
#define IDC_SKILL_M60           0x040E

/*
**  Define IDD_NUMDLG Dialog Control Item ID's
*/
#define IDC_NUMDLG_CHAR             0x2500
#define IDC_NUMDLG_INT              0x2501


/*
**  Define String Resource ID's
*/
#define IDS_CHESS                    1
#define IDS_ILLEGALMOVE              2
#define IDS_AMBIGUOUSMOVE            3
#define IDS_OBAE                     4
#define IDS_OBNF                     5
#define IDS_UNABLESAVE               6
#define IDS_UNABLELIST               7
#define IDS_DRAWGAME                 8
#define IDS_YOUWIN                   9
#define IDS_COMPUTERWIN             10
#define IDS_MATESOON                11
#define IDS_COMPMATE                12
#define IDS_TTABLEAF                13
#define IDS_SQDATAAF                14
#define IDS_HISTORYAF               15
#define IDS_TREEAF                  16
#define IDS_GAMEAF                  17
#define IDS_LOADFAILED              18
#define IDS_SETAWIN                 19
#define IDS_SETBWIN                 20
#define IDS_SETCONTEMPT             21
#define IDS_MAXSEARCH               22
#define IDS_INITERROR               23
