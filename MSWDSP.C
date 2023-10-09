//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//  Copyright (c) 1988, 1989, 1990  John Stanback
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//   Module:    Window Display Logic (MswDsp.c)
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
#include <os2.h>
#include <stdio.h>
#include <string.h>
#include "PmChess.h"
#include "GnuChess.h"
#include "Defs.h"
#include "Resource.h"


extern short boarddraw[64];
extern short colordraw[64];

extern char mvstr[4][6];
extern long evrate;
static char* ColorStr[2] = {"White", "Black"};

void
ShowPlayers (void)
{
  /* display in the status line what color the computer is playing */
  WinSetWindowText ( hComputerColor, (computer == black) ? "Computer is black" :
                                                        "Computer is white" );
}

void
ShowDepth (char ch)
{
   char tmp[30];
   if ( hStats ) {
      sprintf ( tmp, "%d%c", Sdepth, ch);
      WinSetDlgItemText ( hStats, IDC_STATS_DEPTH, tmp);
   }
}

void
ShowScore (short score)
{
   char tmp[30];
   if ( hStats) {
      sprintf ( tmp, "%d",score);
      WinSetDlgItemText ( hStats, IDC_STATS_SCORE, tmp);
   }
}


//***************************************************************************
//
//  Routine: ShowMessage(In, In)
//
//  Remarks: This subroutine is called to display the specified text to the
//           user in a message box.
//
//  Returns: None.
//
void ShowMessage(HWND hWnd, PSZ pszText)
  {
  WinMessageBox(HWND_DESKTOP, hWnd, pszText, szAppName, 0,
                MB_OK | MB_ICONEXCLAMATION);
  }


//***************************************************************************
//
//  Routine: SMessageBox(In, In, In)
//
//  Remarks: This subroutine is called to display a the specified string
//           resource text to the user.
//
//  Returns: None.
//
void SMessageBox(HWND hWnd, SHORT str_num, SHORT str1_num)
  {
  char str[100], str1[100];


  WinLoadString(hab, 0, str_num,  sizeof(str),  str);
  WinLoadString(hab, 0, str1_num, sizeof(str1), str1);

  WinMessageBox(HWND_DESKTOP, hWnd, str, str1, 0, MB_OK | MB_ICONEXCLAMATION);
  }


void
ClearMessage (void)
{
}

void
ShowCurrentMove (short int pnt, short int f, short int t)
{
   char tmp[30];

   if ( hStats) {
      algbr (f, t, false);
      sprintf ( tmp, "(%2d) %4s",pnt, (char *)mvstr[0]);
      WinSetDlgItemText ( hStats, IDC_STATS_POSITION, tmp);
   }
}

void
ShowSidetoMove (void)
{
   char tmp[30];
   sprintf ( tmp, "It is %s's turn",(char *)ColorStr[player]);
   WinSetWindowText ( hWhosTurn, tmp);

}

void
ShowPrompt (void)
{
}

void
ShowNodeCnt (long int NodeCnt, long int evrate)
{
   char tmp[40];

   if ( hStats ) {
      sprintf ( tmp,"%-8ld", NodeCnt);
      WinSetDlgItemText ( hStats, IDC_STATS_NODES, tmp);
      sprintf ( tmp,"%-5ld", evrate);
      WinSetDlgItemText ( hStats, IDC_STATS_RATE, tmp);
   }
}  

void
ShowResults (short int score, short unsigned int *bstline, char ch)
{
  unsigned char d, ply;
  char str[300];
  int s;

  if (flag.post)
    {
      ShowDepth (ch);
      ShowScore (score);
      d = 7; s = 0;
      for (ply = 1; bstline[ply] > 0; ply++)
        {
         algbr ((short) bstline[ply] >> 8, (short) bstline[ply] & 0xFF, false);
         if ( ply==5 || ply==9 || ply==13 || ply==17)
            s += sprintf ( str+s,"\n");
         s += sprintf ( str+s,"%-5s ", (char *) mvstr[0]);
        }
      WinSetDlgItemText ( hStats, IDC_STATS_BEST, str);
    }
}

void
SearchStartStuff (short int side)
{
}

