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

#include <ctype.h>
#include <exec/types.h>

#include "General.h"
#include "Classes.h"
#include "TagInfo.h"

#include "classes/SuperClass.h"
#include "classes/DummyClass.h"
#include "classes/ScriptClass.h"
#include "classes/BlockquoteClass.h"
#include "classes/AClass.h"
#include "classes/AreaClass.h"
#include "classes/BaseClass.h"
#include "classes/BodyClass.h"
#include "classes/DDClass.h"
#include "classes/DLClass.h"
#include "classes/DTClass.h"
#include "classes/LIClass.h"
#include "classes/FontClass.h"
#include "classes/PClass.h"
#include "classes/TableClass.h"
#include "classes/TDClass.h"
#include "classes/THClass.h"
#include "classes/TRClass.h"
#include "classes/TitleClass.h"
#include "classes/OLClass.h"
#include "classes/ULClass.h"
#include "classes/CommentClass.h"
#include "classes/MapClass.h"
#include "classes/MetaClass.h"
#include "classes/BrClass.h"
#include "classes/HRClass.h"
#include "classes/ImgClass.h"
#include "classes/FormClass.h"
#include "classes/InputClass.h"
#include "classes/IsIndexClass.h"
#include "classes/OptionClass.h"
#include "classes/SelectClass.h"
#include "classes/TextAreaClass.h"
#include "classes/FrameClass.h"
#include "classes/FramesetClass.h"
#include "classes/NoFramesClass.h"
#include "classes/FontStyleClass.h"
#include <new>

const char *const AlignKeywords[] = { "LEFT", "CENTER", "RIGHT", NULL };
const char *const VAlignKeywords[] = { "TOP", "MIDDLE", "BOTTOM", NULL };
const char *const ImgAlignKeywords[] =  { "LEFT", "CENTER", "RIGHT", "TOP", "MIDDLE", "BOTTOM", NULL };

class SuperClass *CreateObject (struct TagInfo *tag)
{
  class SuperClass *result = NULL;
  UBYTE textstyles = 0, alignment = Align_None, newline = FALSE;
  BYTE font = Font_None;
  ULONG id = tag->ID;

