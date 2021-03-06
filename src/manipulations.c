#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "../include/bitmap.h"
#include "../include/manipulations.h"

bitmap_pixel_hsv_t* hsv_pixels;
bitmap_pixel_rgb_t* rgb_pixels;
bitmap_pixel_rgb_t* result;
uint32_t widthPx, heightPx;
bitmap_error_t error;

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

int get_width(char path[]) {
	
	loadHSV(path);
	free(hsv_pixels);
	
	return widthPx;
}

int get_height(char path[]) {
	
	loadHSV(path);
	free(hsv_pixels);

	return heightPx;
}

void brightness(char input_path[], char output_path[], int value) {

	loadHSV(input_path);
	uint32_t count = heightPx * widthPx;

		for (uint32_t x = 0; x < count; x++) {

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

void saturation(char input_path[], char output_path[], int value) {

	loadHSV(input_path);
	uint32_t count = heightPx * widthPx;

		for (uint32_t x = 0; x < count; x++) {

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

void contrast(char input_path[], char output_path[], int value) {

	loadHSV(input_path);

	uint32_t count = heightPx * widthPx;

	long brightness = 0;

	// Ermitteln des durchschnittlichen Helligkeitswerts des Bildes
	for (uint32_t x = 0; x < count; x++) {

		bitmap_pixel_hsv_t* pix = &hsv_pixels[x];
		brightness += pix->v;
	}	

	brightness = brightness / count;

	// ??ndern der Helligkeitswerte jedes Pixels abh??ngig von seinem Verh??ltnis zur durchschn. Helligkeit
	for (uint32_t x = 0; x < count; x++) {

		bitmap_pixel_hsv_t* pix = &hsv_pixels[x];

		float divisor1 = (float)pix->v / (float)brightness;
		float divisor2 = (float)brightness / (float)pix->v;
		
		if (divisor1 - 1 >= 0) {

			if (pix->v + (divisor1 - 1) * value >= 255) {
				pix->v = 255;
			}
			else if (pix->v + (divisor1 - 1) * value <= 0) {
				pix->v = 0;
			}
			else {
				pix->v += (divisor1 - 1) * value;
			}
		}
		else {

			if (pix->v - (divisor2 - 1) * value >= 255) {
				pix->v = 255;
			}
			else if (pix->v - (divisor2 - 1) * value <= 0) {
				pix->v = 0;
			}
			else {
				pix->v -= (divisor2 - 1) * value;
			}
		}
	}	

	saveHSV(output_path);
}

void grayscale(char input_path[], char output_path[]) {

	loadHSV(input_path);
	uint32_t count = heightPx * widthPx;

		for (uint32_t x = 0; x < count; x++) {

			bitmap_pixel_hsv_t* pix = &hsv_pixels[x];

			pix->s = 0;
		}	

	saveHSV(output_path);
}

static int find_dominant_color() {

	uint32_t count = heightPx * widthPx;
	int current_max = 0;
	int dominant_color = 255;
	int counters[256] = {0};

	for (uint32_t x = 0; x < count; x++) {

		bitmap_pixel_hsv_t* pix = &hsv_pixels[x];

		counters[pix->h]++;
	}	

	for (uint32_t x = 0; x <= 255; x++) {

		if (counters[x] > current_max) {

			current_max = counters[x];
			dominant_color = x;
		}
	}

	return dominant_color;
}

void exclusive_grayscale(char input_path[], char output_path[], int tolerance) {

	loadHSV(input_path);

	uint32_t count = heightPx * widthPx;
	int dominant_color = find_dominant_color();

	printf("Dominante Farbe: %d\n", dominant_color);

		for (uint32_t x = 0; x < count; x++) {

			bitmap_pixel_hsv_t* pix = &hsv_pixels[x];

			if (abs(pix->h - dominant_color) >= tolerance)
				pix->s = 0;
		}	

	saveHSV(output_path);
}

// Select the color from the palette that exhibits the minimum Euclidean distance to the given pixel.
static bitmap_pixel_rgb_t select_from_pal(bitmap_pixel_rgb_t pix) {

	bitmap_pixel_rgb_t PAL[] = {	
		{ .r = 0x00, .g = 0x00, .b = 0x00 }, // Black
		{ .r = 0xFF, .g = 0x00, .b = 0x00 }, // Red
		{ .r = 0x00, .g = 0xFF, .b = 0x00 }, // Green
		{ .r = 0x00, .g = 0x00, .b = 0xFF }, // Blue
		{ .r = 0xFF, .g = 0xFF, .b = 0x00 }, // Yellow
		{ .r = 0xFF, .g = 0x00, .b = 0xFF }, // Pink
		{ .r = 0x00, .g = 0xFF, .b = 0xFF }, // Cyan
		{ .r = 0xFF, .g = 0xFF, .b = 0xFF }  // White
	};

	int dist = INT_MAX;
	bitmap_pixel_rgb_t pal;

	for (size_t i = 0; i < (sizeof(PAL) / sizeof(*PAL)); i++) {

		bitmap_pixel_rgb_t new_pal = PAL[i];

		int dr = new_pal.r - pix.r, dg = new_pal.g - pix.g, db = new_pal.b - pix.b;
		int new_dist = (dr * dr) + (dg * dg) + (db * db);

		if (new_dist < dist) {

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

	if ((x < width) && (y < height)) {

		bitmap_pixel_rgb_t* pix = &pixels[(width * y) + x];

		apply_quant_err_comp(&pix->r, qe[0], fac);
		apply_quant_err_comp(&pix->g, qe[1], fac);
		apply_quant_err_comp(&pix->b, qe[2], fac);
	}
}

void floyd_steinberg(char input_path[], char output_path[]) {

	loadRGB(input_path);

	for (uint32_t y = 0; y < heightPx; y++) {

		for (uint32_t x = 0; x < widthPx; x++) {

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

	for (uint32_t y = 0; y < heightPx; y++) {

		for (uint32_t x = 0; x < widthPx; x++) {

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

	for (uint32_t x = 0; x < count; x++) {

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

		// l??uft die "Zeilen" ab
		for (uint32_t x = 0; x < heightPx; x++) {
			
			// l??uft die "Spalten" ab
			for (uint32_t y = 0; y < widthPx/2; y++) {
				
				// Vertauscht die gegen??berliegenden Pixel
				bitmap_pixel_rgb_t* pix1 = &rgb_pixels[x*widthPx + y];
				bitmap_pixel_rgb_t* pix2 = &rgb_pixels[x*widthPx + widthPx - y - 1];
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

		// l??uft die "Spalten" ab
		for (uint32_t x = 0; x < widthPx; x++) {
			
			// l??uft die "Zeilen" ab
			for (uint32_t y = 0; y < heightPx/2; y++) {
				
				// Vertauscht die gegen??berliegenden Pixel
				bitmap_pixel_rgb_t* pix1 = &rgb_pixels[y*widthPx + x];
				bitmap_pixel_rgb_t* pix2 = &rgb_pixels[(heightPx - y - 1)*widthPx + x];
				bitmap_pixel_rgb_t* temp = &rgb_pixels[0];
				*temp = *pix1;
				*pix1 = *pix2;
				*pix2 = *temp;
			}
		}	

	saveRGB(output_path);
}

// Grundlagen wurden aus diesem Eintrag entnommen und angepasst: https://stackoverflow.com/questions/42186498/gaussian-blur-image-processing-c
static int calc_gauss_pixel(int col, int row, int width, int height, char component) {

	int kernel[3][3] = { 1, 2, 1,
                   		2, 4, 2,
                   		1, 2, 1 };

    int sum = 0;
    int divisor = 0;
	int color = 0;
	
    for (int j = -1; j <= 1; j++) {

        for (int i = -1; i <= 1; i++) {

            if ((row + j) >= 0 && (row + j) < height && (col + i) >= 0 && (col + i) < width) {

				bitmap_pixel_rgb_t* pix = &rgb_pixels[(row + j) * width + (col + i)];

				switch(component) {

					case 'r':
						color = pix->r;
						break;

					case 'g':
						color = pix->g;
						break;

					case 'b':
						color = pix->b;
						break;

					default:
						printf("Etwas ist schief gelaufen (calc_gauss_pixel)");
				}

                sum += (int)(color * kernel[i + 1][j + 1]);
                divisor += kernel[i + 1][j + 1];
            }
        }
    }

    return (int)(sum / divisor);
}

void gaussian_blur2D(char input_path[], char output_path[]) {

	loadRGB(input_path);

	int width = (int)widthPx;
	int height = (int)heightPx; 

	error = bitmapReadPixels(input_path, (bitmap_pixel_t**)&result, &widthPx, &heightPx, BITMAP_COLOR_SPACE_RGB);
	assert(error == BITMAP_ERROR_SUCCESS);

    for (int row = 0; row < height; row++) {

        for (int col = 0; col < width; col++) {
           
			bitmap_pixel_rgb_t* pix = &result[row * width + col];
				
            pix->r = calc_gauss_pixel(col, row, width, height, 'r');
			pix->g = calc_gauss_pixel(col, row, width, height, 'g');
			pix->b = calc_gauss_pixel(col, row, width, height, 'b');  
        }
    }

	uint32_t count = heightPx * widthPx;

	// Zuweisen der Pixel aus result in rgb_pixels zum speichern
	for (uint32_t x = 0; x < count; x++) {

		bitmap_pixel_rgb_t* pix1 = &rgb_pixels[x];
		bitmap_pixel_rgb_t* pix2 = &result[x];

		*pix1 = *pix2;
	}	

	saveRGB(output_path);
}

void temperature(char input_path[], char output_path[], int value) {

	loadRGB(input_path);

	uint32_t count = heightPx * widthPx;

	value = value / 2;

		for (uint32_t x = 0; x < count; x++) {

			bitmap_pixel_rgb_t* pix = &rgb_pixels[x];

			if (pix->r + 1.5 * value >= 255) {
				pix->r = 255;
			} 
			else if (pix->r + 1.5 * value < 0) {
				pix->r = 0;
			} 
			else {
				pix->r += 1.5 * value;
			}

			if (pix->g + 0.5 * value >= 255) {
				pix->g = 255;
			} 
			else if (pix->g + 0.5 * value < 0) {
				pix->g = 0;
			} 
			else {
				pix->g += 0.5 * value;
			}

			if (pix->b - value <= 0) {
				pix->b = 0;
			} 
			else if (pix->b - value > 255) {
				pix->b = 255;
			} 
			else {
				pix->b -= value;
			}
		}	

	saveRGB(output_path);
}

void colorswap(char input_path[], char output_path[], int old_color, int new_color, int tolerance) {

	loadHSV(input_path);

	uint32_t count = heightPx * widthPx;

		for (uint32_t x = 0; x < count; x++) {

			bitmap_pixel_hsv_t* pix = &hsv_pixels[x];

			if (abs(pix->h - old_color) <= tolerance) {

				if (new_color + (pix->h - old_color) <= 0) { 
					pix->h = 0;
				}
				else if (new_color + (pix->h - old_color) >= 255) {
					pix->h = 255;
				}
				else {
					pix->h = new_color + (pix->h - old_color);
				}
			}
		}	

	saveHSV(output_path);
}

static int calc_sobel (int Gx, int Gy) {

    int x = sqrt(Gx*Gx + Gy*Gy);

    if (x > 255)
    	x = 255;

    return x;
}

void sobel_edge_detection(char input_path[], char output_path[]) {

	loadRGB(input_path);

	error = bitmapReadPixels(input_path, (bitmap_pixel_t**)&result, &widthPx, &heightPx, BITMAP_COLOR_SPACE_RGB);
	assert(error == BITMAP_ERROR_SUCCESS);

	uint32_t count = heightPx * widthPx;

	//Konvertierung in Graustufen (RGB)
	for (uint32_t x = 0; x < count; x++) {

		bitmap_pixel_rgb_t* pix = &rgb_pixels[x];
		int value = (pix->r + pix->g + pix->b) / 3;
		pix->r = pix->g = pix->b = value;
	}	

	int height = heightPx;
	int width = widthPx;

	// Gradienten-Kernel in x- und y-Richtung
	int Gx[3][3] = {{-1, 0, 1}, 
					{-2, 0, 2}, 
					{-1, 0, 1}};

	int Gy[3][3] = {{-1, -2, -1}, 
					{0, 0, 0}, 
					{1, 2, 1}};

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			int Gx_v = 0;
			int Gy_v = 0;

			for (int x = -1; x < 2; x++) {

				for (int y = -1; y < 2; y++) {
					
					//Check, ob die Pixel ausserhalb des Bildes liegen
					if (i + x < height && i + x > 0 && j + y < width && j + y > 0) {

						bitmap_pixel_rgb_t* pix = &rgb_pixels[(i + x) * width + j + y];

						//Anwenden der Sobel-Operatoren
						Gx_v += pix->r * Gx[x+1][y+1];
						Gy_v += pix->r * Gy[x+1][y+1];

					}
				}
			}

			bitmap_pixel_rgb_t* pix = &result[i * width + j];

			//Speichern der ermittelten Gradientenwerte
			pix->r = pix->g = pix->b = calc_sobel(Gx_v, Gy_v);
		}
	}

	//Kopieren vom tempor??ren ins finale Pixelarray
	for (uint32_t x = 0; x < count; x++) {

		bitmap_pixel_rgb_t* pix1 = &rgb_pixels[x];
		bitmap_pixel_rgb_t* pix2 = &result[x];

		*pix1 = *pix2;
	}	

	free(result);

	saveRGB(output_path);
}
