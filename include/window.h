#ifndef WINDOW_H_
#define WINDOW_H_

#include <gtk/gtk.h>
#include <glib/gstdio.h>

static GtkWidget *window;
static GtkWidget *layout;
char *file_name;
bool manipulated = false;
float current_float_value = 1.0;
int current_int_value = 0;

// Funktionen zum Erstellen von Filechooserdialog und Imageabbildung
GtkWidget * create_filechooser_dialog(char *init_path, GtkFileChooserAction action);
static void show_image(char *file_path);

// Funktionen zum aufrufen der Manipulations und deren Speicherung
void set_brightness (GtkWidget* widget, gpointer data);
void set_saturation (GtkWidget* widget, gpointer data);
void set_contrast (GtkWidget* widget, gpointer data);
void set_exclusive_grayscale (GtkWidget* widget, gpointer data);



#endif