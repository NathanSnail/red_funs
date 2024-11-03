#include "libbmp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Image *new_image(Image *img, uint16_t w, uint16_t h) {
	img->width = w;
	img->height = h;
	img->buffer = calloc(w * h, sizeof(Colour));
	return img;
}

void save_image(Image *img, char *path) {
	FILE *file = fopen(path, "wb");
	static int total_header_size = 26;

	// BMP header

	fwrite("BM", sizeof(char), 2, file);
	int size = (uint32_t)img->height * (uint32_t)img->width * sizeof(Colour) +
		     total_header_size;
	fwrite(&size, sizeof(size), 1, file);
	// we can use this to specify about what created the file i think
	int creation_data = 0;
	fwrite(&creation_data, sizeof(creation_data), 1, file);
	fwrite(&total_header_size, sizeof(total_header_size), 1, file);

	// DIB header

	int sizeof_dib = 12;
	fwrite(&sizeof_dib, sizeof(sizeof_dib), 1, file);
	fwrite(&img->width, sizeof(img->width), 1, file);
	fwrite(&img->height, sizeof(img->height), 1, file);
	uint16_t colour_planes = 1;
	fwrite(&colour_planes, sizeof(colour_planes), 1, file);
	uint16_t bpp = 32;
	fwrite(&bpp, sizeof(bpp), 1, file);

	// Pixel data

	fwrite(img->buffer, sizeof(*img->buffer),
		 (uint32_t)img->width * (uint32_t)img->height, file);
}

void set_pixel(Image *img, uint16_t x, uint16_t y, Colour colour) {
	img->buffer[y * img->width + x] = colour;
}

Colour get_pixel(Image *img, uint16_t x, uint16_t y) {
	return img->buffer[y * img->width + x];
}
