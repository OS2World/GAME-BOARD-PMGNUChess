#
#  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
#  Copyright (c) 1988, 1989, 1990  John Stanback
#
#  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
#
#  Version:    1990-11-17
#
#     File:    Make File (PmChess.mak)
#
#   Porter:    Ported to Windows 3.0 by Darly Baker
#
#   Porter:    Ported to OS/2 1.2 by Kent Cedola
#
#   System:    OS2 1.2 using Microsoft C 6.0
#
#  License:
#
#    CHESS is distributed in the hope that it will be useful, but WITHOUT ANY
#    WARRANTY.  No author or distributor accepts responsibility to anyone for
#    the consequences of using it or for whether it serves any particular
#    purpose or works at all, unless he says so in writing.  Refer to the
#    CHESS General Public License for full details.
#
#    Everyone is granted permission to copy, modify and redistribute CHESS,
#    but only under the conditions described in the CHESS General Public
#    License.  A copy of this license is supposed to have been given to you
#    along with CHESS so you can know your rights and responsibilities.  It
#    should be in a file named COPYING.  Among other things, the copyright
#    notice and this notice must be preserved on all copies.
#


#===================================================================
#
#   Default inference rules
#
#===================================================================
.c.obj:
    cl -c -AM -G2cs -Ox -W3 -Zi -FPa -DLINT_ARGS $*.c

#.c.obj:
#    cl386 -c -Gs -Od -W3 -Zi -B1 c1l_386 -DLINT_ARGS $*.c

.rc.res:
    rc -r $*.rc

#===================================================================
#
#   A list of all of the object files
#
#===================================================================
ALL_OBJ1 = PmChess.obj Piece.obj Stats.obj TimeCnt.obj
ALL_OBJ2 = Eval.obj Globals.obj Search.obj Dsp.obj Book.obj Init.obj
ALL_OBJ3 = Board.obj MswDsp.obj Color.obj Create.obj
ALL_OBJ4 = Promote.obj Test.obj InitMenu.obj NumDlg.obj


#===================================================================
#
#   Dependencies
#
#===================================================================

all: PmChess.exe

PmChess.lnk: PmChess.mak
    echo $(ALL_OBJ1) +              > PmChess.lnk
    echo $(ALL_OBJ2) +              >> PmChess.lnk
    echo $(ALL_OBJ3) +              >> PmChess.lnk
    echo $(ALL_OBJ4)                >> PmChess.lnk
    echo PmChess.exe                >> PmChess.lnk
    echo PmChess.map /MAP/CO/NOD    >> PmChess.lnk
    echo mlibca os2                 >> PmChess.lnk
    echo PmChess.def                >> PmChess.lnk

PmChess.res : $*.rc Resource.h

PmChess.obj : $*.c $*.h

Eval.obj    : $*.c GnuChess.h Defs.h

Globals.obj : $*.c GnuChess.h

Search.obj  : $*.c PmChess.h GnuChess.h Defs.h

Book.obj    : $*.c PmChess.h GnuChess.h Defs.h Resource.h

Init.obj    : $*.c PmChess.h GnuChess.h Defs.h Resource.h

Dsp.obj     : $*.c PmChess.h GnuChess.h Defs.h Resource.h

Board.obj   : $*.c PmChess.h Defs.h

MswDsp.obj  : $*.c PmChess.h GnuChess.h Defs.h Resource.h

Color.obj   : $*.c PmChess.h Resource.h

Create.obj  : $*.c PmChess.h Resource.h

Piece.obj   : $*.c PmChess.h GnuChess.h Defs.h Resource.h

Promote.obj : $*.c PmChess.h Resource.h

Stats.obj    : $*.c PmChess.h Resource.h

Test.obj     : $*.c PmChess.h Resource.h

TimeCnt.obj  : $*.c PmChess.h Resource.h

InitMenu.obj : $*.c PmChess.h GnuChess.h Resource.h

NumDlg.obj   : $*.c PmChess.h Resource.h



PmChess.exe: $(ALL_OBJ1) $(ALL_OBJ2) $(ALL_OBJ3) $(ALL_OBJ4) PmChess.def PmChess.lnk PmChess.res
    link @PmChess.lnk
    rc PmChess.res PmChess.exe
