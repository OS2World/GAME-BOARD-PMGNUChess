//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//  Copyright (c) 1988, 1989, 1990  John Stanback
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//   Module:    Init/Update Menu Logic (MenuInit.c)
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

#define INCL_DOS
#define INCL_PM
#include <os2.h>
#include "PmChess.h"
#include "GnuChess.h"
#include "Resource.h"


extern int coords;

void EnableMenuItem(HWND hwndMenu, USHORT idItem, BOOL bEnable)
  {
  if (bEnable)
    WinSendMsg(hwndMenu, MM_SETITEMATTR, MPFROM2SHORT(idItem, TRUE),
               MPFROM2SHORT(MIA_DISABLED, 0));
  else
    WinSendMsg(hwndMenu, MM_SETITEMATTR, MPFROM2SHORT(idItem, TRUE),
               MPFROM2SHORT(MIA_DISABLED, MIA_DISABLED));
  }


void CheckMenuItem(HWND hwndMenu, USHORT idItem, BOOL bCheck)
  {
  if (bCheck)
    WinSendMsg(hwndMenu, MM_SETITEMATTR, MPFROM2SHORT(idItem, TRUE),
               MPFROM2SHORT(MIA_CHECKED, MIA_CHECKED));
  else
    WinSendMsg(hwndMenu, MM_SETITEMATTR, MPFROM2SHORT(idItem, TRUE),
               MPFROM2SHORT(MIA_CHECKED, 0));
  }


void Init_Menus(HWND hWnd, MPARAM mp1, MPARAM mp2)
  {
  HWND   hwndMenu;
  USHORT Status;


  hwndMenu = HWNDFROMMP(mp2);

  switch (SHORT1FROMMP(mp1))
    {
    case IDM_EDIT:
      EnableMenuItem(hwndMenu, IDM_EDIT_GAME,
                             (GameCnt>0 ? TRUE : FALSE) );
      EnableMenuItem(hwndMenu, IDM_EDIT_UNDO,
                             (GameCnt>0 ? TRUE : FALSE) );
      EnableMenuItem(hwndMenu, IDM_EDIT_REMOVE,
                             (GameCnt>1 ? TRUE : FALSE) );
      break;

    case IDM_OPTIONS:
      if ( flag.hash == false)  Status = FALSE; else Status = TRUE;
      CheckMenuItem ( hwndMenu, IDM_OPTIONS_HASH, Status);

      if ( coords == false)  Status = FALSE; else Status = TRUE;
      CheckMenuItem ( hwndMenu, IDM_OPTIONS_COOR, Status);

      if ( flag.beep == false)  Status = FALSE; else Status = TRUE;
      CheckMenuItem ( hwndMenu, IDM_OPTIONS_TONE, Status);

      if ( flag.bothsides == false)  Status = FALSE; else Status = TRUE;
      CheckMenuItem ( hwndMenu, IDM_OPTIONS_BOTH, Status);

      if ( Book == NULL)  Status = FALSE; else Status = TRUE;
      CheckMenuItem ( hwndMenu, IDM_OPTIONS_BOOK, Status);

      if ( flag.post == false)  Status = FALSE; else Status = TRUE;
      CheckMenuItem ( hwndMenu, IDM_OPTIONS_STATS, Status);
      break;

    case IDM_SKILL:
      if ( dither == 0)
        Status = FALSE; else Status = TRUE;
      CheckMenuItem ( hwndMenu, IDM_SKILL_RANDOM, Status);
  
      if ( flag.easy == false)
        Status = TRUE; else Status = FALSE;
      CheckMenuItem ( hwndMenu, IDM_SKILL_EASY, Status);
      break;

    case IDM_SIDE:
      if ( flag.reverse == false)
        Status = FALSE; else Status = TRUE;
       CheckMenuItem ( hwndMenu, IDM_SIDE_REVERSE, Status);

      if (computer == black)
        {
        CheckMenuItem(hwndMenu, IDM_SIDE_BLACK, TRUE);
        CheckMenuItem(hwndMenu, IDM_SIDE_WHITE, FALSE);
        }
      else
        {
        CheckMenuItem(hwndMenu, IDM_SIDE_WHITE, TRUE);
        CheckMenuItem(hwndMenu, IDM_SIDE_BLACK, FALSE);
        }
      break;
    }
  }
