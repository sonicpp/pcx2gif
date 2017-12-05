/*
 * pcx.c - Read PCX image from f_pcx and save it into p_img
 *
 * Copyright (C) 2017 Jan Havran
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "pcx.h"

/* PCX header */
struct PCX_header
{
	uint8_t manufacturer;
	uint8_t version;
	uint8_t encoding;
	uint8_t bits_per_pixel;
	uint16_t xmin;
	uint16_t ymin;
	uint16_t xmax;
	uint16_t ymax;
	uint16_t h_dpi;
	uint16_t v_dpi;
	uint8_t colormap[48];
	uint8_t reserved;
	uint8_t planes_cnt;
	uint16_t bytes_per_line;
	uint16_t palette_info;
	uint16_t h_screen_size;
	uint16_t v_screen_size;
	uint8_t filler[54];
} __attribute__((packed));

#define SIZE_HEADER		(sizeof(struct PCX_header))

static size_t load_header(struct PCX_header *header, FILE *f_pcx)
{
	assert(header);
	assert(f_pcx);
	size_t cnt;

	cnt = fread(header, 1, SIZE_HEADER, f_pcx);
	if (cnt != SIZE_HEADER)
		return 0;

	/* Check header */
	if (
		/* Check PCX flag */
		(header->manufacturer != 0x0A) ||
		/* BytesPerLine MUST be an EVEN number */
		(header->bytes_per_line & 0x1) ||
		/* TODO */
		(header->xmax < header->xmin || header->ymax < header->ymin) ||
		/* TODO */
		(header->bytes_per_line < (header->xmax - header->xmin + 1))
	)
		return 0;

	return cnt;
}

static size_t parse_row(uint8_t *data, uint16_t len, uint16_t size, FILE *f_pcx)
{
	assert(data);
	assert(len <= size);
	assert(f_pcx);
	size_t cnt;

	cnt = fread(data, 1, size, f_pcx);
	if (cnt != size)
		return 0;

	return cnt;
}

size_t pcx_load(image_t *p_img, FILE *f_pcx)
{
	struct PCX_header header;
	size_t pcx_len = 0;
	size_t block_len = 0;
	uint16_t width, height;

	/* Parse Header */
	if ((block_len = load_header(&header, f_pcx)) == 0) {
		fprintf(stderr, "PCX: Invalid header\n");
		return 0;
	}
	pcx_len += block_len;

	width = header.xmax - header.xmin + 1;
	height = header.ymax - header.ymin + 1;
	if ((p_img->data = (uint8_t *) malloc(3u * width * height)) == NULL) {
		fprintf(stderr, "PCX: Out of memory\n");
		return 0;
	}
	printf("Size: %u, %ux%u\n", header.planes_cnt * header.bytes_per_line, width, height);

	while (height--) {
		if ((block_len = parse_row(p_img->data, width,
		header.bytes_per_line, f_pcx)) == 0) {
			fprintf(stderr, "PCX: Invalid data\n");
			free(p_img->data);
			p_img->data = NULL;
			return 0;
		}
		pcx_len += block_len;
	}

	return pcx_len;
}

