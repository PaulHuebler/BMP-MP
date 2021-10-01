#include <gtk/gtk.h>
#include <glib/gstdio.h>

#include "../include/bitmap.h"
#include "../include/manipulations.h"



static GtkWidget *window;
static GtkWidget *layout;
char *file_name;

GtkWidget * create_filechooser_dialog(char *init_path, GtkFileChooserAction action);
static void show_image(char *file_path);
static void set_brightness (char* file_path);


static void menu_response(GtkWidget* menu_item, gpointer data)
{
    GtkWidget *fdialog;
    char *fname;

    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Open") == 0)   
    {
        g_print("You pressed Open\n");
        fdialog = create_filechooser_dialog(fname, GTK_FILE_CHOOSER_ACTION_OPEN);
        if (gtk_dialog_run(GTK_DIALOG(fdialog)) == GTK_RESPONSE_OK) {
          fname = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fdialog));
          g_print("%s\n", fname);
          gtk_image_new_from_file(fname);
          gtk_widget_destroy(fdialog);
          file_name = fname;
          show_image(fname);

          copy_bmp(fname, "../img/old.bmp");
          copy_bmp("../img/old.bmp", "../img/new.bmp");
        }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Brightness") == 0)  
    {
        g_print("You pressed Brightness\n");
        set_brightness(file_name);
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Exit") == 0)  
    {
        gtk_main_quit(); //quit the application
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "About") == 0)
    {
        g_print("You pressed About\n");
    }
}

static void set_brightness (char* file_path)
{
  char *output_path = "/home/benni/Documents/BMP-MP/img/test1.bmp";
  GtkWidget *frame, *table;

  /*
  table = gtk_table_new(2, 2, TRUE);
  gtk_table_set_row_spacings(GTK_TABLE(table), 10);
  gtk_table_set_col_spacings(GTK_TABLE(table), 10);
  gtk_container_add(GTK_CONTAINER(window), table);

  frame = gtk_frame_new("Brightness");
  gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
  gtk_table_attach_defaults(GTK_TABLE(table), frame1, 0, 1, 0, 1);
  */
 
  brightness(file_path, output_path, 100);
  show_image(output_path);
}

GtkWidget * create_filechooser_dialog(char *init_path, GtkFileChooserAction action)
{
  GtkWidget *fdialog = NULL;

  switch (action) {
    case GTK_FILE_CHOOSER_ACTION_SAVE:
      fdialog = gtk_file_chooser_dialog_new("Save file", NULL, action,
        "Cancel", GTK_RESPONSE_CANCEL,
        "Save", GTK_RESPONSE_OK,
        NULL);
      break;

    case GTK_FILE_CHOOSER_ACTION_OPEN:
      fdialog = gtk_file_chooser_dialog_new("Open file", NULL, action,
        "Cancel", GTK_RESPONSE_CANCEL,
        "Open", GTK_RESPONSE_OK,
        NULL);
      break;

    //case GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER:
    //case GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER:
      break;
  }

  return fdialog;
}

static void show_image(char *file_path)
{
  GtkWidget *image;

  // show image
  image = gtk_image_new_from_file (file_path);
  gtk_layout_put(GTK_LAYOUT(layout), image, 20, 80);

  gtk_widget_show(layout);
  gtk_widget_show_all(window);

}

int main (int    argc, char **argv)
{
  GtkWidget *menu_bar, *menu_item, *file_menu, *help_menu, *vbox, *button,
            *tools_menu;

  gtk_init(&argc, &argv);

// Create Window:
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "BMP-MP");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  
// layoutcontainer for image
  layout = gtk_layout_new(NULL, NULL);                                         
  gtk_container_add(GTK_CONTAINER (window), layout);
  gtk_widget_show(layout);


// Menubar: 
  menu_bar = gtk_menu_bar_new();

  file_menu = gtk_menu_new();
  tools_menu = gtk_menu_new();
  help_menu = gtk_menu_new();
  
  menu_item = gtk_menu_item_new_with_label("File");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), file_menu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

  menu_item = gtk_menu_item_new_with_label("Help");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), help_menu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);
 
  menu_item = gtk_menu_item_new_with_label("Open");
  gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);
 
  menu_item = gtk_menu_item_new_with_label("Exit");
  gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);
 
  menu_item = gtk_menu_item_new_with_label("About");
  gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Tools");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), tools_menu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

  menu_item = gtk_menu_item_new_with_label("Brightness");
  gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);


  vbox = gtk_box_new(0,0);
  //button = gtk_button_new_with_label("This is a Button");
  gtk_box_pack_start(GTK_BOX(vbox), menu_bar,1,0,0);
  //gtk_box_pack_start(GTK_BOX(vbox), button,0,0,0);
  gtk_layout_put(GTK_LAYOUT(layout), vbox, 0, 0);
  

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
} 
