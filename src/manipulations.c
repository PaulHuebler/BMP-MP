#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/bitmap.h"
#include "../include/manipulations.h"

void manipulate(char path[], uint8_t manipulation, int opt1, int opt2) {

    bitmap_color_space_t colorspace;

    //Die Manipulationen mit dem Index 1 bis 10 nutzen den RGB-Farbraum, die restlichen den HSV-Farbraum.
    if (manipulation <= 10) {
        colorspace = BITMAP_COLOR_SPACE_RGB;
    } else {
        colorspace = BITMAP_COLOR_SPACE_HSV;
    }

    bitmap_pixel_hsv_t* pixels;
	uint32_t widthPx, heightPx;

	bitmap_error_t error = bitmapReadPixels(path, (bitmap_pixel_t**)&pixels, &widthPx, &heightPx, colorspace);
	assert(error == BITMAP_ERROR_SUCCESS);

    switch(manipulation) {

        case 11:    brightness(pixels, widthPx * heightPx, opt1);
                    break;

        case 12:    grayscale(pixels, widthPx * heightPx);
                    break;

        default:    printf("Die geforderte Manipulation steht noch nicht zur Verfügung.\n");
    }

    bitmap_parameters_t params;

	params.bottomUp = BITMAP_BOOL_TRUE;
	params.widthPx = widthPx;
	params.heightPx = heightPx;
	params.colorDepth = BITMAP_COLOR_DEPTH_24;
	params.compression = BITMAP_COMPRESSION_NONE;
	params.dibHeaderFormat = BITMAP_DIB_HEADER_INFO;
	params.colorSpace = colorspace;

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

static void grayscale(bitmap_pixel_hsv_t* pixels, uint32_t count)
{
		for (uint32_t x = 0; x < count; x++)
		{

			bitmap_pixel_hsv_t* pix = &pixels[x];

			pix->s = 0;
		}	
}