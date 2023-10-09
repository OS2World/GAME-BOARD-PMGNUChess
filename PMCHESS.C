//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//  Copyright (c) 1988, 1989, 1990  John Stanback
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//   Module:    Main Module (PmChess.c)
//
//   Porter:    Ported to Windows 3.0 by Darly Baker
//
//   Porter:    Ported to OS/2 1.2+ by Kent Cedola
//
//   System:    OS2 1.2 using Microsoft C 6.0
//
//  Remarks:    For the most part the port to OS/2 PM was a hard port with
//              very little cleaning up of the old code.  Sections with the
//              double slash '//' is my doing.
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
#define INCL_WIN
#include <os2.h>
#include <string.h>
#include <time.h>
#include "PmChess.h"
#include "GnuChess.h"
#include "Defs.h"
#include "Resource.h"


//
//  Define global variables.
//
  HAB  hab;                             // Primary thread anchor block.
  HMQ  hmq;                             // Message queue handle.

  HWND hwndFrame;                       // Frame window handle.
  HWND hwndClient;                      // Client window handle.
  HPS  hpsClient;
  HWND hwndMenu;                        // Menu window handle.

  short cyClient;                       // Height of client area.

  char szAppName[] = "PmChess";         // Application name.

  short boarddraw[64];       /* Display copies of the board */
  short colordraw[64];       /* Needed because while computer is calculating*/
                             /* moves it updates board and color thus you can*/
                             /* not repaint the screen accuratly */

  ULONG clrBackGround;       /* color index for various colors */
  ULONG clrBlackSquare;
  ULONG clrWhiteSquare;
  ULONG clrBlackPiece;
  ULONG clrWhitePiece;
  ULONG clrText;

  short xchar, ychar;
  short coords = 1;

//
//  Define local variables.
//
  static BOOL FirstSq   = -1;           // Flag is a square is selected
  static int GotFirst   = FALSE;
  static int EditActive = FALSE;        /* Edit mode? */
  static int User_Move  = TRUE;         /* User or computer's turn */
  static char szClass[] = "PmChess";    // Class name of main window procedure.
  static HPS  hpsPieces;                // Memory PS of all chess pieces.


//
//  Define prototypes of local routines.
//
void    cdecl    main(short argc, char **argv);
MRESULT EXPENTRY ChessProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);
static  void     WndCreate(HWND hWnd);
static  void     WndPaint(HWND hWnd);
static  void     WndButton(HWND hWnd, USHORT msg, MPARAM mp1);
static  void     WndDestroy(void);
MRESULT EXPENTRY AboutProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2);


//***************************************************************************
//
//  Routine: main(In, In)
//
//  Remarks: This routine is then entry-point called by the OS/2 executive.
//
//  Returns: None.
//
void cdecl main(short argc, char **argv)
  {
  QMSG   qmsg;
  ULONG  ctlData;
  POINTL ptl;


  //
  //  Allocate an anchor block and message queue to use PM services.
  //
  hab = WinInitialize(0);
  hmq = WinCreateMsgQueue(hab, 0);

  //
  //  Register the main window procedure.
  //
  if (!WinRegisterClass(NULL, szClass, ChessProc, CS_SIZEREDRAW, 0))
    {
    //
    //  This should never happen...
    //
    WinMessageBox(HWND_DESKTOP, NULL, "Register Class Failure", szAppName, 0,
                  MB_OK);
    goto Error;
    }

  //
  //  Compute the idea client height.
  //
  QueryBoardSize(&ptl);
  cyClient = (SHORT)(ptl.y + WinQuerySysValue(HWND_DESKTOP, SV_CYSIZEBORDER)
             * 2L+ WinQuerySysValue(HWND_DESKTOP, SV_CYMENU)+
             WinQuerySysValue(HWND_DESKTOP, SV_CYTITLEBAR) +
             (LONG)ychar * 2L);

  //
  //  Define the control fields for creating a standard frame window.
  //
  ctlData = FCF_TITLEBAR | FCF_MINMAX | FCF_SIZEBORDER | FCF_SYSMENU |
            FCF_MENU | FCF_TASKLIST | FCF_SHELLPOSITION | FCF_ICON |
            FCF_PALETTE_NORMAL;

  //
  //  Create our main frame window that makes us who we are.
  //
  hwndFrame = WinCreateStdWindow(HWND_DESKTOP, WS_VISIBLE, &ctlData,
                                 szClass, NULL, WS_VISIBLE, 0, IDR_PMCHESS,
                                 &hwndClient);

  //
  //  Make sure the frame window creation was successful.
  //
  if (hwndFrame == NULL)
    {
    //
    //  This should almost never happen...
    //
    WinMessageBox(HWND_DESKTOP, NULL, "Window Create Failure", szAppName, 0,
                  MB_OK);
    goto Error;
    }

  //
  //  Retrieve the menu handle to speed up future processing.
  //
  hwndMenu = WinWindowFromID(hwndFrame, FID_MENU);

  //
  //  Size the frame window to our standard size.
  //
  QueryBoardSize(&ptl);
  WinSetWindowPos(hwndFrame, NULL, 32, 32,
                  (SHORT)(ptl.x+WinQuerySysValue(HWND_DESKTOP, SV_CXSIZEBORDER)*2L+50L),
                  (SHORT)(ptl.y+WinQuerySysValue(HWND_DESKTOP, SV_CYSIZEBORDER)*2+
                  WinQuerySysValue(HWND_DESKTOP, SV_CYMENU)+
                  WinQuerySysValue(HWND_DESKTOP, SV_CYTITLEBAR) + (LONG)ychar * 2L),
                  SWP_MOVE | SWP_SIZE);

  //
  //  Initialize the GNU Chess Logic...
  //
  init_main(hwndFrame);
  player = opponent;
  ShowSidetoMove();

  //
  //  The heart of an event driven system, the message dispatch loop.
  //
  while (WinGetMsg(hab, &qmsg, NULL, 0, 0))
    WinDispatchMsg(hab, &qmsg);

  //
  //  Release the anchor block and message queue as we are terminating.
  //
Error:
  WinDestroyMsgQueue(hmq);
  WinTerminate(hab);

  DosExit(EXIT_PROCESS, 0);
  }


