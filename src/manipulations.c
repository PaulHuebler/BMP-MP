#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "../include/bitmap.h"
#include "../include/manipulations.h"

bitmap_pixel_hsv_t* hsv_pixels;
bitmap_pixel_rgb_t* rgb_pixels;
uint32_t widthPx, heightPx;
bitmap_error_t error;

bitmap_pixel_rgb_t PAL[] =
{
	{ .r = 0x00, .g = 0x00, .b = 0x00 }, // Black
	{ .r = 0xFF, .g = 0x00, .b = 0x00 }, // Red
	{ .r = 0x00, .g = 0xFF, .b = 0x00 }, // Green
	{ .r = 0x00, .g = 0x00, .b = 0xFF }, // Blue
	{ .r = 0xFF, .g = 0xFF, .b = 0x00 }, // Yellow
	{ .r = 0xFF, .g = 0x00, .b = 0xFF }, // Pink
	{ .r = 0x00, .g = 0xFF, .b = 0xFF }, // Cyan
	{ .r = 0xFF, .g = 0xFF, .b = 0xFF }  // White
};

static void loadHSV(char path[]) {

	error = bitmapReadPixels(path, (bitmap_pixel_t**)&hsv_pixels, &widthPx, &heightPx, BITMAP_COLOR_SPACE_HSV);
	assert(error == BITMAP_ERROR_SUCCESS);
}

static void saveHSV(char path[]) {

	bitmap_parameters_t params;

	params.bottomUp = BITMAP_BOOL_TRUE;
	params.widthPx = widthPx;
	params.heightPx = heightPx;
	params.colorDepth = BITMAP_COLOR_DEPTH_24;
	params.compression = BITMAP_COMPRESSION_NONE;
	params.dibHeaderFormat = BITMAP_DIB_HEADER_INFO;
	params.colorSpace = BITMAP_COLOR_SPACE_HSV;

    error = bitmapWritePixels(path, BITMAP_BOOL_TRUE, &params, (bitmap_pixel_t*)hsv_pixels);
	assert(error == BITMAP_ERROR_SUCCESS);

	//Free the pixel array:
	free(hsv_pixels);

}

static void loadRGB(char path[]) {

	error = bitmapReadPixels(path, (bitmap_pixel_t**)&rgb_pixels, &widthPx, &heightPx, BITMAP_COLOR_SPACE_RGB);
	assert(error == BITMAP_ERROR_SUCCESS);
}

static void saveRGB(char path[]) {

	bitmap_parameters_t params;

	params.bottomUp = BITMAP_BOOL_TRUE;
	params.widthPx = widthPx;
	params.heightPx = heightPx;
	params.colorDepth = BITMAP_COLOR_DEPTH_24;
	params.compression = BITMAP_COMPRESSION_NONE;
	params.dibHeaderFormat = BITMAP_DIB_HEADER_INFO;
	params.colorSpace = BITMAP_COLOR_SPACE_RGB;

    error = bitmapWritePixels(path, BITMAP_BOOL_TRUE, &params, (bitmap_pixel_t*)rgb_pixels);
	assert(error == BITMAP_ERROR_SUCCESS);

	//Free the pixel array:
	free(rgb_pixels);

}

void brightness(char input_path[], char output_path[], int value)
{

	loadHSV(input_path);
	uint32_t count = heightPx * widthPx;

		for (uint32_t x = 0; x < count; x++)
		{

			bitmap_pixel_hsv_t* pix = &hsv_pixels[x];

			if ((pix->v + value) > 255) {
				pix->v = 255;
			} 
			else if ((pix->v + value) < 0) {
				pix->v = 0;
			}
			else {
				pix->v = (pix->v + value);
			}
		}	

	saveHSV(output_path);
}

void saturation(char input_path[], char output_path[], int value)
{
	loadHSV(input_path);
	uint32_t count = heightPx * widthPx;

		for (uint32_t x = 0; x < count; x++)
		{

			bitmap_pixel_hsv_t* pix = &hsv_pixels[x];

			if ((pix->s + value) > 255) {
				pix->s = 255;
			} 
			else if ((pix->s + value) < 0) {
				pix->s = 0;
			}
			else {
				pix->s = (pix->s + value);
			}
		}	

	saveHSV(output_path);
}

