#ifndef WINDOW_H_
#define WINDOW_H_

#include <gtk/gtk.h>
#include <glib/gstdio.h>

static GtkWidget *window;
static GtkWidget *layout;
char *file_name;
bool manipulated = false;

GtkWidget * create_filechooser_dialog(char *init_path, GtkFileChooserAction action);
static void show_image(char *file_path);
static void set_brightness (GtkWidget* widget, gpointer data);
void set_saturation (GtkWidget* widget, gpointer data);
void set_contrast (GtkWidget* widget, gpointer data);


#endif