//
//  Copyright (C)  Kent D. Cedola  All Rights Reserved.
//
//  Project:    Port Windows GNU Chess to OS/2 PM (PmChess).
//
//  Program:    Convert Windows 3.0 B/W Bitmaps to OS/2 B/W Bitmaps.
//
//   Author:    Kent David Cedola
//
//   System:    OS2 1.2 using Microsoft C 6.0
//
//  Remarks:    This is a quick and dirty tool that I used to convert the B/W
//              bitmaps in the Windows 3.0 version of GNU Chess to something
//              that OS/2 can understand.  After which I will used the OS/2
//              IconEditor to modify the bitmaps (if required).
//
//              Actually I just peeked at the Windows bitmaps and a PM bitmaps
//              and just moved the last 128 bytes from the Windows bitmap to
//              a PM bitmap that I create.  Dumb, but it works...
//
//              Since I plan to use this application only once, it's not fancy
//              and your mileage could vary.
//

#include <stdio.h>
#include <memory.h>


//
//  This is the prefix of a B/W 32x32 PM 1.1 bitmap that I dumped.
//
unsigned char BmpHdr[] =
  {
  0x42, 0x4D, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00,
  0x10, 0x00, 0x20, 0x00, 0x00, 0x00, 0x0C, 0x00,
  0x00, 0x00, 0x20, 0x00, 0x20, 0x00, 0x01, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF
  };


//
//  Define prototypes of routines.
//
void main(short argc, char **argv);


//***************************************************************************
//
//  Routine: main(In, In)
//
//  Remarks: This is where it all begins.
//
//  Returns: None.
//
void main(short argc, char **argv)
  {
  FILE *pFile;
  unsigned char WnBmp[256];
  unsigned char PmBmp[256];
  register i;


  //
  //  Load the header of a PM 32x32 B/W bitmap to our output buffer.
  //
  memcpy(PmBmp, BmpHdr, sizeof(BmpHdr));

  //
  //  Loop through all the icky Windows bitmaps and make neat-o Pm bitmaps.
  //
  for (i = 1; i < argc; i++)
    {
    //
    //  Read in the Windows bitmap into memory so we can play with it.
    //
    pFile = fopen(argv[1], "rb");
    fread(WnBmp, sizeof(WnBmp), 1, pFile);
    fclose(pFile);

    //
    //  Retrieve just the raw bitmap data from the Windows bitmap and merge
    //  with the header of the new PM bitmap.
    //
    memcpy(&PmBmp[sizeof(BmpHdr)], &WnBmp[62], 128);

    //
    //  Write over the Windows bitmap to form a new PM bitmap (not very nice,
    //  but this is only a one time tool...
    //
    pFile = fopen(argv[1], "wb");
    fwrite(PmBmp, sizeof(BmpHdr) + 128, 1, pFile);
    fclose(pFile);
    }
  }
