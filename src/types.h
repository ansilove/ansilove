/*
 * types.h
 * Ansilove 4.0.7
 * https://www.ansilove.org
 *
 * Copyright (c) 2011-2020 Stefan Vogt, Brian Cassidy, and Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause License.
 * See LICENSE file for details.
 */

#ifndef TYPES_H
#define TYPES_H

extern char *types[];
extern int (*loaders[])(struct ansilove_ctx *, struct ansilove_options *);

#endif /* TYPES_H */
