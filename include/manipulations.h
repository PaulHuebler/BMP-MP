#ifndef MANIPULATIONS_H_
#define MANIPULATIONS_H_

bitmap_pixel_hsv_t* hsv_pixels;
bitmap_pixel_rgb_t* rgb_pixels;
uint32_t widthPx, heightPx;
bitmap_error_t error;

static void loadHSV(char path[]);

static void saveHSV(char path[]);

static void loadRGB(char path[]);

static void saveRGB(char path[]);

void copy_bmp(char input_path[], char output_path[]);

void brightness(char input_path[], char output_path[], int value);

void saturation(char input_path[], char output_path[], int value);

void grayscale(char input_path[], char output_path[]);

void floyd_steinberg(char input_path[], char output_path[]);

void color_seperation(char input_path[], char output_path[]);

void color_enhancement(char input_path[], char output_path[], int color, float value);

#endif