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

#ifndef RENDER_H
#define RENDER_H

enum
{
  Col_Background,
  Col_Text,
  Col_Shine,
  Col_Shadow,
  Col_Halfshine,
  Col_Halfshadow,
  Col_Link,
  Col_VLink,
  Col_ALink,

  Col_NumberOf
};

struct RenderMessage
{
  VOID Reset (ULONG minx, ULONG miny, ULONG maxx, ULONG maxy, LONG offsetx, LONG offsety, LONG left, LONG top, LONG *pens);

  struct RastPort *ObtainDoubleBuffer (ULONG width, ULONG height);
  VOID FlushDoubleBuffer ();

  /* Doublebuffer info */
  ULONG BufferWidth, BufferHeight;
  struct RastPort *BufferRP;

  Object *HTMLview;
  struct SharedData *Share;

  struct RastPort *RPort;
  LONG MinX, MaxX, MinY, MaxY;
  LONG OffsetX, OffsetY;
  LONG Left, Top;

  class SuperClass *TargetObj;
  class BackFillClass *BackgroundObj;

  ULONG UL_Nesting;

  LONG Colours[Col_NumberOf];

  BOOL RedrawGadgets;
  UBYTE Textstyles, Align;

  LONG CellBackgroundCol;
  struct PictureFrame *CellPicture;
  BOOL TableBorder;
  UWORD OL_Type;

  BOOL RedrawLink;
};

#endif
