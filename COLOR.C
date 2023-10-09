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
//              method with some editing improvements.  Based on ideas and
//              code segments of Charles Petzold from artices in Microsoft
//              Systems Journal.
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
#define INCL_GPI
#define INCL_PM
#include <os2.h>
#include <stdio.h>
#include <string.h>
#include "PmChess.h"
#include "Resource.h"


extern ULONG clrBackGround;
extern ULONG clrBlackSquare;
extern ULONG clrWhiteSquare;
extern ULONG clrBlackPiece;
extern ULONG clrWhitePiece;
extern ULONG clrText;

extern HWND hComputerColor;
extern HWND hComputerMove;
extern HWND hWhosTurn;
extern HWND hClockComputer;
extern HWND hClockHuman;
extern HWND hMsgComputer;
extern HWND hMsgHuman;

//
//  Define dialog procedure's prototypes.
//
MRESULT EXPENTRY ColorProc(HWND hWnd, USHORT msg, MPARAM mp1, MPARAM mp2);



static char lpChessini[]    = "chess.ini";
static char lpBackGround[]  = "BackGround";
static char lpBlackSquare[] = "BlackSquare";
static char lpWhiteSquare[] = "WhiteSquare";
static char lpBlackPiece[]  = "BlackPiece";
static char lpWhitePiece[]  = "WhitePiece";
static char lpDefault[]     = "Default";
static char lpText[]        = "Text";

static char np08lX[] = "%08lX";


void UpdateChilds()
  {
  WinSetPresParam(hComputerColor, PP_BACKGROUNDCOLORINDEX,
                  sizeof(LONG), &clrBackGround);
  WinSetPresParam(hWhosTurn,      PP_BACKGROUNDCOLORINDEX,
                  sizeof(LONG), &clrBackGround);
  WinSetPresParam(hComputerMove,  PP_BACKGROUNDCOLORINDEX,
                  sizeof(LONG), &clrBackGround);
  WinSetPresParam(hClockComputer,  PP_BACKGROUNDCOLORINDEX,
                  sizeof(LONG), &clrBackGround);
  WinSetPresParam(hClockHuman,  PP_BACKGROUNDCOLORINDEX,
                  sizeof(LONG), &clrBackGround);
  WinSetPresParam(hMsgComputer,  PP_BACKGROUNDCOLORINDEX,
                  sizeof(LONG), &clrBackGround);
  WinSetPresParam(hMsgHuman, PP_BACKGROUNDCOLORINDEX,
                  sizeof(LONG), &clrBackGround);
  }


void SetStandardColors ( VOID )
  {
  clrBackGround  = CLR_CYAN;
  clrBlackSquare = CLR_DARKGREEN;
  clrWhiteSquare = CLR_PALEGRAY;
  clrBlackPiece  = CLR_RED;
  clrWhitePiece  = CLR_WHITE;
  clrText        = CLR_BLACK;

  UpdateChilds();
  }


void SaveColors(PSZ appname )
  {
  HINI hIni;
  char ostring[30];


  hIni = PrfOpenProfile(hab, lpChessini);

   sprintf ( ostring, np08lX, clrBackGround);
   PrfWriteProfileString (hIni, appname, lpBackGround,ostring);

   sprintf ( ostring, np08lX, clrBlackSquare);
   PrfWriteProfileString (hIni, appname, lpBlackSquare,ostring);
   
   sprintf ( ostring, np08lX, clrWhiteSquare);
   PrfWriteProfileString (hIni, appname, lpWhiteSquare,ostring);
   
   sprintf ( ostring, np08lX, clrBlackPiece);
   PrfWriteProfileString (hIni, appname, lpBlackPiece,ostring);

   sprintf ( ostring, np08lX, clrWhitePiece);
   PrfWriteProfileString (hIni, appname, lpWhitePiece,ostring);

   sprintf ( ostring, np08lX, clrText);
   PrfWriteProfileString (hIni, appname, lpText,ostring);

  PrfCloseProfile(hIni);
  }

void GetStartupColors ( PSZ appname )
{
  HINI hIni;
  char istring[30];


  hIni = PrfOpenProfile(hab, lpChessini);

   SetStandardColors ();

   PrfQueryProfileString (hIni, appname, lpBackGround,lpDefault,istring,
                             sizeof(istring));
   if (strcmp ( istring, lpDefault) != 0)  sscanf ( istring, np08lX, &clrBackGround);

   PrfQueryProfileString (hIni, appname, lpBlackSquare,lpDefault,istring,
                             sizeof(istring));
   if (strcmp ( istring, lpDefault) != 0)  sscanf ( istring, np08lX, &clrBlackSquare);

   PrfQueryProfileString (hIni, appname, lpWhiteSquare,lpDefault,istring,
                             sizeof(istring));
   if (strcmp ( istring, lpDefault) != 0)  sscanf ( istring, np08lX, &clrWhiteSquare);

   PrfQueryProfileString (hIni, appname, lpBlackPiece,lpDefault,istring,
                             sizeof(istring));
   if (strcmp ( istring, lpDefault) != 0)  sscanf ( istring, np08lX, &clrBlackPiece);

   PrfQueryProfileString (hIni, appname, lpWhitePiece,lpDefault,istring,
                             sizeof(istring));
   if (strcmp ( istring, lpDefault) != 0)  sscanf ( istring, np08lX, &clrWhitePiece);

   PrfQueryProfileString (hIni, appname, lpText,lpDefault,istring,
                             sizeof(istring));
   if (strcmp ( istring, lpDefault) != 0)  sscanf ( istring, np08lX, &clrText);

  PrfCloseProfile(hIni);


  UpdateChilds();
}


