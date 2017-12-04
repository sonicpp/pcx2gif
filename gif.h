/*
 * gif.h - Convert p_img to GIF format and write it to f_gif
 *
 * Copyright (C) 2017 Jan Havran
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef GIF_H
#define GIF_H

#include "pcx2gif.h"

extern size_t gif_save(image_t *p_img, const FILE *f_gif);

#endif // GIF_H

