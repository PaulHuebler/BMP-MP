#ifndef WINDOW_H_
#define WINDOW_H_

#include <gtk/gtk.h>
#include <glib/gstdio.h>

static GtkWidget *window;
static GtkWidget *layout;

char *file_name;
char *original_file;
// the image that should be manipulated
//char *manipulate_img;

float current_float_value = 1.0;
int current_int_value = 0;

// for UNDO/ REDO function and  Save operation (current image state)
int current_index = 0;   
bool IsDirty = true;                

// Funktionen zum Erstellen von Filechooserdialog und Imageabbildung
GtkWidget * create_filechooser_dialog (char *init_path, GtkFileChooserAction action);
static void show_image (char *file_path);

// SAVE / UNDO / REDO
char * index_path (int index_i);
void save (char *new_image);
void undo (char *new_image);
void redo ();

// Funktionen zum aufrufen der Manipulations und deren Speicherung
void set_brightness (GtkWidget* widget, gpointer data);/*
void set_saturation (GtkWidget* widget, gpointer data);
void set_contrast (GtkWidget* widget, gpointer data);

void set_exclusive_grayscale (GtkWidget* widget, gpointer data);
void set_floyd_steinberg (GtkWidget* menu_item, gpointer data);
void set_grayscale (GtkWidget* menu_item, gpointer data);
void set_color_seperation (GtkWidget* menu_item, gpointer data);

void set_invert_colors (GtkWidget* menu_item, gpointer data);
void set_sepia (GtkWidget* menu_item, gpointer data);
void set_mirror_vert (GtkWidget* menu_item, gpointer data);
void set_mirror_hor (GtkWidget* menu_item, gpointer data);
*/




#endif