//***************************************************************************
//
//  WndProc: ChessProc(In, In, In, In)
//
//  Remarks: This routine is then entry-point called by the OS/2 executive.
//
//  Returns: Depends on message processed.
//
MRESULT EXPENTRY ChessProc(HWND hWnd, USHORT msg, MPARAM mp1, MPARAM mp2)
  {
  HWND hwndOldMenu;
  CHAR szBuf[64];


  switch (msg)
    {
    case WM_CREATE:
      WndCreate(hWnd);
      return (0);

    case WM_DESTROY:
      WndDestroy();
      break;

    case WM_PAINT:
      WndPaint(hWnd);
      break;

    case WM_ERASEBACKGROUND:
      WinFillRect(PVOIDFROMMP(mp1), PVOIDFROMMP(mp2), clrBackGround);
      break;

    case WM_SIZE:
      cyClient = SHORT2FROMMP(mp2);
      break;

    case WM_BUTTON1DOWN:
      WndButton(hWnd, msg, mp1);
      break;

    case WM_INITMENU:
      if ( User_Move ) {            /*Abort thinklook ahead*/
         flag.timeout = true;
         flag.bothsides = false;
         }

      if (!EditActive)
        Init_Menus(hWnd, mp1, mp2);
      break;

    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1))
        {
        case IDM_FILE_NEW:
          NewGame(hWnd);
          GetOpenings(hWnd);
          break;

        case IDM_FILE_OPEN:
          break;

        case IDM_FILE_SAVE:
          break;

        case IDM_FILE_SAVEAS:
          break;

        case IDM_FILE_LIST:
          break;

        case IDM_FILE_EXIT:
          WinDestroyWindow(hWnd);
          break;

        case IDM_EDIT_BOARD:
          EditActive = TRUE;
          hwndOldMenu = WinWindowFromID(hwndFrame, FID_MENU);
          WinLoadMenu(hwndFrame, 0, IDR_EDIT);
          WinSendMsg(hwndFrame, WM_UPDATEFRAME, NULL, NULL);
          WinDestroyWindow(hwndOldMenu);
          break;

        case IDM_EDIT_DONE:
          EditActive = FALSE;
          hwndOldMenu = WinWindowFromID(hwndFrame, FID_MENU);
          WinLoadMenu(hwndFrame, 0, IDR_PMCHESS);
          WinSendMsg(hwndFrame, WM_UPDATEFRAME, NULL, NULL);
          WinDestroyWindow(hwndOldMenu);

          GameCnt = 0;
          Game50 = 1;
          ZeroRPT ();
          Sdepth = 0;
          InitializeStats();
          WinPostMsg(hWnd, UM_USER_MOVE, NULL, NULL);
          break;

        case IDM_EDIT_GAME:
          //ReviewDialog(hWnd);
          break;

        case IDM_EDIT_UNDO:
          if (GameCnt > 0)
            Undo(hWnd);
          break;

        case IDM_EDIT_REMOVE:
          if (GameCnt > 1)
            {
            Undo(hWnd);
            Undo(hWnd);
            }
          break;

        case IDM_EDIT_FORCE:
          computer = opponent;
          opponent = otherside[computer];
          ShowPlayers();
          WinPostMsg(hWnd, UM_COMPUTER_MOVE, NULL, NULL);
          break;

        case IDM_OPTIONS_TONE:
          flag.beep = !flag.beep;
          break;

        case IDM_OPTIONS_COOR:
          coords = !coords;
          UpdateDisplay(hWnd, 0, 0, 1, 0);
          break;

        case IDM_OPTIONS_STATS:
          if (flag.post)
            {
            WinSendMsg(hStats, WM_SYSCOMMAND, MPFROMSHORT(SC_CLOSE), NULL);
            flag.post = false;
            }
          else
            {
            StatDialog(hWnd);
            flag.post = TRUE;
            }
          break;

        case IDM_OPTIONS_SPEED:
          TestDialog(hWnd);
          break;

        case IDM_OPTIONS_HASH:
          flag.hash = !flag.hash;
          break;

        case IDM_OPTIONS_BOTH:
          flag.bothsides = !flag.bothsides;
          flag.easy = true;
          Sdepth = 0;
          WinPostMsg(hWnd, UM_USER_MOVE, NULL, NULL);
          break;

        case IDM_OPTIONS_BOOK:
          Book = NULL;
          break;

        case IDM_OPTIONS_AWINDOW:
          WinLoadString(hab, 0, IDS_SETAWIN, sizeof(szBuf), szBuf);
          Awindow = DoGetNumberDlg(hWnd, szBuf, Awindow);
          break;

        case IDM_OPTIONS_BWINDOW:
          WinLoadString(hab, 0, IDS_SETBWIN, sizeof(szBuf), szBuf);
          Bwindow = DoGetNumberDlg(hWnd, szBuf, Bwindow);
          break;

        case IDM_OPTIONS_CONTEMP:
          WinLoadString(hab, 0, IDS_SETCONTEMPT, sizeof(szBuf), szBuf);
          contempt = DoGetNumberDlg(hWnd, szBuf, contempt);
          break;

        case IDM_SKILL_TIME:
          if (TimeControlDialog(hWnd))
            {
            TCflag = (TCmoves > 1);

            SetTimeControl();
            }
          break;

        case IDM_SKILL_RANDOM:
          if (dither == 0)
            dither = 6;
          else
            dither = 0;
          break;

        case IDM_SKILL_EASY:
          flag.easy = !flag.easy;
          break;

        case IDM_SKILL_DEPTH:
          WinLoadString(hab, 0, IDS_MAXSEARCH, sizeof(szBuf), szBuf);
          MaxSearchDepth = DoGetNumberDlg(hWnd, szBuf, MaxSearchDepth);
          break;

        case IDM_SIDE_REVERSE:
          flag.reverse = !flag.reverse;
          ShowPlayers();
          UpdateDisplay(hWnd, 0, 0, 1, 0);
          break;

        case IDM_SIDE_SWITCH:
          computer = otherside[computer];
          opponent = otherside[opponent];
          flag.force = false;
          Sdepth = 0;
          ShowPlayers();
          WinPostMsg(hWnd, UM_COMPUTER_MOVE, NULL, NULL);
          break;

        case IDM_SIDE_BLACK:
          computer = black;
          opponent = white;
          flag.force = false;
          Sdepth = 0;
          ShowPlayers();
          WinPostMsg(hWnd, UM_COMPUTER_MOVE, NULL, NULL);
          break;

        case IDM_SIDE_WHITE:
          computer = white;
          opponent = black;
          flag.force = false;
          Sdepth = 0;
          ShowPlayers();
          WinPostMsg(hWnd, UM_COMPUTER_MOVE, NULL, NULL);
          break;

        case IDM_COLORS_BACKGROUND:
        case IDM_COLORS_BSQUARES:
        case IDM_COLORS_WSQUARES:
        case IDM_COLORS_BPIECES:
        case IDM_COLORS_WPIECES:
        case IDM_COLORS_TEXT:
          if (ColorDialog(hWnd, (LONG)(SHORT1FROMMP(mp1))))
            WinInvalidateRect(hWnd, NULL, TRUE);
          break;

        case IDM_COLORS_DEFAULT:
          SetStandardColors ();
          WinInvalidateRect(hWnd, NULL, TRUE);
          break;

        case IDM_HINT:
          GiveHint(hWnd);
          break;

        case IDM_HELP_ABOUT:
          WinDlgBox(HWND_DESKTOP, hWnd, AboutProc, 0, IDD_ABOUT, NULL);
          break;
        }
      return (0);

    case UM_EDITBOARD:
      {
      int Square, First;

      if ( flag.reverse ) {
        First = 63 - ((SHORT1FROMMP(mp1) >> 8) & 0xff);
        Square  = 63 - (SHORT1FROMMP(mp1) & 0xff);
      } else {
        First = (SHORT1FROMMP(mp1) >>8) & 0xff;
        Square  = SHORT1FROMMP(mp1) & 0xff;
      }
         
      board[Square] = board[First];
      color[Square] = color[First];

      board[First] = no_piece;
      color[First] = neutral;

      UpdateDisplay(hWnd, First, Square, false, false);
      }
      break;

    case UM_USER_MOVE:
         if ( flag.bothsides && !flag.mate ) {
            SelectMove ( hWnd, opponent, 1);
            if ( flag.beep ) WinAlarm(HWND_DESKTOP, WA_NOTE);
            WinPostMsg( hWnd, UM_COMPUTER_MOVE, NULL, NULL);
         } else if (!flag.mate) {
            User_Move = TRUE;

            ft = 0;
            player = opponent;
            ShowSidetoMove ();
         {
            /* Set up to allow computer to think while user takes move*/
            int tmp; unsigned short mv; char s[10];
            if ( hint>0 && !flag.easy && Book == NULL) {
               time0 = time ( NULL);
               algbr ( hint>>8, hint&0xff, false);
               strcpy ( s, mvstr[0]);
               tmp = epsquare;
               if ( VerifyMove (hWnd, s,1, &mv) ) {
                  SelectMove ( hWnd, computer, 2);
                  VerifyMove ( hWnd, mvstr[0], 2, &mv);
                  if ( Sdepth>0 ) Sdepth --;
               }
               ft = time (NULL) - time0;
               epsquare = tmp;
            }
            }
         }
      break;

    case UM_USER_ENTERED_MOVE:
      {
         int temp; unsigned short mv; int Square,First; char str[10];
         int algbr_flag;
         User_Move = FALSE;
         player = opponent;

         /* Fix coord's if user "reversed" board */
         if ( flag.reverse ) {
            First = 63 - ((SHORT1FROMMP(mp1) >>8) & 0xff);
            Square  = 63 - (SHORT1FROMMP(mp1) & 0xff);
         } else {
            First = (SHORT1FROMMP(mp1) >>8) & 0xff;
            Square  = SHORT1FROMMP(mp1) & 0xff;
         }

         /* Logic to allow selection for pawn promotion */
         if ( (board[First] == pawn) &&( (Square <8) || (Square>55)) ) {
            algbr_flag = promote + PromoteDialog (hWnd);
         } else algbr_flag = 0;
         algbr ( First, Square, algbr_flag);

         strcpy ( str, mvstr[0] );
         
         temp = VerifyMove ( hWnd, str, 0, &mv);
         if ( temp && (mv != hint)) {
            Sdepth = 0;
            ft = 0;
            ElapsedTime (1);
            WinPostMsg( hWnd, UM_COMPUTER_MOVE, NULL, NULL);
         } else if ( temp == TRUE) {
            ElapsedTime (1);
            WinPostMsg ( hWnd, UM_COMPUTER_MOVE, NULL, NULL);
         } else WinPostMsg ( hWnd, UM_USER_MOVE, NULL, NULL);
      }
      break;

    case UM_COMPUTER_MOVE:
         if ( !(flag.quit || flag.mate || flag.force) ) {
            SelectMove ( hWnd, computer, 1);
            if ( flag.beep ) WinAlarm(HWND_DESKTOP, WA_NOTE);
         }
         WinPostMsg( hWnd, UM_USER_MOVE, NULL, NULL);
      break;
    }

  return (WinDefWindowProc(hWnd, msg, mp1, mp2));
  }


