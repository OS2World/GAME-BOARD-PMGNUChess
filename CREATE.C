//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//  Copyright (c) 1988, 1989, 1990  John Stanback
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//   Module:    Color Support Logic (Color.c)
//
//   Porter:    Ported to Windows 3.0 by Darly Baker
//
//   Porter:    Ported to OS/2 1.2+ by Kent Cedola
//
//   System:    OS2 1.2 using Microsoft C 6.0
//
//  Remarks:    This code converted from Windows to PM using a straight port
//              method with some editing improvements.
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

#define INCL_DOS
#define INCL_PM
#include <OS2.h>
#include <Stdio.h>
#include "PmChess.h"
#include "Defs.h"


extern HWND hComputerColor;
extern HWND hComputerMove;
extern HWND hWhosTurn;
extern HWND hClockComputer;
extern HWND hClockHuman;
extern HWND hMsgComputer;
extern HWND hMsgHuman;


void Create_Children(HWND hWnd, short xchar, short ychar)
{
   POINTL pt;

   /* Get the location of lower left conor of client area */
   QueryBoardSize ( &pt);
   
            hComputerColor = WinCreateWindow (hWnd, WC_STATIC,
	                     NULL,
                     	SS_TEXT | DT_CENTER | WS_VISIBLE,
                     	0,
                     	cyClient - (SHORT)pt.y - ychar * 3 + 5,
                     	10*xchar,
                     	ychar,
                       	hWnd, HWND_TOP, 1000, NULL, NULL);

         hWhosTurn = WinCreateWindow (hWnd, WC_STATIC,
	                     NULL,
                     	SS_TEXT | DT_CENTER | WS_VISIBLE,
                     	10*xchar,
                     	cyClient - (SHORT)pt.y - ychar * 3 + 5,
                     	10*xchar,
                     	ychar,
                     	hWnd, HWND_TOP, 1001, NULL, NULL);

         hComputerMove = WinCreateWindow (hWnd, WC_STATIC,
	                     NULL,
                     	SS_TEXT | DT_LEFT | WS_VISIBLE,
                     	375 /*0*/,
                     	cyClient - (SHORT)pt.y - ychar * 3 + 5/*pt.y+(3*ychar)/2*/,
                     	10*xchar,
                     	ychar,
                       	hWnd, HWND_TOP, 1003, NULL, NULL);


         hClockComputer =  WinCreateWindow (hWnd,  WC_STATIC, NULL,
                     	SS_TEXT | DT_CENTER | WS_VISIBLE,
                        390, cyClient - 55 - 4, 6*xchar, ychar, hWnd,
                        HWND_TOP, 1010, NULL, NULL);

         hClockHuman =  WinCreateWindow (hWnd,  WC_STATIC, NULL,
                     	SS_TEXT | DT_CENTER | WS_VISIBLE,
                        390, cyClient - (55+3*ychar) - 4, 6*xchar, ychar, hWnd,
                        HWND_TOP, 1011, NULL, NULL);

         hMsgComputer = WinCreateWindow (hWnd,  WC_STATIC, "Computer:",
                     	SS_TEXT | DT_CENTER | WS_VISIBLE,
                        390, cyClient - (55-3*ychar/2) - 4, 6*xchar, ychar, hWnd,
                        HWND_TOP, 1020, NULL, NULL);

         hMsgHuman    = WinCreateWindow (hWnd,  WC_STATIC, "You:",
                      	SS_TEXT | DT_CENTER | WS_VISIBLE,
                        390, cyClient - (55+3*ychar/2) - 4, 6*xchar, ychar, hWnd,
                        HWND_TOP, 1021, NULL, NULL);
}
 
