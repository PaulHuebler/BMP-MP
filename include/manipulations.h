#ifndef MANIPULATIONS_H_
#define MANIPULATIONS_H_

void manipulate(char[], uint8_t, int, int);

static void brightness(bitmap_pixel_hsv_t*, uint32_t, int);

static void saturation(bitmap_pixel_hsv_t*, uint32_t, int);

static void grayscale(bitmap_pixel_hsv_t*, uint32_t);

#endif