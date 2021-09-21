#ifndef MANIPULATIONS_H_
#define MANIPULATIONS_H_

bitmap_pixel_hsv_t* pixels;
uint32_t widthPx, heightPx;
bitmap_error_t error;

void loadHSV(char[]);

void saveHSV(char[]);

void brightness(char[], char[], int);

void saturation(char[], char[], int);

void grayscale(char[], char[]);

#endif