#ifndef MANIPULATIONS_H_
#define MANIPULATIONS_H_

bitmap_pixel_hsv_t* hsv_pixels;
bitmap_pixel_rgb_t* rgb_pixels;
uint32_t widthPx, heightPx;
bitmap_error_t error;

// Lädt eine Bitmap ins Pixel-Array (HSV-Farbraum)
static void loadHSV(char path[]);

// Speichert das Pixel-Array als Bitmap (HSV-Farbraum)
static void saveHSV(char path[]);

// Lädt eine Bitmap ins Pixel-Array (RGB-Farbraum)
static void loadRGB(char path[]);

// Speichert das Pixel-Array als Bitmap (RGB-Farbraum)
static void saveRGB(char path[]);

// Findet den H-Wert (0-255), den die meisten Pixel im Bild besitzen (HSV)
static int find_dominant_color();

// Zum Berechnen der Einzelnen Pixel für den Gaussian Blur Filter (RGB)
static int calc_gauss_pixel(int col, int row, int width, int height, char component);

// Kopiert eine Bitmap mittels des Pixel-Arrays an einen neuen Speicherort (HSV)
void copy_bmp(char input_path[], char output_path[]);

// Gibt die Breite des Bildes in Pixel zurück.
int get_width(char path[]);

// Gibt die Höhe des Bildes in Pixel zurück.
int get_height(char path[]);

// Verändert die Helligkeit des Bildes (HSV) 
void brightness(char input_path[], char output_path[], int value);

// Verändert die Sättigung des Bildes (HSV) 
void saturation(char input_path[], char output_path[], int value);

// Verändert den Kontrast des Bildes (RGB)
void contrast(char input_path[], char output_path[], float value);

// Stellt das Bild in Graustufen dar (HSV) 
void grayscale(char input_path[], char output_path[]);

// Stellt das Bild in Graustufen dar, lässt jedoch die dominante Farbe farbig (HSV)
void exclusive_grayscale(char input_path[], char output_path[], int tolerance);

// Floyd-Steinberg-Dithering zur Verringerung der Farbanzahl (RGB)
void floyd_steinberg(char input_path[], char output_path[]);

// Verringert die Anzahl der Farben, indem jedem Pixel eine Palettenfarbe zugewiesen wird (RGB)
void color_seperation(char input_path[], char output_path[]);

// Eine Palettenfarbe wird verstärkt (RGB)
void color_enhancement(char input_path[], char output_path[], int color, float value);

// Eine Farbe wird durch eine andere ersetzt (HSV)
void colorswap(char input_path[], char output_path[], int old_color, int new_color, int tolerance);

// Invertieren der Farben (RGB)
void invert_colors(char input_path[], char output_path[]);

// Färbt ein Bild in Sepia-Farben (RGB)
void sepia(char input_path[], char output_path[]);

// Spiegelt das Bild vertikal (RGB)
void mirror_vert(char input_path[], char output_path[]);

// Spiegelt das Bild horizontal (RGB)
void mirror_hor(char input_path[], char output_path[]);

// Wendet einen Unschärfe-Filter auf das Bild an (RGB)
void gaussian_blur2D(char input_path[], char output_path[]);

// Passt die Farbtemperatur des Bildes an (Naive Implementation). value sollte zwischen -1 und 1 liegen (RGB)
void temperature(char input_path[], char output_path[], float value);

#endif