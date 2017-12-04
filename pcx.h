/*
 * pcx.h - Read PCX image from f_pcx and save it into p_img
 *
 * Copyright (C) 2017 Jan Havran
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef PCX_H
#define PCX_H

#include "pcx2gif.h"

extern size_t pcx_load(image_t *p_img, FILE *f_pcx);

#endif // PCX_H