//***************************************************************************
//
//  Routine: WndCreate(In):Static
//
//  Remarks: This routine processed the WM_CREATE message from the main
//           client window.
//
//  Returns: None.
//
static void WndCreate(HWND hWnd)
  {
  FONTMETRICS fm;


  hpsClient = WinGetPS(hWnd);

  //
  //  Load all the chess piece's bitmaps into a master memory ps for later.
  //
  hpsPieces = LoadChessPieces(hab);

  //
  //  Load the diamensions of the default system font.
  //
  GpiQueryFontMetrics(hpsClient, sizeof(fm), &fm);
  xchar = (SHORT)fm.lEmInc;
  ychar = (SHORT)fm.lMaxBaselineExt+(SHORT)fm.lExternalLeading;

  Create_Children(hWnd, xchar, ychar);

  GetStartupColors(szAppName);
  }


//***************************************************************************
//
//  Routine: WndDestroy():Static
//
//  Remarks: This routine processed the WM_DESTROY message from the main
//           client window.
//
//  Returns: None.
//
static void WndDestroy()
  {
  //
  //  Save the current color settings for the next time.
  //
  SaveColors(szAppName);

  WinReleasePS(hpsClient);
  }


//***************************************************************************
//
//  Routine: WndPaint(In):Static
//
//  Remarks: This routine processed the WM_PAINT message from the main client
//           client window.
//
//  Returns: None.
//
static void WndPaint(HWND hWnd)
  {
  HPS   hps;
  RECTL rcl;


  //
  //  Remember to properly repaint hi-lighted square.
  //
  if (FirstSq != -1)
    {
    POINTL ptl;
    RECTL  rcl;

    QuerySqOrigin(FirstSq % 8, FirstSq / 8, &ptl);
    rcl.xLeft   = ptl.x;
    rcl.xRight  = ptl.x + 48;
    rcl.yTop    = ptl.y;
    rcl.yBottom = ptl.y - 48;
    WinInvalidateRect(hWnd, &rcl, FALSE);
    }

  //
  //  Retrieve the presentation space for drawing.
  //
  hps = WinBeginPaint(hWnd, NULL, &rcl);

  //
  //  Clear the background.
  //
  WinFillRect(hps, &rcl, clrBackGround);

  //
  //  Draw the chess board.
  //
  Draw_Board(hps, flag.reverse, clrBlackSquare, clrWhiteSquare);

  //
  //  Draw the coordinates if that option has been selected by the user.
  //
  if (coords)
    DrawCoords(hps, flag.reverse, clrBackGround, clrText);

  //
  //  Draw in the pieces.
  //
  DrawAllPieces(hps, hpsPieces, flag.reverse, boarddraw, colordraw,
                clrBlackPiece, clrWhitePiece);

  //
  //  All done with painting the client area.
  //
  WinEndPaint(hps);

  //
  //  If we have a selected square then hi-lighted it.
  //
  if (FirstSq != -1)
    HiliteSquare(hWnd, FirstSq);
  }


