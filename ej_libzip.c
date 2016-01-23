/* -*- c -*- */

/* Copyright (C) 2016 Alexander Chernov <cher@ejudge.ru> */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "ejudge/config.h"
#include "ejudge/ej_limits.h"
#include "ejudge/version.h"
#include "ejudge/ej_libzip.h"

#if defined CONF_HAS_LIBZIP
#include <zip.h>
#endif

#if defined CONF_HAS_LIBZIP
#else

struct ZipData *
ej_libzip_open(FILE *log_f, const unsigned char *path, int flags)
{
    if (log_f) {
        fprintf(log_f, "libzip library is not supported");
    }
    return NULL;
}

#endif

/*
 * Local variables:
 *  c-basic-offset: 4
 * End:
 */
