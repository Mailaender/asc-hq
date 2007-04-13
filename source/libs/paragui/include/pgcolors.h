/*
    ParaGUI - crossplatform widgetset
    Copyright (C) 2000,2001,2002,2003,2004  Alexander Pipelka
 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
 
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
 
    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
    Alexander Pipelka
    pipelka@teleweb.at
 
    Last Update:      $Author: mbickel $
    Update Date:      $Date: 2007-04-13 16:15:56 $
    Source File:      $Source: /home/martin/asc/v2/svntest/games/asc/source/libs/paragui/include/pgcolors.h,v $
    CVS/RCS Revision: $Revision: 1.2 $
    Status:           $State: Exp $
 
    AUTOGENERATED PLEASE Do NOT EDIT!
*/

/** @file pgcolors.h
	Header file of the PG_Colors class.
	This header file also creates a bunch of useful color constants. To enable the
	creation of the color constants define "USE_COLOR_CONSTANTS" before including
	this header file.
	There are 891 predefined color constants, though many of them are duplicates
	differing in spelling and capitalization. @ref predefcolorlist "List of all the
	predefined colors."*/

/** \page predefcolorlist A list of all the predefined colors.
@verbatim
snow
ghost_white
GhostWhite
white_smoke
WhiteSmoke
gainsboro
floral_white
FloralWhite
old_lace
OldLace
linen
antique_white
AntiqueWhite
papaya_whip
PapayaWhip
blanched_almond
BlanchedAlmond
bisque
peach_puff
PeachPuff
navajo_white
NavajoWhite
moccasin
cornsilk
ivory
lemon_chiffon
LemonChiffon
seashell
honeydew
mint_cream
MintCream
azure
alice_blue
AliceBlue
lavender
lavender_blush
LavenderBlush
misty_rose
MistyRose
white
dim_gray
DimGray
dim_grey
DimGrey
slate_gray
SlateGray
slate_grey
SlateGrey
light_slate_gray
LightSlateGray
light_slate_grey
LightSlateGrey
gray
grey
light_grey
LightGrey
light_gray
LightGray
cornflower_blue
CornflowerBlue
slate_blue
SlateBlue
medium_slate_blue
MediumSlateBlue
light_slate_blue
LightSlateBlue
sky_blue
SkyBlue
light_sky_blue
LightSkyBlue
light_steel_blue
LightSteelBlue
light_blue
LightBlue
powder_blue
PowderBlue
pale_turquoise
PaleTurquoise
light_cyan
LightCyan
medium_aquamarine
MediumAquamarine
aquamarine
dark_sea_green
DarkSeaGreen
pale_green
PaleGreen
lawn_green
LawnGreen
chartreuse
green_yellow
GreenYellow
yellow_green
YellowGreen
olive_drab
OliveDrab
dark_khaki
DarkKhaki
khaki
pale_goldenrod
PaleGoldenrod
light_goldenrod_yellow
LightGoldenrodYellow
light_yellow
LightYellow
yellow
gold
light_goldenrod
LightGoldenrod
goldenrod
dark_goldenrod
DarkGoldenrod
rosy_brown
RosyBrown
indian_red
IndianRed
saddle_brown
SaddleBrown
sienna
peru
burlywood
beige
wheat
sandy_brown
SandyBrown
tan
chocolate
firebrick
brown
dark_salmon
DarkSalmon
salmon
light_salmon
LightSalmon
orange
dark_orange
DarkOrange
coral
light_coral
LightCoral
tomato
orange_red
OrangeRed
red
hot_pink
HotPink
deep_pink
DeepPink
pink
light_pink
LightPink
pale_violet_red
PaleVioletRed
maroon
medium_violet_red
MediumVioletRed
violet_red
VioletRed
magenta
violet
plum
orchid
medium_orchid
MediumOrchid
dark_orchid
DarkOrchid
dark_violet
DarkViolet
blue_violet
BlueViolet
purple
medium_purple
MediumPurple
thistle
snow1
snow2
snow3
snow4
seashell1
seashell2
seashell3
seashell4
AntiqueWhite1
AntiqueWhite2
AntiqueWhite3
AntiqueWhite4
bisque1
bisque2
bisque3
bisque4
PeachPuff1
PeachPuff2
PeachPuff3
PeachPuff4
NavajoWhite1
NavajoWhite2
NavajoWhite3
NavajoWhite4
LemonChiffon1
LemonChiffon2
LemonChiffon3
LemonChiffon4
cornsilk1
cornsilk2
cornsilk3
cornsilk4
ivory1
ivory2
ivory3
ivory4
honeydew1
honeydew2
honeydew3
honeydew4
LavenderBlush1
LavenderBlush2
LavenderBlush3
LavenderBlush4
MistyRose1
MistyRose2
MistyRose3
MistyRose4
azure1
azure2
azure3
azure4
SlateBlue1
SlateBlue2
SlateBlue3
SkyBlue1
SkyBlue2
SkyBlue3
LightSkyBlue1
LightSkyBlue2
LightSkyBlue3
SlateGray1
SlateGray2
SlateGray3
SlateGray4
LightSteelBlue1
LightSteelBlue2
LightSteelBlue3
LightSteelBlue4
LightBlue1
LightBlue2
LightBlue3
LightBlue4
LightCyan1
LightCyan2
LightCyan3
LightCyan4
PaleTurquoise1
PaleTurquoise2
PaleTurquoise3
PaleTurquoise4
CadetBlue1
CadetBlue2
CadetBlue3
DarkSlateGray1
DarkSlateGray2
DarkSlateGray3
aquamarine1
aquamarine2
aquamarine3
DarkSeaGreen1
DarkSeaGreen2
DarkSeaGreen3
DarkSeaGreen4
PaleGreen1
PaleGreen2
PaleGreen3
chartreuse1
chartreuse2
chartreuse3
OliveDrab1
OliveDrab2
OliveDrab3
OliveDrab4
DarkOliveGreen1
DarkOliveGreen2
DarkOliveGreen3
DarkOliveGreen4
khaki1
khaki2
khaki3
khaki4
LightGoldenrod1
LightGoldenrod2
LightGoldenrod3
LightGoldenrod4
LightYellow1
LightYellow2
LightYellow3
LightYellow4
yellow1
yellow2
yellow3
yellow4
gold1
gold2
gold3
gold4
goldenrod1
goldenrod2
goldenrod3
goldenrod4
DarkGoldenrod1
DarkGoldenrod2
DarkGoldenrod3
DarkGoldenrod4
RosyBrown1
RosyBrown2
RosyBrown3
RosyBrown4
IndianRed1
IndianRed2
IndianRed3
IndianRed4
sienna1
sienna2
sienna3
sienna4
burlywood1
burlywood2
burlywood3
burlywood4
wheat1
wheat2
wheat3
wheat4
tan1
tan2
tan3
tan4
chocolate1
chocolate2
chocolate3
chocolate4
firebrick1
firebrick2
firebrick3
firebrick4
brown1
brown2
brown3
brown4
salmon1
salmon2
salmon3
salmon4
LightSalmon1
LightSalmon2
LightSalmon3
LightSalmon4
orange1
orange2
orange3
orange4
DarkOrange1
DarkOrange2
DarkOrange3
DarkOrange4
coral1
coral2
coral3
coral4
tomato1
tomato2
tomato3
tomato4
OrangeRed1
OrangeRed2
OrangeRed3
OrangeRed4
red1
red2
red3
red4
DeepPink1
DeepPink2
DeepPink3
DeepPink4
HotPink1
HotPink2
HotPink3
HotPink4
pink1
pink2
pink3
pink4
LightPink1
LightPink2
LightPink3
LightPink4
PaleVioletRed1
PaleVioletRed2
PaleVioletRed3
PaleVioletRed4
maroon1
maroon2
maroon3
maroon4
VioletRed1
VioletRed2
VioletRed3
VioletRed4
magenta1
magenta2
magenta3
magenta4
orchid1
orchid2
orchid3
orchid4
plum1
plum2
plum3
plum4
MediumOrchid1
MediumOrchid2
MediumOrchid3
MediumOrchid4
DarkOrchid1
DarkOrchid2
DarkOrchid3
DarkOrchid4
purple1
purple2
purple3
MediumPurple1
MediumPurple2
MediumPurple3
thistle1
thistle2
thistle3
thistle4
gray40
grey40
gray41
grey41
gray42
grey42
gray43
grey43
gray44
grey44
gray45
grey45
gray46
grey46
gray47
grey47
gray48
grey48
gray49
grey49
gray50
grey50
gray51
grey51
gray52
grey52
gray53
grey53
gray54
grey54
gray55
grey55
gray56
grey56
gray57
grey57
gray58
grey58
gray59
grey59
gray60
grey60
gray61
grey61
gray62
grey62
gray63
grey63
gray64
grey64
gray65
grey65
gray66
grey66
gray67
grey67
gray68
grey68
gray69
grey69
gray70
grey70
gray71
grey71
gray72
grey72
gray73
grey73
gray74
grey74
gray75
grey75
gray76
grey76
gray77
grey77
gray78
grey78
gray79
grey79
gray80
grey80
gray81
grey81
gray82
grey82
gray83
grey83
gray84
grey84
gray85
grey85
gray86
grey86
gray87
grey87
gray88
grey88
gray89
grey89
gray90
grey90
gray91
grey91
gray92
grey92
gray93
grey93
gray94
grey94
gray95
grey95
gray96
grey96
gray97
grey97
gray98
grey98
gray99
grey99
gray100
grey100
dark_grey
DarkGrey
dark_gray
DarkGray
dark_blue
DarkBlue
dark_cyan
DarkCyan
dark_magenta
DarkMagenta
dark_red
DarkRed
light_green
LightGreen
@endverbatim
*/

