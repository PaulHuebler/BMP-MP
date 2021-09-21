#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/bitmap.h"
#include "../include/manipulations.h"

bitmap_pixel_hsv_t* hsv_pixels;
bitmap_pixel_rgb_t* rgb_pixels;
uint32_t widthPx, heightPx;
bitmap_error_t error;

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

void red(char input_path[], char output_path[])
{
	loadRGB(input_path);
	uint32_t count = heightPx * widthPx;

		for (uint32_t x = 0; x < count; x++)
		{

			bitmap_pixel_rgb_t* pix = &rgb_pixels[x];

			pix->r = 255;
			pix->g = 0;
			pix->b = 0;
		}	

	saveRGB(output_path);
}