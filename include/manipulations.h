#ifndef MANIPULATIONS_H_
#define MANIPULATIONS_H_

bitmap_pixel_hsv_t* hsv_pixels;
bitmap_pixel_rgb_t* rgb_pixels;
uint32_t widthPx, heightPx;
bitmap_error_t error;

static void loadHSV(char[]);

static void saveHSV(char[]);

static void loadRGB(char[]);

static void saveRGB(char[]);

void brightness(char[], char[], int);

void saturation(char[], char[], int);

void grayscale(char[], char[]);

void red(char[], char[]);

#endif