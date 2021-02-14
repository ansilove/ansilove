/*
 * fonts.h
 * Ansilove 4.1.5
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2021 Stefan Vogt, Brian Cassidy, and Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause License.
 * See LICENSE file for details.
 */

#ifndef FONTS_H
#define FONTS_H

char *fonts[] = {
	"cp737",				/* Greek */
	"cp775",				/* Baltic */
	"cp850",				/* Latin 1 */
	"cp852",				/* Latin 2 */
	"cp855",				/* Cyrillic */
	"cp857",				/* Turkish */
	"cp860",				/* Portuguese */
	"cp861",				/* Icelandic */
	"cp862",				/* Hebrew */
	"cp863",				/* French-canadian */
	"cp865",				/* Nordic */
	"cp866",				/* Russian */
	"cp869",				/* Greek */
	"80x25",
	"80x50",
	"greek",
	"baltic",
	"latin1",
	"latin2",
	"cyrillic",
	"turkish",
	"portuguese",
	"icelandic",
	"hebrew",
	"french-canadian",
	"nordic",
	"russian",
	"greek-869",
	"terminus",
	"amiga",
	"microknight",
	"microknight+",
	"mosoul",
	"pot-noodle",
	"topaz",
	"topaz+",
	"topaz500",
	"topaz500+"
};

int fontsId[] = {
	ANSILOVE_FONT_CP737,			/* Greek */
	ANSILOVE_FONT_CP775,			/* Baltic */
	ANSILOVE_FONT_CP850,			/* Latin 1 */
	ANSILOVE_FONT_CP852,			/* Latin 2 */
	ANSILOVE_FONT_CP855,			/* Cyrillic */
	ANSILOVE_FONT_CP857,			/* Turkish */
	ANSILOVE_FONT_CP860,			/* Portuguese */
	ANSILOVE_FONT_CP861,			/* Icelandic */
	ANSILOVE_FONT_CP862,			/* Hebrew */
	ANSILOVE_FONT_CP863,			/* French-canadian */
	ANSILOVE_FONT_CP865,			/* Nordic */
	ANSILOVE_FONT_CP866,			/* Russian */
	ANSILOVE_FONT_CP869,			/* Greek */
	ANSILOVE_FONT_CP437,			/* IBM PC 80x25 */
	ANSILOVE_FONT_CP437_80x50,		/* IBM PC 80x50 */
	ANSILOVE_FONT_CP737,			/* Greek */
	ANSILOVE_FONT_CP775,			/* Baltic */
	ANSILOVE_FONT_CP850,			/* Latin 1 */
	ANSILOVE_FONT_CP852,			/* Latin 2 */
	ANSILOVE_FONT_CP855,			/* Cyrillic */
	ANSILOVE_FONT_CP857,			/* Turkish */
	ANSILOVE_FONT_CP860,			/* Portuguese */
	ANSILOVE_FONT_CP861,			/* Icelandic */
	ANSILOVE_FONT_CP862,			/* Hebrew */
	ANSILOVE_FONT_CP863,			/* French-canadian */
	ANSILOVE_FONT_CP865,			/* Nordic */
	ANSILOVE_FONT_CP866,			/* Russian */
	ANSILOVE_FONT_CP869,			/* Greek */
	ANSILOVE_FONT_TERMINUS,
	ANSILOVE_FONT_TOPAZ,			/* Alias: amiga */
	ANSILOVE_FONT_MICROKNIGHT,
	ANSILOVE_FONT_MICROKNIGHT_PLUS,
	ANSILOVE_FONT_MOSOUL,
	ANSILOVE_FONT_POT_NOODLE,
	ANSILOVE_FONT_TOPAZ,
	ANSILOVE_FONT_TOPAZ_PLUS,
	ANSILOVE_FONT_TOPAZ500,
	ANSILOVE_FONT_TOPAZ500_PLUS
};

#endif /* FONTS_H */
