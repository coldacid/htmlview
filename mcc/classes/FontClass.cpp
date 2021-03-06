/***************************************************************************

 HTMLview.mcc - HTMLview MUI Custom Class
 Copyright (C) 1997-2000 Allan Odgaard
 Copyright (C) 2005-2007 by HTMLview.mcc Open Source Team

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 HTMLview class Support Site:  http://www.sf.net/projects/htmlview-mcc/

 $Id$

***************************************************************************/

#include "FontClass.h"

#include "Layout.h"
#include "MinMax.h"
#include "ParseMessage.h"
#include "ScanArgs.h"
#include "SharedData.h"
#include <stdio.h>

VOID FontClass::AllocateColours (struct ColorMap *cmap)
{
  FontCol = AllocPen(cmap, FontRGB);
  Flags |= FLG_AllocatedColours;
  TreeClass::AllocateColours(cmap);
}

VOID FontClass::FreeColours (struct ColorMap *cmap)
{
  if(Flags & FLG_AllocatedColours)
  {
    FreePen(cmap, FontCol);
    Flags &= ~FLG_AllocatedColours;
  }
  TreeClass::FreeColours(cmap);
}

BOOL FontClass::Layout (struct LayoutMessage &lmsg)
{
  if(!(Flags & FLG_AllocatedColours))
    AllocateColours(lmsg.Share->Scr->ViewPort.ColorMap);

  struct TextFont *oldfont = lmsg.Font;
  if(Font != Font_None)
    lmsg.Font = lmsg.Share->Fonts[Font];

  TreeClass::Layout(lmsg);

  lmsg.Font = oldfont;

  return TRUE;
}

VOID FontClass::MinMax (struct MinMaxMessage &mmsg)
{
  struct TextFont *oldfont = mmsg.Font;
  if(Font != Font_None)
    mmsg.Font = mmsg.Fonts[Font];

  TreeClass::MinMax(mmsg);

  mmsg.Font = oldfont;
}

VOID FontClass::Parse(struct ParseMessage &pmsg)
{
  pmsg.SetLock();
  pmsg.NextEndBracket();
#ifdef OUTPUT
  PrintTag(pmsg.Locked);
#endif

  STRPTR font = NULL;
  struct ArgList args[] =
  {
    { "COLOR",  &FontRGB, ARG_COLOUR, NULL },
    { "SIZE",   &font,    ARG_STRING, NULL },
    { NULL,     NULL,     0,          NULL }
  };

  ScanArgs(pmsg.Locked, args);

  LONG size = Font_None;
  if(font && sscanf(font, "%*[+-]%ld", &size) == 1)
  {
    switch(*font)
    {
      case '+':
        size = Font_H4 - ((size > 3) ? 3 : size);
      break;

      case '-':
        size = Font_H4 + ((size > 2) ? 2 : size);
      break;

      default:
        size = Font_Fixed - ((size > 6) ? 6 : size);
      break;
    }
  }
//  if(font) printf("Converted: %d (%s)\n", size, font);
  delete font;
  Font = size;

  TreeClass::Parse(pmsg);
}

VOID FontClass::Render (struct RenderMessage &rmsg)
{
  LONG oldcol = rmsg.Colours[Col_Text];
  SetCol(rmsg.Colours[Col_Text], FontCol);
  TreeClass::Render(rmsg);
  rmsg.Colours[Col_Text] = oldcol;
}

