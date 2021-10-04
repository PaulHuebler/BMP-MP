#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include <stdint.h>

#include "../include/bitmap.h"
#include "../include/manipulations.h"


static GtkWidget *window;
static GtkWidget *layout;
char *file_name;


GtkWidget * create_filechooser_dialog(char *init_path, GtkFileChooserAction action);
static void show_image(char *file_path);
static void set_brightness (GtkWidget* widget, gpointer data);
void set_saturation (GtkWidget* widget, gpointer data);


/**********************************************************************************************************************************************************************
	Menubar/ show_image()/ filechooser 
**********************************************************************************************************************************************************************/

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
          copy_bmp(file_name, "../img/old.bmp");        // backup of the original
        }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Brightness") == 0)  
    {
        g_print("You pressed Brightness\n");
        copy_bmp(file_name, "../img/old.bmp");        // backup of the original
        //eventuell "../img/brightness.bmp"    --> UNDO jeder Änderung (Bright, Sat., b/w)
        

        GtkWidget *plus_btn, *minus_btn, *undo_btn;
        GtkWidget *frame_b;
        int p = 10;
        int m = -10;

        plus_btn = gtk_button_new_with_label("+10");
        minus_btn = gtk_button_new_with_label("-10");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), minus_btn, 100, 680);
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 200, 680);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 300, 680);
        g_signal_connect (G_OBJECT(minus_btn), "clicked", 
                          G_CALLBACK(set_brightness), GINT_TO_POINTER(m));
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_brightness), GINT_TO_POINTER(p));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(set_brightness), GINT_TO_POINTER(0));
                          
        frame_b = gtk_frame_new("Brightness");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, 620);

        gtk_widget_show(layout);
        gtk_widget_show_all(window);
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Saturation") == 0)  
    {
        g_print("You pressed Saturation\n");
        
        GtkWidget *plus_btn, *minus_btn, *undo_btn;
        GtkWidget *frame_b;
        int p = 10;
        int m = -10;

        plus_btn = gtk_button_new_with_label("+10");
        minus_btn = gtk_button_new_with_label("-10");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), minus_btn, 100, 680);
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 200, 680);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 300, 680);
        g_signal_connect (G_OBJECT(minus_btn), "clicked", 
                          G_CALLBACK(set_saturation), GINT_TO_POINTER(m));
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_saturation), GINT_TO_POINTER(p));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(set_saturation), GINT_TO_POINTER(0));
                          
        frame_b = gtk_frame_new("Saturation");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, 620);

        gtk_widget_show(layout);
        gtk_widget_show_all(window);
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Grayscale") == 0)  
    {
      //copy_bmp("../img/new.bmp","../img/old.bmp");
      if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item))){
        
        grayscale("../img/new.bmp","../img/new.bmp");
        show_image("../img/new.bmp");
      } else {
        
        show_image("../img/old.bmp");
      }
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

/**********************************************************************************************************************************************************************
	Callback to Manipulation functions
**********************************************************************************************************************************************************************/

void set_brightness (GtkWidget* widget, gpointer data)
{
  char *output_path = "../img/new.bmp";
  
  if (GPOINTER_TO_INT(data) == 0){
    copy_bmp("../img/old.bmp","../img/new.bmp");
    show_image("../img/old.bmp");
  }
  if (GPOINTER_TO_INT(data) != 0){
    brightness("../img/new.bmp", output_path, GPOINTER_TO_INT(data));
    show_image(output_path);
  }
}

void set_saturation (GtkWidget* widget, gpointer data)
{
  char *output_path = "../img/new.bmp";
  
  if (GPOINTER_TO_INT(data) == 0){
    copy_bmp("../img/old.bmp","../img/new.bmp");
    show_image("../img/old.bmp");
  }
  if (GPOINTER_TO_INT(data) != 0){
    saturation("../img/new.bmp", output_path, GPOINTER_TO_INT(data));
    show_image(output_path);
  }
}

/**********************************************************************************************************************************************************************
	main()
**********************************************************************************************************************************************************************/

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

  menu_item = gtk_menu_item_new_with_label("Saturation");
  gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  // CheckMenu Grayscale
  menu_item = gtk_check_menu_item_new_with_label("Grayscale");
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu_item), FALSE);
  gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  vbox = gtk_box_new(0,0);
  //button = gtk_button_new_with_label("SAVEBUTTON");
  gtk_box_pack_start(GTK_BOX(vbox), menu_bar,1,0,0);
  //gtk_box_pack_start(GTK_BOX(vbox), button,0,0,0);
  gtk_layout_put(GTK_LAYOUT(layout), vbox, 0, 0);
  

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
} 