  switch(id)
  {
    case tag_HEAD:
    case tag_HTML:
    default:
      result = new (std::nothrow) class DummyClass();
    break;

    case tag_SCRIPT:
      result = new (std::nothrow) class ScriptClass();
    break;
/* ----------------------------- */
    case tag_ADDRESS:
//      font = Font_Fixed;
      textstyles = TSF_Italic;
      newline = TRUE;
    break;

    case tag_BIG:
      font = Font_Big;
    break;

    case tag_BLOCKQUOTE:
//      textstyles = TSF_Italic;
//      textstyles = TSF_BlockQuote;
//      newline = TRUE;
      result = new (std::nothrow) class BlockquoteClass();
    break;

    case tag_CENTER:
      alignment = Align_Center;
      newline = TRUE;
    break;

    case tag_CITE:
      textstyles = TSF_Italic;
    break;

    case tag_SAMP:
//      newline = TRUE;
    case tag_CODE:
      font = Font_Fixed;
    break;

    case tag_DFN:
      textstyles = TSF_Bold;
    break;

    case tag_PRE:
      font = Font_Fixed;
      newline = TRUE;
    break;

    case tag_Q:
      textstyles = TSF_Italic;
    break;

    case tag_S:
//      textstyles = TSF_Strike;
    break;

    case tag_SMALL:
      font = Font_Small;
    break;

    case tag_STRIKE:
//      textstyles = TSF_Strike;
    break;

    case tag_TT:
      font = Font_Fixed;
    break;

    case tag_SUB:
//      textstyles = TSF_Sub;
    break;

    case tag_SUP:
//      textstyles = TSF_Super;
    break;

    case tag_B:
    case tag_STRONG:
      textstyles = TSF_Bold;
    break;

    case tag_I:
    case tag_EM:
      textstyles = TSF_Italic;
    break;

    case tag_U:
      textstyles = TSF_Underline;
    break;

    case tag_H1:
      font = Font_H1;
      newline = TRUE;
      alignment = Align_Query;
    break;

    case tag_H2:
      font = Font_H2;
      newline = TRUE;
      alignment = Align_Query;
    break;

    case tag_H3:
      font = Font_H3;
      newline = TRUE;
      alignment = Align_Query;
    break;

    case tag_H4:
      font = Font_H4;
      newline = TRUE;
      alignment = Align_Query;
    break;

    case tag_H5:
      font = Font_H5;
      newline = TRUE;
      alignment = Align_Query;
    break;

    case tag_H6:
      font = Font_H6;
      newline = TRUE;
      alignment = Align_Query;
    break;

/* ----------------------------- */
    case tag_A:
      result = new (std::nothrow) class AClass();
    break;

    case tag_AREA:
      result = new (std::nothrow) class AreaClass();
    break;

    case tag_BASE:
      result = new (std::nothrow) class BaseClass();
    break;

    case tag_BODY:
      result = new (std::nothrow) class BodyClass();
    break;

    case tag_DD:
      result = new (std::nothrow) class DDClass();
    break;

    case tag_DIV:
      alignment = Align_Query;
      newline = TRUE;
    break;

    case tag_DL:
      result = new (std::nothrow) class DLClass();
    break;

    case tag_DT:
      result = new (std::nothrow) class DTClass();
    break;

    case tag_LI:
      result = new (std::nothrow) class LIClass();
    break;

    case tag_FONT:
      result = new (std::nothrow) class FontClass();
    break;

    case tag_P:
      result = new (std::nothrow) class PClass();
    break;

    case tag_TABLE:
      result = new (std::nothrow) class TableClass();
    break;

    case tag_TD:
      result = new (std::nothrow) class TDClass();
    break;

    case tag_TH:
      result = new (std::nothrow) class THClass();
    break;

    case tag_TR:
      result = new (std::nothrow) class TRClass();
    break;

    case tag_TITLE:
      result = new (std::nothrow) class TitleClass();
    break;

    case tag_OL:
      result = new (std::nothrow) class OLClass();
    break;

    case tag_DIR:
    case tag_MENU:
    case tag_UL:
      result = new (std::nothrow) class ULClass();
    break;

    case tag_COMMENT:
      result = new (std::nothrow) class CommentClass();
    break;

    case tag_MAP:
      result = new (std::nothrow) class MapClass();
    break;

    case tag_META:
      result = new (std::nothrow) class MetaClass();
    break;

    case tag_BR:
      result = new (std::nothrow) class BrClass();
    break;

    case tag_HR:
      result = new (std::nothrow) class HRClass();
    break;

    case tag_IMG:
      result = new (std::nothrow) class ImgClass();
    break;

    case tag_FORM:
      result = new (std::nothrow) class FormClass();
    break;

    case tag_INPUT:
      result = new (std::nothrow) class InputClass();
    break;

    case tag_ISINDEX:
      result = new (std::nothrow) class IsIndexClass();
    break;

    case tag_OPTION:
      result = new (std::nothrow) class OptionClass();
    break;

    case tag_SELECT:
      result = new (std::nothrow) class SelectClass();
    break;

    case tag_TEXTAREA:
      result = new (std::nothrow) class TextAreaClass();
    break;


    case tag_FRAME:
      result = new (std::nothrow) class FrameClass();
    break;

    case tag_FRAMESET:
      result = new (std::nothrow) class FramesetClass();
    break;

    case tag_NOFRAMES:
      result = new (std::nothrow) class NoFramesClass();
    break;
  }

  if(!result)
    result = new (std::nothrow) class FontStyleClass(textstyles, alignment, newline, font);

  if(result)
    result->setId(id);

  return(result);
}
