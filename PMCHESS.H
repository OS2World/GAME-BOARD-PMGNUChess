//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//  Copyright (C) 1988, 1989, 1990  John Stanback
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//  Include:    Main Include (PmChess.h)
//
//   Porter:    Ported to Windows 3.0 by Darly Baker
//
//   Porter:    Ported to OS/2 1.2+ by Kent Cedola
//
//   System:    OS2 1.2 using Microsoft C 6.0
//
//  License:
//
//    CHESS is distributed in the hope that it will be useful, but WITHOUT ANY
//    WARRANTY.  No author or distributor accepts responsibility to anyone for
//    the consequences of using it or for whether it serves any particular
//    purpose or works at all, unless he says so in writing.  Refer to the
//    CHESS General Public License for full details.
//
//    Everyone is granted permission to copy, modify and redistribute CHESS,
//    but only under the conditions described in the CHESS General Public
//    License.  A copy of this license is supposed to have been given to you
//    along with CHESS so you can know your rights and responsibilities.  It
//    should be in a file named COPYING.  Among other things, the copyright
//    notice and this notice must be preserved on all copies.
//


//
//  Define global defines.
//
#define MAX_PATH            260

#define BLACK   1
#define WHITE   2

#define NETURAL 2

#define UM_EDITBOARD            (WM_USER+0)
#define UM_USER_MOVE            (WM_USER+1)
#define UM_COMPUTER_MOVE        (WM_USER+2)
#define UM_USER_ENTERED_MOVE    (WM_USER+3)


//
//  Define global variables.
//
extern HAB  hab;                        // Primary thread anchor block.
extern HMQ  hmq;                        // Message queue handle.

extern HWND hwndFrame;                  // Frame window handle.
extern HWND hwndClient;                 // Client window handle.
extern HPS  hpsClient;                  // Presentation space of Client window.
extern HWND hwndMenu;                   // Menu window handle.

extern short cyClient;                  // Height of client area.

extern char szAppName[];                // Application name.

extern short boarddraw[64]; /* Display copies of the board */
extern short colordraw[64]; /* Needed because while computer is calculating*/
                            /* moves it updates board and color thus you can*/
                            /* not repaint the screen accuratly */
