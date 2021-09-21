#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/bitmap.h"
#include "../include/manipulations.h"

void manipulate(char path[], uint manipulation, int opt1, int opt2) {

    bitmap_pixel_hsv_t* pixels;
	uint32_t widthPx, heightPx;

	bitmap_error_t error = bitmapReadPixels(path, (bitmap_pixel_t**)&pixels, &widthPx, &heightPx, BITMAP_COLOR_SPACE_HSV);
	assert(error == BITMAP_ERROR_SUCCESS);

    brightness(pixels, widthPx * heightPx, 100);

    bitmap_parameters_t params;

	params.bottomUp = BITMAP_BOOL_TRUE;
	params.widthPx = widthPx;
	params.heightPx = heightPx;
	params.colorDepth = BITMAP_COLOR_DEPTH_24;
	params.compression = BITMAP_COMPRESSION_NONE;
	params.dibHeaderFormat = BITMAP_DIB_HEADER_INFO;
	params.colorSpace = BITMAP_COLOR_SPACE_HSV;

    error = bitmapWritePixels("../img/result.bmp", BITMAP_BOOL_TRUE, &params, (bitmap_pixel_t*)pixels);
	assert(error == BITMAP_ERROR_SUCCESS);

	//Free the pixel array:
	free(pixels);

}

static void brightness(bitmap_pixel_hsv_t* pixels, uint32_t count, int value)
{
		for (uint32_t x = 0; x < count; x++)
		{

			bitmap_pixel_hsv_t* pix = &pixels[x];

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
}