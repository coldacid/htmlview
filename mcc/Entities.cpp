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

#include <string.h>
#include <exec/types.h>

#include "Entities.h"
#include "TernaryTrees.h"
#include "private.h"

struct EntityInfo EntityTable[] =
{
  { "Aacute", 193 },
  { "Acirc",  194 },
  { "AElig",  198 },
  { "Agrave", 192 },
  { "Aring",  197 },
  { "Atilde", 195 },
  { "Auml",   196 },
  { "Eacute", 201 },
  { "Ecirc",  202 },
  { "Egrave", 200 },
  { "ETH",    208 },
  { "Euml",   203 },
  { "Iacute", 205 },
  { "Icirc",  206 },
  { "Igrave", 204 },
  { "Iuml",   207 },
  { "Ntilde", 209 },
  { "Oacute", 211 },
  { "Ocirc",  212 },
  { "Ograve", 210 },
  { "Oslash", 216 },
  { "Otilde", 213 },
  { "Ouml",   214 },
  { "THORN",  222 },
  { "Uacute", 218 },
  { "Ucirc",  219 },
  { "Ugrave", 217 },
  { "Uuml",   220 },
  { "Yacute", 221 },
  { "aacute", 225 },
  { "acirc",  226 },
  { "acute",  180 },
  { "aelig",  230 },
  { "agrave", 224 },
  { "amp",     38 },
  { "aring",  229 },
  { "atilde", 227 },
  { "auml",   228 },
  { "brvbar", 166 },
  { "bull",   183 },
  { "Ccedil", 199 },
  { "ccedil", 231 },
  { "cedil",  184 },
  { "cent",   162 },
  { "copy",   169 },
  { "curren", 164 },
  { "deg",    176 },
  { "divide", 247 },
  { "eacute", 233 },
  { "ecirc",  234 },
  { "egrave", 232 },
  { "eth",    240 },
  { "euml",   235 },
  { "frac12", 189 },
  { "frac14", 188 },
  { "frac34", 190 },
  { "gt",      62 },
  { "iacute", 237 },
  { "icirc",  238 },
  { "iexcl",  161 },
  { "igrave", 236 },
  { "iquest", 191 },
  { "iuml",   239 },
  { "laquo",  171 },
  { "lt",      60 },
  { "macr",   175 },
  { "micro",  181 },
  { "middot", 183 },
  { "nbsp",   160 },
  { "not",    172 },
  { "ntilde", 241 },
  { "oacute", 243 },
  { "ocirc",  244 },
  { "ograve", 242 },
  { "ordf",   170 },
  { "ordm",   186 },
  { "oslash", 248 },
  { "otilde", 245 },
  { "ouml",   246 },
  { "para",   182 },
  { "plusmn", 177 },
  { "pound",  163 },
  { "quot",    34 },
  { "raquo",  187 },
  { "reg",    174 },
  { "sect",   167 },
  { "shy",    173 },
  { "sup1",   185 },
  { "sup2",   178 },
  { "sup3",   179 },
  { "szlig",  223 },
  { "thorn",  254 },
  { "times",  215 },
  { "uacute", 250 },
  { "ucirc",  251 },
  { "ugrave", 249 },
  { "uml",    168 },
  { "uuml",   252 },
  { "yacute", 253 },
  { "yen",    165 },
  { "yuml",   255 },
  { NULL,       0 }
};

static struct EntityInfo *TFind (struct TNode *node, CONST_STRPTR str)
{
  UBYTE chr, src = *str++;

  while(node)
  {
    if((chr = node->SplitChar) == '\0')
    {
      /* This allow entities to end with a white space */
/*      if(IsWhitespace(src))
      {
        node = node->Middle;
        break;
      }
*/    }

    if(src < chr)
      node = node->Left;
    else if(src > chr)
      node = node->Right;
    else if((node = node->Middle), src)
      src = (src = *str++) == ';' ? 0 : src;
    else break;
  }

  return (struct EntityInfo *)node;
}

struct TNode *EntityTree = NULL;

CONSTRUCTOR(BuildEntityTree, 5)
{
  /*return*/ BinaryInsert(EntityTree, EntityTable, (ULONG)0, (ULONG)sizeof(EntityTable) / sizeof(EntityInfo) - 2);
}

DESTRUCTOR(DisposeEntityTree, 5)
{
  if (EntityTree) delete EntityTree;
}

struct EntityInfo *GetEntityInfo (CONST_STRPTR str)
{
  return (struct EntityInfo *)TFind(EntityTree, str);
}
