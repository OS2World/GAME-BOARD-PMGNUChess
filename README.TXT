
  Version 1.01 of OS/2 PM port of GNUCHESS 3.1.
  Modified by Kent Cedola for use under the OS/2 PM environment.

  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
  Copyright (c) 1988, 1989, 1990  John Stanback

  This file is part of CHESS.

  CHESS is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY.  No author or distributor accepts responsibility to anyone for
  the consequences of using it or for whether it serves any particular
  purpose or works at all, unless he says so in writing.  Refer to the CHESS
  General Public License for full details.

  Everyone is granted permission to copy, modify and redistribute CHESS, but
  only under the conditions described in the CHESS General Public License.
  A copy of this license is supposed to have been given to you along with
  CHESS so you can know your rights and responsibilities.  It should be in a
  file named COPYING.  Among other things, the copyright notice and this
  notice must be preserved on all copies.


  >>> The PM version of GNUCHESS is a hard port of the Windows port done by
      Daryl Baker.  My goal was to do the initial port of the code to PM and
      then hope that another programmer (someone that enjoys chess abit more
      than I do) will continue with future enhancements.  I myself prefer
      games with lots of hexes.

      While I did clean up some of the code when I did the translation.  The
      overall structure of this application needs some work.  The board
      should be moved to it's own window for example.

      I would also like to thank Daryl Baker for his much harder task in
      converting GNU Chess from a character mode to Windows in the first
      place.  Without his effort I would of never attempted the PM port.



***************************************************************
<<<< The below is from the Windows version of GNUCHESS 3.1 >>>>
***************************************************************

  Version 1.01 of MicroSoft Windows port of GNUCHESS 3.1.
  Modified by Daryl Baker for use in MS WINDOWS environment

  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
  Copyright (c) 1988, 1989, 1990  John Stanback

  This file is part of CHESS.

  CHESS is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY.  No author or distributor accepts responsibility to anyone for
  the consequences of using it or for whether it serves any particular
  purpose or works at all, unless he says so in writing.  Refer to the CHESS
  General Public License for full details.

  Everyone is granted permission to copy, modify and redistribute CHESS, but
  only under the conditions described in the CHESS General Public License.
  A copy of this license is supposed to have been given to you along with
  CHESS so you can know your rights and responsibilities.  It should be in a
  file named COPYING.  Among other things, the copyright notice and this
  notice must be preserved on all copies.


Fixes/changes since 1.0
        1) Fixed bug where "computer is black" never changed when switched
           sides
        2) Fixed problem with promoting pawn.
        3) Changed File Get ... to File Open ...
        4) Made fancier Open dialog box, (includes scroll bars amoung other)
        5) Properly frees memory when program ends.
        6) Made text color selectable
        7) Added GNU copyleft to source files.

ToDos
        1) Code needs to be looked over and cleaned up, routines
           made "static near", and such.  Maybe use -GW switch for
           several modules.
        2) Scalable/scrollable graphics (Probably won't get done)
        3) Once pawn is promoted UNDO does not restore to pawn.  This also
           appers in the dos and unix versions of gnuchess.  Not sure if
           I'll fix it.  I have tried not to change (this is debatable) the 
           orignal source except to "windowize" it.

release notes:
        1) I have only tested this under windows 3.0 386 enhanced mode.
           Seems to work ok in real mode though slower.
        2) It requires at least 282k of memory.
        3) Fits on a EGA screen, no scrolling implemented.
        4) Most of the GNUCHESS commands are implemented.
        5) When computer is playing itself abort by clicking on any square.
           The last move made will most likely show "draw" or "mate", ignore
           this message.  You may have to remove the last move.
        6) To have the computer think while it is your turn, select "easy"
           from the menu.  Clicking on square to take your turn will abort
           the look ahead.
        7) There is no help file.
        8) The file gnuchess.boo must be in the same directory as 
           the executable.
        9) The program create a file "chess.ini" in your windows directory to
           store various settings.  Currently only the screen colors.

Enjoy.

Daryl Baker
dkb@mitre.org