int ColorDialog(HWND hWnd, ULONG Param )
  {
  int status;

  status = (int)(LONG)WinDlgBox(HWND_DESKTOP, hWnd, ColorProc, 0, IDD_COLORS,
                           (PVOID)Param);
  if (status)
    UpdateChilds();

  return (status);
  }


static int ColorToIndex ( ULONG color)
{
   if (color == CLR_BLACK ) return IDC_COLORS_BLACK;
   else if ( color == CLR_BLUE) return IDC_COLORS_BLUE;
   else if ( color == CLR_GREEN) return IDC_COLORS_GREEN;
   else if ( color == CLR_CYAN) return IDC_COLORS_CYAN;
   else if ( color == CLR_RED) return IDC_COLORS_RED;
   else if ( color == CLR_PINK) return IDC_COLORS_PINK;
   else if ( color == CLR_YELLOW) return IDC_COLORS_YELLOW;
   else if ( color == CLR_PALEGRAY) return IDC_COLORS_PALEGRAY;
   else if ( color == CLR_DARKGRAY) return IDC_COLORS_DARKGRAY;
   else if ( color == CLR_DARKBLUE) return IDC_COLORS_DARKBLUE;
   else if ( color == CLR_DARKGREEN) return IDC_COLORS_DARKGREEN;
   else if ( color == CLR_DARKCYAN) return IDC_COLORS_DARKCYAN;
   else if ( color == CLR_DARKRED) return IDC_COLORS_DARKRED;
   else if ( color == CLR_DARKPINK) return IDC_COLORS_DARKPINK;
   else if ( color == CLR_BROWN) return IDC_COLORS_BROWN;
   else if ( color == CLR_WHITE) return IDC_COLORS_WHITE;
   return IDC_COLORS_WHITE;
}

static ULONG IndexToColor ( int color)
{
   if (color == IDC_COLORS_BLACK ) return  CLR_BLACK;
   else if ( color == IDC_COLORS_BLUE) return  CLR_BLUE;
   else if ( color == IDC_COLORS_GREEN) return  CLR_GREEN;
   else if ( color == IDC_COLORS_CYAN) return  CLR_CYAN;
   else if ( color == IDC_COLORS_RED) return  CLR_RED;
   else if ( color == IDC_COLORS_PINK) return  CLR_PINK;
   else if ( color == IDC_COLORS_YELLOW) return  CLR_YELLOW;
   else if ( color == IDC_COLORS_PALEGRAY) return  CLR_PALEGRAY;
   else if ( color == IDC_COLORS_DARKGRAY) return  CLR_DARKGRAY;
   else if ( color == IDC_COLORS_DARKBLUE) return  CLR_DARKBLUE;
   else if ( color == IDC_COLORS_DARKGREEN) return  CLR_DARKGREEN;
   else if ( color == IDC_COLORS_DARKCYAN) return  CLR_DARKCYAN;
   else if ( color == IDC_COLORS_DARKRED) return  CLR_DARKRED;
   else if ( color == IDC_COLORS_DARKPINK) return  CLR_DARKPINK;
   else if ( color == IDC_COLORS_BROWN) return  CLR_BROWN;
   else if ( color == IDC_COLORS_WHITE) return  CLR_WHITE;
   return CLR_RED;
}

static char lpWBGC[] ="Window background color";
static char lpBS[]   ="Black square color";
static char lpWS[]   ="White square color";
static char lpBP[]   ="Black piece color";
static char lpWP[]   ="White piece color";
static char lpTX[]   ="Text color";

static ULONG *pclr;
static int index;

MRESULT EXPENTRY ColorProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2)
  {
  char *pchHeading;


  switch (msg)
    {
    case WM_INITDLG:
      switch (LONGFROMMP(mp2))
        {
        case IDM_COLORS_BSQUARES:
          pchHeading = (char *)lpBS;
          pclr       = &clrBlackSquare;
          break;

        case IDM_COLORS_WSQUARES:
          pchHeading = (char *)lpWS;
          pclr       = &clrWhiteSquare;
          break;

        case IDM_COLORS_BPIECES:
          pchHeading = (char *) lpBP;
          pclr       = &clrBlackPiece;
          break;

        case IDM_COLORS_WPIECES:
          pchHeading = (char *) lpWP;
          pclr       = &clrWhitePiece;
          break;

        case IDM_COLORS_TEXT:
          pchHeading = (char *) lpTX;
          pclr       = &clrText;
          break;

        default:
          pchHeading = (char *) lpWBGC;
          pclr       = &clrBackGround;
          break;

         }

      WinSetDlgItemText(hDlg, IDC_COLORS_HEADER, pchHeading);
      index = ColorToIndex( *pclr);

      WinSendDlgItemMsg(hDlg, index, BM_SETCHECK, MPFROMSHORT(TRUE), NULL);

      WinSetFocus (HWND_DESKTOP, WinWindowFromID(hDlg, index));

      return ((MRESULT)TRUE);

    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1))
        {
        case IDC_OK:
          *pclr = IndexToColor (index);
          WinDismissDlg(hDlg, TRUE);
          break;

        case IDC_CANCEL:
          WinDismissDlg(hDlg, FALSE);
          break;
        }
      return (0);

    case WM_CONTROL:
      WinSendDlgItemMsg(hDlg, index, BM_SETCHECK, MPFROMSHORT(FALSE), NULL);
      index = SHORT1FROMMP(mp1);
      WinSendDlgItemMsg(hDlg, index, BM_SETCHECK, MPFROMSHORT(TRUE), NULL);
      return 0 ;
    }

  return (WinDefDlgProc(hDlg, msg, mp1, mp2));
  }