//***************************************************************************
//
//  Routine: WndButton(In):Static
//
//  Remarks: This routine processed the various mouse button message from the
//           main client window.
//
//  Returns: None.
//
static void WndButton(HWND hWnd, USHORT msg, MPARAM mp1)
  {
  POINTL ptl;
  short  Hit;
  short  x, y;


  switch (msg)
    {
    case WM_BUTTON1DOWN:
      /*  If computer is thinking on human's time stop it at the first
          button click.  add test to ensure that "human" can't interupt
          the computer from thinking through its turn. */
      if (User_Move)
        {
        flag.timeout   = true;
        flag.bothsides = false;
        }

      /* Don't continue unless reason to */
      if (!(EditActive || User_Move))
         break;

      ptl.x = SHORT1FROMMP(mp1);
      ptl.y = SHORT2FROMMP(mp1);

      CkdQueryHitCoords(hpsClient, &ptl, &x, &y);

      if (x != -1 && y != -1)
        Hit = y * 8 + x;
      else
        Hit = -1;


         if ( Hit == -1 ){
            if ( FirstSq != -1) {
               UnHiliteSquare ( hWnd, FirstSq);
               GotFirst = FALSE;
               FirstSq = -1;
            }
            break;
         }

         if ( GotFirst ) {
            UnHiliteSquare( hWnd, FirstSq);
            GotFirst = FALSE;

            if ( EditActive == TRUE) {
               WinPostMsg(hWnd, UM_EDITBOARD, MPFROMSHORT((FirstSq<<8)|Hit), NULL);
            } else if (User_Move == TRUE) {
               WinPostMsg(hWnd, UM_USER_ENTERED_MOVE, MPFROMSHORT((FirstSq<<8)|Hit), NULL);
            }
            FirstSq = -1;
         } else {
            GotFirst = TRUE;
            FirstSq = Hit;
            HiliteSquare ( hWnd, Hit);
         }
      break;
    }
  }



MRESULT EXPENTRY AboutProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2)
  {
  switch (msg)
    {
    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1))
        {
        case IDC_OK:
          WinDismissDlg(hDlg, TRUE);
          break;
        }
      return (0);
    }

  return (WinDefDlgProc(hDlg, msg, mp1, mp2));
  }