#ifndef PG_COLORS_H
#define PG_COLORS_H

#include "paragui.h"
#include "pgcolor.h"
#include MAP_INC

#ifdef USE_COLOR_CONSTANTS

namespace PG_Colormap {
const PG_Color snow = 0xfffafa;
const PG_Color ghost_white = 0xf8f8ff;
const PG_Color GhostWhite = 0xf8f8ff;
const PG_Color white_smoke = 0xf5f5f5;
const PG_Color WhiteSmoke = 0xf5f5f5;
const PG_Color gainsboro = 0xdcdcdc;
const PG_Color floral_white = 0xfffaf0;
const PG_Color FloralWhite = 0xfffaf0;
const PG_Color old_lace = 0xfdf5e6;
const PG_Color OldLace = 0xfdf5e6;
const PG_Color linen = 0xfaf0e6;
const PG_Color antique_white = 0xfaebd7;
const PG_Color AntiqueWhite = 0xfaebd7;
const PG_Color papaya_whip = 0xffefd5;
const PG_Color PapayaWhip = 0xffefd5;
const PG_Color blanched_almond = 0xffebcd;
const PG_Color BlanchedAlmond = 0xffebcd;
const PG_Color bisque = 0xffe4c4;
const PG_Color peach_puff = 0xffdab9;
const PG_Color PeachPuff = 0xffdab9;
const PG_Color navajo_white = 0xffdead;
const PG_Color NavajoWhite = 0xffdead;
const PG_Color moccasin = 0xffe4b5;
const PG_Color cornsilk = 0xfff8dc;
const PG_Color ivory = 0xfffff0;
const PG_Color lemon_chiffon = 0xfffacd;
const PG_Color LemonChiffon = 0xfffacd;
const PG_Color seashell = 0xfff5ee;
const PG_Color honeydew = 0xf0fff0;
const PG_Color mint_cream = 0xf5fffa;
const PG_Color MintCream = 0xf5fffa;
const PG_Color azure = 0xf0ffff;
const PG_Color alice_blue = 0xf0f8ff;
const PG_Color AliceBlue = 0xf0f8ff;
const PG_Color lavender = 0xe6e6fa;
const PG_Color lavender_blush = 0xfff0f5;
const PG_Color LavenderBlush = 0xfff0f5;
const PG_Color misty_rose = 0xffe4e1;
const PG_Color MistyRose = 0xffe4e1;
const PG_Color white = 0xffffff;
const PG_Color dim_gray = 0x696969;
const PG_Color DimGray = 0x696969;
const PG_Color dim_grey = 0x696969;
const PG_Color DimGrey = 0x696969;
const PG_Color slate_gray = 0x708090;
const PG_Color SlateGray = 0x708090;
const PG_Color slate_grey = 0x708090;
const PG_Color SlateGrey = 0x708090;
const PG_Color light_slate_gray = 0x778899;
const PG_Color LightSlateGray = 0x778899;
const PG_Color light_slate_grey = 0x778899;
const PG_Color LightSlateGrey = 0x778899;
const PG_Color gray = 0xbebebe;
const PG_Color grey = 0xbebebe;
const PG_Color light_grey = 0xd3d3d3;
const PG_Color LightGrey = 0xd3d3d3;
const PG_Color light_gray = 0xd3d3d3;
const PG_Color LightGray = 0xd3d3d3;
const PG_Color cornflower_blue = 0x6495ed;
const PG_Color CornflowerBlue = 0x6495ed;
const PG_Color slate_blue = 0x6a5acd;
const PG_Color SlateBlue = 0x6a5acd;
const PG_Color medium_slate_blue = 0x7b68ee;
const PG_Color MediumSlateBlue = 0x7b68ee;
const PG_Color light_slate_blue = 0x8470ff;
const PG_Color LightSlateBlue = 0x8470ff;
const PG_Color sky_blue = 0x87ceeb;
const PG_Color SkyBlue = 0x87ceeb;
const PG_Color light_sky_blue = 0x87cefa;
const PG_Color LightSkyBlue = 0x87cefa;
const PG_Color light_steel_blue = 0xb0c4de;
const PG_Color LightSteelBlue = 0xb0c4de;
const PG_Color light_blue = 0xadd8e6;
const PG_Color LightBlue = 0xadd8e6;
const PG_Color powder_blue = 0xb0e0e6;
const PG_Color PowderBlue = 0xb0e0e6;
const PG_Color pale_turquoise = 0xafeeee;
const PG_Color PaleTurquoise = 0xafeeee;
const PG_Color light_cyan = 0xe0ffff;
const PG_Color LightCyan = 0xe0ffff;
const PG_Color medium_aquamarine = 0x66cdaa;
const PG_Color MediumAquamarine = 0x66cdaa;
const PG_Color aquamarine = 0x7fffd4;
const PG_Color dark_sea_green = 0x8fbc8f;
const PG_Color DarkSeaGreen = 0x8fbc8f;
const PG_Color pale_green = 0x98fb98;
const PG_Color PaleGreen = 0x98fb98;
const PG_Color lawn_green = 0x7cfc00;
const PG_Color LawnGreen = 0x7cfc00;
const PG_Color chartreuse = 0x7fff00;
const PG_Color green_yellow = 0xadff2f;
const PG_Color GreenYellow = 0xadff2f;
const PG_Color yellow_green = 0x9acd32;
const PG_Color YellowGreen = 0x9acd32;
const PG_Color olive_drab = 0x6b8e23;
const PG_Color OliveDrab = 0x6b8e23;
const PG_Color dark_khaki = 0xbdb76b;
const PG_Color DarkKhaki = 0xbdb76b;
const PG_Color khaki = 0xf0e68c;
const PG_Color pale_goldenrod = 0xeee8aa;
const PG_Color PaleGoldenrod = 0xeee8aa;
const PG_Color light_goldenrod_yellow = 0xfafad2;
const PG_Color LightGoldenrodYellow = 0xfafad2;
const PG_Color light_yellow = 0xffffe0;
const PG_Color LightYellow = 0xffffe0;
const PG_Color yellow = 0xffff00;
const PG_Color gold = 0xffd700;
const PG_Color light_goldenrod = 0xeedd82;
const PG_Color LightGoldenrod = 0xeedd82;
const PG_Color goldenrod = 0xdaa520;
const PG_Color dark_goldenrod = 0xb8860b;
const PG_Color DarkGoldenrod = 0xb8860b;
const PG_Color rosy_brown = 0xbc8f8f;
const PG_Color RosyBrown = 0xbc8f8f;
const PG_Color indian_red = 0xcd5c5c;
const PG_Color IndianRed = 0xcd5c5c;
const PG_Color saddle_brown = 0x8b4513;
const PG_Color SaddleBrown = 0x8b4513;
const PG_Color sienna = 0xa0522d;
const PG_Color peru = 0xcd853f;
const PG_Color burlywood = 0xdeb887;
const PG_Color beige = 0xf5f5dc;
const PG_Color wheat = 0xf5deb3;
const PG_Color sandy_brown = 0xf4a460;
const PG_Color SandyBrown = 0xf4a460;
const PG_Color tan = 0xd2b48c;
const PG_Color chocolate = 0xd2691e;
const PG_Color firebrick = 0xb22222;
const PG_Color brown = 0xa52a2a;
const PG_Color dark_salmon = 0xe9967a;
const PG_Color DarkSalmon = 0xe9967a;
const PG_Color salmon = 0xfa8072;
const PG_Color light_salmon = 0xffa07a;
const PG_Color LightSalmon = 0xffa07a;
const PG_Color orange = 0xffa500;
const PG_Color dark_orange = 0xff8c00;
const PG_Color DarkOrange = 0xff8c00;
const PG_Color coral = 0xff7f50;
const PG_Color light_coral = 0xf08080;
const PG_Color LightCoral = 0xf08080;
const PG_Color tomato = 0xff6347;
const PG_Color orange_red = 0xff4500;
const PG_Color OrangeRed = 0xff4500;
const PG_Color red = 0xff0000;
const PG_Color hot_pink = 0xff69b4;
const PG_Color HotPink = 0xff69b4;
const PG_Color deep_pink = 0xff1493;
const PG_Color DeepPink = 0xff1493;
const PG_Color pink = 0xffc0cb;
const PG_Color light_pink = 0xffb6c1;
const PG_Color LightPink = 0xffb6c1;
const PG_Color pale_violet_red = 0xdb7093;
const PG_Color PaleVioletRed = 0xdb7093;
const PG_Color maroon = 0xb03060;
const PG_Color medium_violet_red = 0xc71585;
const PG_Color MediumVioletRed = 0xc71585;
const PG_Color violet_red = 0xd02090;
const PG_Color VioletRed = 0xd02090;
const PG_Color magenta = 0xff00ff;
const PG_Color violet = 0xee82ee;
const PG_Color plum = 0xdda0dd;
const PG_Color orchid = 0xda70d6;
const PG_Color medium_orchid = 0xba55d3;
const PG_Color MediumOrchid = 0xba55d3;
const PG_Color dark_orchid = 0x9932cc;
const PG_Color DarkOrchid = 0x9932cc;
const PG_Color dark_violet = 0x9400d3;
const PG_Color DarkViolet = 0x9400d3;
const PG_Color blue_violet = 0x8a2be2;
const PG_Color BlueViolet = 0x8a2be2;
const PG_Color purple = 0xa020f0;
const PG_Color medium_purple = 0x9370db;
const PG_Color MediumPurple = 0x9370db;
const PG_Color thistle = 0xd8bfd8;
const PG_Color snow1 = 0xfffafa;
const PG_Color snow2 = 0xeee9e9;
const PG_Color snow3 = 0xcdc9c9;
const PG_Color snow4 = 0x8b8989;
const PG_Color seashell1 = 0xfff5ee;
const PG_Color seashell2 = 0xeee5de;
const PG_Color seashell3 = 0xcdc5bf;
const PG_Color seashell4 = 0x8b8682;
const PG_Color AntiqueWhite1 = 0xffefdb;
const PG_Color AntiqueWhite2 = 0xeedfcc;
const PG_Color AntiqueWhite3 = 0xcdc0b0;
const PG_Color AntiqueWhite4 = 0x8b8378;
const PG_Color bisque1 = 0xffe4c4;
const PG_Color bisque2 = 0xeed5b7;
const PG_Color bisque3 = 0xcdb79e;
const PG_Color bisque4 = 0x8b7d6b;
const PG_Color PeachPuff1 = 0xffdab9;
const PG_Color PeachPuff2 = 0xeecbad;
const PG_Color PeachPuff3 = 0xcdaf95;
const PG_Color PeachPuff4 = 0x8b7765;
const PG_Color NavajoWhite1 = 0xffdead;
const PG_Color NavajoWhite2 = 0xeecfa1;
const PG_Color NavajoWhite3 = 0xcdb38b;
const PG_Color NavajoWhite4 = 0x8b795e;
const PG_Color LemonChiffon1 = 0xfffacd;
const PG_Color LemonChiffon2 = 0xeee9bf;
const PG_Color LemonChiffon3 = 0xcdc9a5;
const PG_Color LemonChiffon4 = 0x8b8970;
const PG_Color cornsilk1 = 0xfff8dc;
const PG_Color cornsilk2 = 0xeee8cd;
const PG_Color cornsilk3 = 0xcdc8b1;
const PG_Color cornsilk4 = 0x8b8878;
const PG_Color ivory1 = 0xfffff0;
const PG_Color ivory2 = 0xeeeee0;
const PG_Color ivory3 = 0xcdcdc1;
const PG_Color ivory4 = 0x8b8b83;
const PG_Color honeydew1 = 0xf0fff0;
const PG_Color honeydew2 = 0xe0eee0;
const PG_Color honeydew3 = 0xc1cdc1;
const PG_Color honeydew4 = 0x838b83;
const PG_Color LavenderBlush1 = 0xfff0f5;
const PG_Color LavenderBlush2 = 0xeee0e5;
const PG_Color LavenderBlush3 = 0xcdc1c5;
const PG_Color LavenderBlush4 = 0x8b8386;
const PG_Color MistyRose1 = 0xffe4e1;
const PG_Color MistyRose2 = 0xeed5d2;
const PG_Color MistyRose3 = 0xcdb7b5;
const PG_Color MistyRose4 = 0x8b7d7b;
const PG_Color azure1 = 0xf0ffff;
const PG_Color azure2 = 0xe0eeee;
const PG_Color azure3 = 0xc1cdcd;
const PG_Color azure4 = 0x838b8b;
const PG_Color SlateBlue1 = 0x836fff;
const PG_Color SlateBlue2 = 0x7a67ee;
const PG_Color SlateBlue3 = 0x6959cd;
const PG_Color SkyBlue1 = 0x87ceff;
const PG_Color SkyBlue2 = 0x7ec0ee;
const PG_Color SkyBlue3 = 0x6ca6cd;
const PG_Color LightSkyBlue1 = 0xb0e2ff;
const PG_Color LightSkyBlue2 = 0xa4d3ee;
const PG_Color LightSkyBlue3 = 0x8db6cd;
const PG_Color SlateGray1 = 0xc6e2ff;
const PG_Color SlateGray2 = 0xb9d3ee;
const PG_Color SlateGray3 = 0x9fb6cd;
const PG_Color SlateGray4 = 0x6c7b8b;
const PG_Color LightSteelBlue1 = 0xcae1ff;
const PG_Color LightSteelBlue2 = 0xbcd2ee;
const PG_Color LightSteelBlue3 = 0xa2b5cd;
const PG_Color LightSteelBlue4 = 0x6e7b8b;
const PG_Color LightBlue1 = 0xbfefff;
const PG_Color LightBlue2 = 0xb2dfee;
const PG_Color LightBlue3 = 0x9ac0cd;
const PG_Color LightBlue4 = 0x68838b;
const PG_Color LightCyan1 = 0xe0ffff;
const PG_Color LightCyan2 = 0xd1eeee;
const PG_Color LightCyan3 = 0xb4cdcd;
const PG_Color LightCyan4 = 0x7a8b8b;
const PG_Color PaleTurquoise1 = 0xbbffff;
const PG_Color PaleTurquoise2 = 0xaeeeee;
const PG_Color PaleTurquoise3 = 0x96cdcd;
const PG_Color PaleTurquoise4 = 0x668b8b;
const PG_Color CadetBlue1 = 0x98f5ff;
const PG_Color CadetBlue2 = 0x8ee5ee;
const PG_Color CadetBlue3 = 0x7ac5cd;
const PG_Color DarkSlateGray1 = 0x97ffff;
const PG_Color DarkSlateGray2 = 0x8deeee;
const PG_Color DarkSlateGray3 = 0x79cdcd;
const PG_Color aquamarine1 = 0x7fffd4;
const PG_Color aquamarine2 = 0x76eec6;
const PG_Color aquamarine3 = 0x66cdaa;
const PG_Color DarkSeaGreen1 = 0xc1ffc1;
const PG_Color DarkSeaGreen2 = 0xb4eeb4;
const PG_Color DarkSeaGreen3 = 0x9bcd9b;
const PG_Color DarkSeaGreen4 = 0x698b69;
const PG_Color PaleGreen1 = 0x9aff9a;
const PG_Color PaleGreen2 = 0x90ee90;
const PG_Color PaleGreen3 = 0x7ccd7c;
const PG_Color chartreuse1 = 0x7fff00;
const PG_Color chartreuse2 = 0x76ee00;
const PG_Color chartreuse3 = 0x66cd00;
const PG_Color OliveDrab1 = 0xc0ff3e;
const PG_Color OliveDrab2 = 0xb3ee3a;
const PG_Color OliveDrab3 = 0x9acd32;
const PG_Color OliveDrab4 = 0x698b22;
const PG_Color DarkOliveGreen1 = 0xcaff70;
const PG_Color DarkOliveGreen2 = 0xbcee68;
const PG_Color DarkOliveGreen3 = 0xa2cd5a;
const PG_Color DarkOliveGreen4 = 0x6e8b3d;
const PG_Color khaki1 = 0xfff68f;
const PG_Color khaki2 = 0xeee685;
const PG_Color khaki3 = 0xcdc673;
const PG_Color khaki4 = 0x8b864e;
const PG_Color LightGoldenrod1 = 0xffec8b;
const PG_Color LightGoldenrod2 = 0xeedc82;
const PG_Color LightGoldenrod3 = 0xcdbe70;
const PG_Color LightGoldenrod4 = 0x8b814c;
const PG_Color LightYellow1 = 0xffffe0;
const PG_Color LightYellow2 = 0xeeeed1;
const PG_Color LightYellow3 = 0xcdcdb4;
const PG_Color LightYellow4 = 0x8b8b7a;
const PG_Color yellow1 = 0xffff00;
const PG_Color yellow2 = 0xeeee00;
const PG_Color yellow3 = 0xcdcd00;
const PG_Color yellow4 = 0x8b8b00;
const PG_Color gold1 = 0xffd700;
const PG_Color gold2 = 0xeec900;
const PG_Color gold3 = 0xcdad00;
const PG_Color gold4 = 0x8b7500;
const PG_Color goldenrod1 = 0xffc125;
const PG_Color goldenrod2 = 0xeeb422;
const PG_Color goldenrod3 = 0xcd9b1d;
const PG_Color goldenrod4 = 0x8b6914;
const PG_Color DarkGoldenrod1 = 0xffb90f;
const PG_Color DarkGoldenrod2 = 0xeead0e;
const PG_Color DarkGoldenrod3 = 0xcd950c;
const PG_Color DarkGoldenrod4 = 0x8b6508;
const PG_Color RosyBrown1 = 0xffc1c1;
const PG_Color RosyBrown2 = 0xeeb4b4;
const PG_Color RosyBrown3 = 0xcd9b9b;
const PG_Color RosyBrown4 = 0x8b6969;
const PG_Color IndianRed1 = 0xff6a6a;
const PG_Color IndianRed2 = 0xee6363;
const PG_Color IndianRed3 = 0xcd5555;
const PG_Color IndianRed4 = 0x8b3a3a;
const PG_Color sienna1 = 0xff8247;
const PG_Color sienna2 = 0xee7942;
const PG_Color sienna3 = 0xcd6839;
const PG_Color sienna4 = 0x8b4726;
const PG_Color burlywood1 = 0xffd39b;
const PG_Color burlywood2 = 0xeec591;
const PG_Color burlywood3 = 0xcdaa7d;
const PG_Color burlywood4 = 0x8b7355;
const PG_Color wheat1 = 0xffe7ba;
const PG_Color wheat2 = 0xeed8ae;
const PG_Color wheat3 = 0xcdba96;
const PG_Color wheat4 = 0x8b7e66;
const PG_Color tan1 = 0xffa54f;
const PG_Color tan2 = 0xee9a49;
const PG_Color tan3 = 0xcd853f;
const PG_Color tan4 = 0x8b5a2b;
const PG_Color chocolate1 = 0xff7f24;
const PG_Color chocolate2 = 0xee7621;
const PG_Color chocolate3 = 0xcd661d;
const PG_Color chocolate4 = 0x8b4513;
const PG_Color firebrick1 = 0xff3030;
const PG_Color firebrick2 = 0xee2c2c;
const PG_Color firebrick3 = 0xcd2626;
const PG_Color firebrick4 = 0x8b1a1a;
const PG_Color brown1 = 0xff4040;
const PG_Color brown2 = 0xee3b3b;
const PG_Color brown3 = 0xcd3333;
const PG_Color brown4 = 0x8b2323;
const PG_Color salmon1 = 0xff8c69;
const PG_Color salmon2 = 0xee8262;
const PG_Color salmon3 = 0xcd7054;
const PG_Color salmon4 = 0x8b4c39;
const PG_Color LightSalmon1 = 0xffa07a;
const PG_Color LightSalmon2 = 0xee9572;
const PG_Color LightSalmon3 = 0xcd8162;
const PG_Color LightSalmon4 = 0x8b5742;
const PG_Color orange1 = 0xffa500;
const PG_Color orange2 = 0xee9a00;
const PG_Color orange3 = 0xcd8500;
const PG_Color orange4 = 0x8b5a00;
const PG_Color DarkOrange1 = 0xff7f00;
const PG_Color DarkOrange2 = 0xee7600;
const PG_Color DarkOrange3 = 0xcd6600;
const PG_Color DarkOrange4 = 0x8b4500;
const PG_Color coral1 = 0xff7256;
const PG_Color coral2 = 0xee6a50;
const PG_Color coral3 = 0xcd5b45;
const PG_Color coral4 = 0x8b3e2f;
const PG_Color tomato1 = 0xff6347;
const PG_Color tomato2 = 0xee5c42;
const PG_Color tomato3 = 0xcd4f39;
const PG_Color tomato4 = 0x8b3626;
const PG_Color OrangeRed1 = 0xff4500;
const PG_Color OrangeRed2 = 0xee4000;
const PG_Color OrangeRed3 = 0xcd3700;
const PG_Color OrangeRed4 = 0x8b2500;
const PG_Color red1 = 0xff0000;
const PG_Color red2 = 0xee0000;
const PG_Color red3 = 0xcd0000;
const PG_Color red4 = 0x8b0000;
const PG_Color DeepPink1 = 0xff1493;
const PG_Color DeepPink2 = 0xee1289;
const PG_Color DeepPink3 = 0xcd1076;
const PG_Color DeepPink4 = 0x8b0a50;
const PG_Color HotPink1 = 0xff6eb4;
const PG_Color HotPink2 = 0xee6aa7;
const PG_Color HotPink3 = 0xcd6090;
const PG_Color HotPink4 = 0x8b3a62;
const PG_Color pink1 = 0xffb5c5;
const PG_Color pink2 = 0xeea9b8;
const PG_Color pink3 = 0xcd919e;
const PG_Color pink4 = 0x8b636c;
const PG_Color LightPink1 = 0xffaeb9;
const PG_Color LightPink2 = 0xeea2ad;
const PG_Color LightPink3 = 0xcd8c95;
const PG_Color LightPink4 = 0x8b5f65;
const PG_Color PaleVioletRed1 = 0xff82ab;
const PG_Color PaleVioletRed2 = 0xee799f;
const PG_Color PaleVioletRed3 = 0xcd6889;
const PG_Color PaleVioletRed4 = 0x8b475d;
const PG_Color maroon1 = 0xff34b3;
const PG_Color maroon2 = 0xee30a7;
const PG_Color maroon3 = 0xcd2990;
const PG_Color maroon4 = 0x8b1c62;
const PG_Color VioletRed1 = 0xff3e96;
const PG_Color VioletRed2 = 0xee3a8c;
const PG_Color VioletRed3 = 0xcd3278;
const PG_Color VioletRed4 = 0x8b2252;
const PG_Color magenta1 = 0xff00ff;
const PG_Color magenta2 = 0xee00ee;
const PG_Color magenta3 = 0xcd00cd;
const PG_Color magenta4 = 0x8b008b;
const PG_Color orchid1 = 0xff83fa;
const PG_Color orchid2 = 0xee7ae9;
const PG_Color orchid3 = 0xcd69c9;
const PG_Color orchid4 = 0x8b4789;
const PG_Color plum1 = 0xffbbff;
const PG_Color plum2 = 0xeeaeee;
const PG_Color plum3 = 0xcd96cd;
const PG_Color plum4 = 0x8b668b;
const PG_Color MediumOrchid1 = 0xe066ff;
const PG_Color MediumOrchid2 = 0xd15fee;
const PG_Color MediumOrchid3 = 0xb452cd;
const PG_Color MediumOrchid4 = 0x7a378b;
const PG_Color DarkOrchid1 = 0xbf3eff;
const PG_Color DarkOrchid2 = 0xb23aee;
const PG_Color DarkOrchid3 = 0x9a32cd;
const PG_Color DarkOrchid4 = 0x68228b;
const PG_Color purple1 = 0x9b30ff;
const PG_Color purple2 = 0x912cee;
const PG_Color purple3 = 0x7d26cd;
const PG_Color MediumPurple1 = 0xab82ff;
const PG_Color MediumPurple2 = 0x9f79ee;
const PG_Color MediumPurple3 = 0x8968cd;
const PG_Color thistle1 = 0xffe1ff;
const PG_Color thistle2 = 0xeed2ee;
const PG_Color thistle3 = 0xcdb5cd;
const PG_Color thistle4 = 0x8b7b8b;
const PG_Color gray40 = 0x666666;
const PG_Color grey40 = 0x666666;
const PG_Color gray41 = 0x696969;
const PG_Color grey41 = 0x696969;
const PG_Color gray42 = 0x6b6b6b;
const PG_Color grey42 = 0x6b6b6b;
const PG_Color gray43 = 0x6e6e6e;
const PG_Color grey43 = 0x6e6e6e;
const PG_Color gray44 = 0x707070;
const PG_Color grey44 = 0x707070;
const PG_Color gray45 = 0x737373;
const PG_Color grey45 = 0x737373;
const PG_Color gray46 = 0x757575;
const PG_Color grey46 = 0x757575;
const PG_Color gray47 = 0x787878;
const PG_Color grey47 = 0x787878;
const PG_Color gray48 = 0x7a7a7a;
const PG_Color grey48 = 0x7a7a7a;
const PG_Color gray49 = 0x7d7d7d;
const PG_Color grey49 = 0x7d7d7d;
const PG_Color gray50 = 0x7f7f7f;
const PG_Color grey50 = 0x7f7f7f;
const PG_Color gray51 = 0x828282;
const PG_Color grey51 = 0x828282;
const PG_Color gray52 = 0x858585;
const PG_Color grey52 = 0x858585;
const PG_Color gray53 = 0x878787;
const PG_Color grey53 = 0x878787;
const PG_Color gray54 = 0x8a8a8a;
const PG_Color grey54 = 0x8a8a8a;
const PG_Color gray55 = 0x8c8c8c;
const PG_Color grey55 = 0x8c8c8c;
const PG_Color gray56 = 0x8f8f8f;
const PG_Color grey56 = 0x8f8f8f;
const PG_Color gray57 = 0x919191;
const PG_Color grey57 = 0x919191;
const PG_Color gray58 = 0x949494;
const PG_Color grey58 = 0x949494;
const PG_Color gray59 = 0x969696;
const PG_Color grey59 = 0x969696;
const PG_Color gray60 = 0x999999;
const PG_Color grey60 = 0x999999;
const PG_Color gray61 = 0x9c9c9c;
const PG_Color grey61 = 0x9c9c9c;
const PG_Color gray62 = 0x9e9e9e;
const PG_Color grey62 = 0x9e9e9e;
const PG_Color gray63 = 0xa1a1a1;
const PG_Color grey63 = 0xa1a1a1;
const PG_Color gray64 = 0xa3a3a3;
const PG_Color grey64 = 0xa3a3a3;
const PG_Color gray65 = 0xa6a6a6;
const PG_Color grey65 = 0xa6a6a6;
const PG_Color gray66 = 0xa8a8a8;
const PG_Color grey66 = 0xa8a8a8;
const PG_Color gray67 = 0xababab;
const PG_Color grey67 = 0xababab;
const PG_Color gray68 = 0xadadad;
const PG_Color grey68 = 0xadadad;
const PG_Color gray69 = 0xb0b0b0;
const PG_Color grey69 = 0xb0b0b0;
const PG_Color gray70 = 0xb3b3b3;
const PG_Color grey70 = 0xb3b3b3;
const PG_Color gray71 = 0xb5b5b5;
const PG_Color grey71 = 0xb5b5b5;
const PG_Color gray72 = 0xb8b8b8;
const PG_Color grey72 = 0xb8b8b8;
const PG_Color gray73 = 0xbababa;
const PG_Color grey73 = 0xbababa;
const PG_Color gray74 = 0xbdbdbd;
const PG_Color grey74 = 0xbdbdbd;
const PG_Color gray75 = 0xbfbfbf;
const PG_Color grey75 = 0xbfbfbf;
const PG_Color gray76 = 0xc2c2c2;
const PG_Color grey76 = 0xc2c2c2;
const PG_Color gray77 = 0xc4c4c4;
const PG_Color grey77 = 0xc4c4c4;
const PG_Color gray78 = 0xc7c7c7;
const PG_Color grey78 = 0xc7c7c7;
const PG_Color gray79 = 0xc9c9c9;
const PG_Color grey79 = 0xc9c9c9;
const PG_Color gray80 = 0xcccccc;
const PG_Color grey80 = 0xcccccc;
const PG_Color gray81 = 0xcfcfcf;
const PG_Color grey81 = 0xcfcfcf;
const PG_Color gray82 = 0xd1d1d1;
const PG_Color grey82 = 0xd1d1d1;
const PG_Color gray83 = 0xd4d4d4;
const PG_Color grey83 = 0xd4d4d4;
const PG_Color gray84 = 0xd6d6d6;
const PG_Color grey84 = 0xd6d6d6;
const PG_Color gray85 = 0xd9d9d9;
const PG_Color grey85 = 0xd9d9d9;
const PG_Color gray86 = 0xdbdbdb;
const PG_Color grey86 = 0xdbdbdb;
const PG_Color gray87 = 0xdedede;
const PG_Color grey87 = 0xdedede;
const PG_Color gray88 = 0xe0e0e0;
const PG_Color grey88 = 0xe0e0e0;
const PG_Color gray89 = 0xe3e3e3;
const PG_Color grey89 = 0xe3e3e3;
const PG_Color gray90 = 0xe5e5e5;
const PG_Color grey90 = 0xe5e5e5;
const PG_Color gray91 = 0xe8e8e8;
const PG_Color grey91 = 0xe8e8e8;
const PG_Color gray92 = 0xebebeb;
const PG_Color grey92 = 0xebebeb;
const PG_Color gray93 = 0xededed;
const PG_Color grey93 = 0xededed;
const PG_Color gray94 = 0xf0f0f0;
const PG_Color grey94 = 0xf0f0f0;
const PG_Color gray95 = 0xf2f2f2;
const PG_Color grey95 = 0xf2f2f2;
const PG_Color gray96 = 0xf5f5f5;
const PG_Color grey96 = 0xf5f5f5;
const PG_Color gray97 = 0xf7f7f7;
const PG_Color grey97 = 0xf7f7f7;
const PG_Color gray98 = 0xfafafa;
const PG_Color grey98 = 0xfafafa;
const PG_Color gray99 = 0xfcfcfc;
const PG_Color grey99 = 0xfcfcfc;
const PG_Color gray100 = 0xffffff;
const PG_Color grey100 = 0xffffff;
const PG_Color dark_grey = 0xa9a9a9;
const PG_Color DarkGrey = 0xa9a9a9;
const PG_Color dark_gray = 0xa9a9a9;
const PG_Color DarkGray = 0xa9a9a9;
const PG_Color dark_blue = 0x00008b;
const PG_Color DarkBlue = 0x00008b;
const PG_Color dark_cyan = 0x008b8b;
const PG_Color DarkCyan = 0x008b8b;
const PG_Color dark_magenta = 0x8b008b;
const PG_Color DarkMagenta = 0x8b008b;
const PG_Color dark_red = 0x8b0000;
const PG_Color DarkRed = 0x8b0000;
const PG_Color light_green = 0x90ee90;
const PG_Color LightGreen = 0x90ee90;
} // namespace PG_Colormap
#endif // !USE_COLOR_CONSTANTS

/**
	@author Marek Habersack
	@short tool-class for descriptive colorvalues
*/

class PG_Colors {
	typedef STL_MAP<const char*, PG_Color> colormap;
	typedef STL_MAP<const char*, PG_Color>::iterator cit;

public:
	PG_Colors() {
		if (!PG_Colors::initialized) {
			PG_Colors::InitColors();
			PG_Colors::initialized = true;
		}
	}
	static bool FindColorByName(const char *name, PG_Color &c) {
		cit col = PG_Colors::colors.find(name);
		if (col != PG_Colors::colors.end()) {
			c = colors[name];
			return true;
		}
		return false;
	}

	static const PG_Color FindColorByName(const char *name) {
		PG_Color c;
		if(FindColorByName(name, c)) {
			return c;
		}
		return colors["black"];
	}

	static void InitColors();

	const PG_Color operator[](const char *name) {
		return FindColorByName(name);
	}
protected:
	static colormap colors;
	static bool     initialized;
};
#endif // !PG_COLORS_H
