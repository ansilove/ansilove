/*
 * strtolower.c
 * Ansilove 4.2.1
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2025 Stefan Vogt, Brian Cassidy, and Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause license.
 * See LICENSE file for details.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <ctype.h>
#include "strtolower.h"

char *
strtolower(char *str)
{
	char *p = str;

	while (*p) {
		*p = tolower((unsigned char)*p);
		p++;
	}

	return str;
}