void
OutputMove (HWND hWnd)
{
  char tmp[30];

  UpdateDisplay (hWnd, root->f, root->t, 0, (short) root->flags);
  sprintf ( tmp, "My move is %s",(char *) mvstr[0]);
  WinSetWindowText ( hComputerMove, tmp);

  if (root->flags & draw)
    SMessageBox ( hWnd, IDS_DRAWGAME,IDS_CHESS);
  else if (root->score == -9999)
    SMessageBox ( hWnd, IDS_YOUWIN, IDS_CHESS);
  else if (root->score == 9998)
    SMessageBox ( hWnd, IDS_COMPUTERWIN,IDS_CHESS);
  else if (root->score < -9000)
    SMessageBox ( hWnd, IDS_MATESOON,IDS_CHESS);
  else if (root->score > 9000)
    SMessageBox ( hWnd, IDS_COMPMATE,IDS_CHESS);
  if (flag.post)
    {
      ShowNodeCnt (NodeCnt, evrate);
/*
      for (i = 1999; i >= 0 && Tree[i].f == 0 && Tree[i].t == 0; i--);
      printz ("Max Tree= %5d", i);
*/
    }
}

void
UpdateClocks (void)
{
  short m, s;
  char tmp[20];

  m = (short) (et / 60);
  s = (short) (et - 60 * (long) m);
  if (TCflag)
    {
      m = (short) ((TimeControl.clock[player] - et) / 60);
      s = (short) (TimeControl.clock[player] - et - 60 * (long) m);
    }
  if (m < 0) m = 0;
  if (s < 0) s = 0;

  sprintf ( tmp, "%0d:%02d",m,s);
  if ( player == computer ) {
      WinSetWindowText (hClockComputer, tmp);
  } else {
      WinSetWindowText (hClockHuman, tmp);
  }

  if (flag.post)
    ShowNodeCnt (NodeCnt, evrate);
}

void
ShowPostnValue (short int sq)
{
}

void
ShowPostnValues (void)
{
}

//***************************************************************************
//
//  Routine: DrawPiece(In, In)
//
//  Remarks: This subroutine is called to display a piece by invalidating
//           it's region and letting the paint logic draw it in.
//
//  Returns: None.
//
void DrawPiece(HWND hWnd, short f)
  {
  POINTL aptl[4];
  RECTL  rcl;
  short  x,y;


  //
  //  Compute the (x,y) coordinate of the piece to draw.
  //
  if (flag.reverse)
    {
    x = 7 - (f % 8);
    y = 7 - (f / 8);
    }
   else
    {
    x = f % 8;
    y = f / 8;
    }

  //
  //  Retrieve the corners of the piece to redraw.
  //
  QuerySqCoords(x, y, aptl);

  //
  //  Invalidate the area around the piece to redraw.
  //
  rcl.xLeft   = aptl[0].x - 1;
  rcl.yBottom = aptl[0].y;
  rcl.xRight  = aptl[2].x + 1;
  rcl.yTop    = aptl[2].y;
  WinInvalidateRect(hWnd, &rcl, FALSE);
  }


void
UpdateDisplay (HWND hWnd, short int f, short int t, short int redraw, short int isspec)
{
  short sq;
  
  for (sq=0; sq<64; sq++) {
         boarddraw[sq] = board[sq];
         colordraw[sq] = color[sq];
  }

  if (redraw){
      WinInvalidateRect ( hWnd, NULL, TRUE);
      ShowPlayers ();
      WinUpdateWindow ( hWnd );
  } else {
      DrawPiece (hWnd, f);
      DrawPiece (hWnd, t);
      if (isspec & cstlmask)
        if (t > f)
          {
            DrawPiece (hWnd, f + 3);
            DrawPiece (hWnd, t - 1);
          }
        else
          {
            DrawPiece (hWnd, f - 4);
            DrawPiece (hWnd, t + 1);
          }
      else if (isspec & epmask)
        {
          DrawPiece (hWnd, t - 8);
          DrawPiece (hWnd, t + 8);
        }
      WinUpdateWindow (hWnd);
    }
}

void
GiveHint (HWND hWnd)
{
  char s[40];
  algbr ((short) (hint >> 8), (short) (hint & 0xFF), false);
  strcpy (s, "try ");
  strcat (s, mvstr[0]);
  ShowMessage (hWnd, s);
}
