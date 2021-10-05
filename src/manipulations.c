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

void copy_bmp(char input_path[], char output_path[]) {

	loadHSV(input_path);
	saveHSV(output_path);
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

void contrast(char input_path[], char output_path[], float value) 
{
	loadRGB(input_path);

	uint32_t count = heightPx * widthPx;

		for (uint32_t x = 0; x < count; x++)
		{

			bitmap_pixel_rgb_t* pix = &rgb_pixels[x];

			if ((pix->r * value) > 255) {
				pix->r = 255;
			} 
			else if ((pix->r * value) < 0) {
				pix->r = 0;
			}
			else {
				pix->r = (pix->r * value);
			}

			if ((pix->g * value) > 255) {
				pix->g = 255;
			} 
			else if ((pix->g * value) < 0) {
				pix->g = 0;
			}
			else {
				pix->g = (pix->g * value);
			}

			if ((pix->b * value) > 255) {
				pix->b = 255;
			} 
			else if ((pix->b * value) < 0) {
				pix->b = 0;
			}
			else {
				pix->b = (pix->b * value);
			}
		}	

	saveRGB(output_path);
}

void grayscale(char input_path[], char output_path[]) {

	loadHSV(input_path);
	uint32_t count = heightPx * widthPx;

		for (uint32_t x = 0; x < count; x++)
		{

			bitmap_pixel_hsv_t* pix = &hsv_pixels[x];

			pix->s = 0;
		}	

	saveHSV(output_path);
}

static int find_dominant_color() {

	uint32_t count = heightPx * widthPx;
	int current_max = 0;
	int dominant_color = 255;
	int counters[256];

	for (uint32_t x = 0; x < count; x++) {

			bitmap_pixel_hsv_t* pix = &hsv_pixels[x];

			counters[pix->h]++;
		}	

	for (uint32_t x = 0; x <= 255; x++) {

		// Ohne diese Ausgabe werden plötzlich ganz andere Werte als dominante Farbe ermittelt -> Quantentheorie? :o
		printf("%d: %d | ", x, counters[x]);

		if (counters[x] >= current_max) {

			current_max = counters[x];
			dominant_color = x;
		}
	}

	return dominant_color;

}

void exclusive_grayscale(char input_path[], char output_path[], int tolerance) {

	uint32_t count = heightPx * widthPx;
	int dominant_color = find_dominant_color();

	printf("Dominante Farbe: %d\n", dominant_color);

		for (uint32_t x = 0; x < count; x++)
		{

			bitmap_pixel_hsv_t* pix = &hsv_pixels[x];

			if (abs(pix->h - dominant_color) >= tolerance) {
				pix->s = 0;
			}
		}	
}

// Select the color from the palette that exhibits the minimum Euclidean distance to the given pixel.
static bitmap_pixel_rgb_t select_from_pal(bitmap_pixel_rgb_t pix) {

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
static void apply_quant_err_comp(bitmap_component_t* c, int qe, int fac) {

	int new_c = *c + ((qe * fac) / 16);
	*c = (new_c < 0) ? 0 : (new_c > 255) ? 255 : new_c;
}

static void apply_quant_err(bitmap_pixel_rgb_t* pixels, uint32_t width, uint32_t height, uint32_t x, uint32_t y, const int* qe, int fac) {

	if ((x < width) && (y < height))
	{
		bitmap_pixel_rgb_t* pix = &pixels[(width * y) + x];

		apply_quant_err_comp(&pix->r, qe[0], fac);
		apply_quant_err_comp(&pix->g, qe[1], fac);
		apply_quant_err_comp(&pix->b, qe[2], fac);
	}
}

void floyd_steinberg(char input_path[], char output_path[]) {


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

void color_seperation(char input_path[], char output_path[]) {

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

void invert_colors(char input_path[], char output_path[]) {

	loadRGB(input_path);

	uint32_t count = heightPx * widthPx;

		for (uint32_t x = 0; x < count; x++) {

			bitmap_pixel_rgb_t* pix = &rgb_pixels[x];

			pix->r = 255 - pix->r;
			pix->g = 255 - pix->g;
			pix->b = 255 - pix->b;
		}	

	saveRGB(output_path);
}

void sepia(char input_path[], char output_path[]) {

	loadRGB(input_path);

	uint32_t count = heightPx * widthPx;

	for (uint32_t x = 0; x < count; x++)
		{

			bitmap_pixel_rgb_t* pix = &rgb_pixels[x];

			// Calculations: https://www.techrepublic.com/blog/how-do-i/how-do-i-convert-images-to-grayscale-and-sepia-tone-using-c/
			int output_r = (pix->r * 0.393 + pix->g * 0.769 + pix->b * 0.189);
			int output_g = (pix->r * 0.349 + pix->g * 0.686 + pix->b * 0.168);
			int output_b = (pix->r * 0.272 + pix->g * 0.534 + pix->b * 0.131);

			if (output_r > 255) {
				pix->r = 255;
			} 
			else {
				pix->r = output_r;
			}

			if (output_g > 255) {
				pix->g = 255;
			} 
			else {
				pix->g = output_g;
			}

			if (output_b > 255) {
				pix->b = 255;
			} 
			else {
				pix->b = output_b;
			}
			
		}

	saveRGB(output_path);

}

void mirror_vert(char input_path[], char output_path[]) {

	loadRGB(input_path);

		// läuft die "Zeilen" ab
		for (uint32_t x = 0; x < heightPx; x++) {
			
			// läuft die "Spalten" ab
			for (uint32_t y = 0; y < widthPx/2; y++) {

				bitmap_pixel_rgb_t* pix1 = &rgb_pixels[x*widthPx + y];
				bitmap_pixel_rgb_t* pix2 = &rgb_pixels[x*widthPx + widthPx - y];
				bitmap_pixel_rgb_t* temp = &rgb_pixels[0];
				*temp = *pix1;
				*pix1 = *pix2;
				*pix2 = *temp;
			}
		}	

	saveRGB(output_path);
}

void mirror_hor(char input_path[], char output_path[]) {

	loadRGB(input_path);

		// läuft die "Spalten" ab
		for (uint32_t x = 0; x < widthPx; x++) {
			
			// läuft die "Zeilen" ab
			for (uint32_t y = 0; y < heightPx/2; y++) {

				bitmap_pixel_rgb_t* pix1 = &rgb_pixels[y*widthPx + x];
				bitmap_pixel_rgb_t* pix2 = &rgb_pixels[(heightPx - y)*widthPx + x];
				bitmap_pixel_rgb_t* temp = &rgb_pixels[0];
				*temp = *pix1;
				*pix1 = *pix2;
				*pix2 = *temp;
			}
		}	

	saveRGB(output_path);
}