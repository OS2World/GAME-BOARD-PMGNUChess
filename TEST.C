//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//  Copyright (c) 1988, 1989, 1990  John Stanback
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//   Module:    Promote User Query Dialog (Promote.c)
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
#include <time.h>
#include "PmChess.h"
#include "GnuChess.h"
#include "Defs.h"
#include "Resource.h"


//
//  Define dialog procedure's prototypes.
//
MRESULT EXPENTRY TestProc(HWND hWnd, USHORT msg, MPARAM mp1, MPARAM mp2);


//***************************************************************************
//
//  Routine: TestDialog(In)
//
//  Remarks: This routine displays a dialog that test the speed of the GNU
//           logic.
//
//  Returns: None.
//
void TestDialog(HWND hWnd)
  {
  WinDlgBox(HWND_DESKTOP, hWnd, TestProc, 0, IDD_TEST, NULL);
  }


void
TestSpeed(HWND hWnd, int cnt, void (*f) (short int side, short int ply))
{
  register short i;
  long t1, t2, evrate;
  char tmp[40];


  t1 = time (0);
  for (i = 0; i < 10000; i++)
    {
      f (opponent, 2);
    }
  t2 = time (0);
  NodeCnt = 10000L * (TrPnt[3] - TrPnt[2]);
  evrate = NodeCnt / (t2 - t1);

  sprintf ( tmp, "Nodes= %8ld, Nodes/Sec= %5ld", NodeCnt, evrate);
  WinSetDlgItemText (hWnd, cnt, tmp);
}


//***************************************************************************
//
//  Routine: TestProc(In, In, In, In)
//
//  Remarks: This routine displays a dialog that queries the user of which
//           type of piece to promote a pawn.
//
//  Returns: The piece selected.
//
MRESULT EXPENTRY TestProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2)
  {
  HPOINTER hCurrent, hWait;


  switch (msg)
    {
    case WM_INITDLG:
      WinPostMsg(hDlg, WM_USER+1, NULL, NULL);
      return (FALSE);

    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1))
        {
        case IDC_OK:
          WinDismissDlg(hDlg, TRUE);
          break;
        }
      return (0);

    case WM_USER+1:
      hCurrent = WinQueryPointer(HWND_DESKTOP);
      hWait    = WinQuerySysPointer(HWND_DESKTOP, SPTR_WAIT, FALSE);
      WinSetPointer(HWND_DESKTOP, hWait);

      TestSpeed(hDlg, IDC_TEST_MOVELIST,    MoveList);
      TestSpeed(hDlg, IDC_TEST_CAPTURELIST, CaptureList);

      WinSetPointer(HWND_DESKTOP, hCurrent);
      break;
    }

  return (WinDefDlgProc(hDlg, msg, mp1, mp2));
  }
