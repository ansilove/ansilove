#ifndef COMPAT_H
#define COMPAT_H

#ifndef HAVE_PLEDGE
#include "pledge.h"
#endif

#ifndef HAVE_STRTONUM
#include "strtonum.h"
#endif

#endif /* COMPAT_H */
