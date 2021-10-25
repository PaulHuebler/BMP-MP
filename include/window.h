#ifndef WINDOW_H_
#define WINDOW_H_

#include <gtk/gtk.h>
#include <glib/gstdio.h>


static GtkWidget *window, *vbox;
static GtkWidget *layout;
static GtkWidget *image;
static GtkWidget *frame_b;
static GtkWidget *plus_btn, *minus_btn, *undo_btn;
static GtkWidget *old_color_entry, *new_color_entry;
static GtkWidget *color_chooser;

static GdkRGBA rgba;

typedef struct HsvColor
{
    int hue;
    float saturation;
    float value;
} HsvColor;

static int color_picked = 0;

// start parameters for window
int width = 500;
int height = 500;

static char *current_file;
static char *original_file;

float current_float_value = 1.0;
int current_int_value = 0;
gint old_color = 100;
gint new_color = 100;

// for UNDO/ REDO function and  Save operation (current image state)
static int current_index = -1;   
bool manipulated = false;                

// Funktionen zum Erstellen von Filechooserdialog und Imageabbildung
GtkWidget * create_filechooser_dialog (char *init_path, GtkFileChooserAction action);
static void show_image (char *file_path);
void set_hsv_color ();

// SAVE / UNDO 
void save ();
void undo ();

// Destroy all widgets
void destroy_widgets();


// Funktionen zum aufrufen der Manipulations und deren Speicherung
void set_brightness (GtkWidget* widget, gpointer data);
void set_saturation (GtkWidget* widget, gpointer data);
void set_contrast (GtkWidget* widget, gpointer data);
void set_exclusive_grayscale (GtkWidget* widget, gpointer data);
void set_floyd_steinberg (GtkWidget* menu_item, gpointer data);
void set_grayscale (GtkWidget* menu_item, gpointer data);
void set_color_seperation (GtkWidget* menu_item, gpointer data);
void set_invert_colors (GtkWidget* menu_item, gpointer data);
void set_sepia (GtkWidget* menu_item, gpointer data);
void set_mirror (GtkWidget* menu_item, gpointer data);
void set_gaussian_blur2D (GtkWidget* menu_item, gpointer data);
void set_temperature (GtkWidget* menu_item, gpointer data);
void set_color_swap (GtkWidget* widget, gpointer data);
void set_sobel_edge_detection (GtkWidget* menu_item, gpointer data);




#endif