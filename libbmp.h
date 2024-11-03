#pragma once
#include "stdint.h"

typedef union {
	uint32_t data;
	struct {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};
} Colour;

typedef struct {
	Colour *buffer;
	uint16_t width;
	uint16_t height;
} Image;

Image *new_image(Image *img, uint16_t w, uint16_t h);
void save_image(Image *to_save, char *path);
void set_pixel(Image *img, uint16_t x, uint16_t y, Colour colour);
Colour get_pixel(Image *img, uint16_t x, uint16_t y);