void grayscale(char input_path[], char output_path[])
{
	loadHSV(input_path);
	uint32_t count = heightPx * widthPx;

		for (uint32_t x = 0; x < count; x++)
		{

			bitmap_pixel_hsv_t* pix = &hsv_pixels[x];

			pix->s = 0;
		}	

	saveHSV(output_path);
}

// Select the color from the palette that exhibits the minimum Euclidean distance to the given pixel.
static bitmap_pixel_rgb_t select_from_pal(bitmap_pixel_rgb_t pix)
{
	int dist = INT_MAX;
	bitmap_pixel_rgb_t pal;

	for (size_t i = 0; i < (sizeof(PAL) / sizeof(*PAL)); i++)
	{
		bitmap_pixel_rgb_t new_pal = PAL[i];

		int dr = new_pal.r - pix.r, dg = new_pal.g - pix.g, db = new_pal.b - pix.b;
		int new_dist = (dr * dr) + (dg * dg) + (db * db);

		if (new_dist < dist)
		{
			dist = new_dist;
			pal = PAL[i];
		}
	}

	return pal;
}

// Helper funcs for dithering
static void apply_quant_err_comp(bitmap_component_t* c, int qe, int fac)
{
	int new_c = *c + ((qe * fac) / 16);
	*c = (new_c < 0) ? 0 : (new_c > 255) ? 255 : new_c;
}

static void apply_quant_err(bitmap_pixel_rgb_t* pixels, uint32_t width, uint32_t height, uint32_t x, uint32_t y, const int* qe, int fac)
{
	if ((x < width) && (y < height))
	{
		bitmap_pixel_rgb_t* pix = &pixels[(width * y) + x];

		apply_quant_err_comp(&pix->r, qe[0], fac);
		apply_quant_err_comp(&pix->g, qe[1], fac);
		apply_quant_err_comp(&pix->b, qe[2], fac);
	}
}

void floyd_steinberg(char input_path[], char output_path[])
{

	loadRGB(input_path);

	for (uint32_t y = 0; y < heightPx; y++)
	{
		for (uint32_t x = 0; x < widthPx; x++)
		{
			// Get a pointer to the pixel and select a palette color for it.
			bitmap_pixel_rgb_t* pix = &rgb_pixels[(widthPx * y) + x];
			bitmap_pixel_rgb_t pal = select_from_pal(*pix);
			// Calculate the quantization error in all components.
			int qe[] = { pix->r - pal.r, pix->g - pal.g, pix->b - pal.b };

			// Distribute the error onto the neighbours.
			// Note: For x == 0, the expression "x - 1" will underflow and wrap.
			// This is *not* UB for unsigned.
			// In consequence, the "(x < width)" guard in "apply_quant_err()" will catch that case.
			apply_quant_err(rgb_pixels, widthPx, heightPx, x + 1, y, qe, 7);
			apply_quant_err(rgb_pixels, widthPx, heightPx, x, y + 1, qe, 5);
			apply_quant_err(rgb_pixels, widthPx, heightPx, x - 1, y + 1, qe, 3);
			apply_quant_err(rgb_pixels, widthPx, heightPx, x + 1, y + 1, qe, 1);

			// Assign the new pixel value.
			*pix = pal;
		}
	}

	saveRGB(output_path);

}

void color_seperation(char input_path[], char output_path[])
{
	loadRGB(input_path);

	for (uint32_t y = 0; y < heightPx; y++)
	{
		for (uint32_t x = 0; x < widthPx; x++)
		{
			// Get a pointer to the pixel and select a palette color for it.
			bitmap_pixel_rgb_t* pix = &rgb_pixels[(widthPx * y) + x];
			bitmap_pixel_rgb_t pal = select_from_pal(*pix);

			// Assign the new pixel value.
			*pix = pal;
		}
	}

	saveRGB(output_path);
} 