#define _GNU_SOURCE

#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/bitmap.h"
#include "../include/manipulations.h"
#include "../include/window.h"

/**********************************************************************************************************************************************************************
	Menubar/ show_image()/ filechooser 
**********************************************************************************************************************************************************************/

static void menu_response(GtkWidget* menu_item, gpointer data)
{
    GtkWidget *fdialog = NULL;

    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Open") == 0)   
    {
        fdialog = create_filechooser_dialog(original_file, GTK_FILE_CHOOSER_ACTION_OPEN);
        if (gtk_dialog_run(GTK_DIALOG(fdialog)) == GTK_RESPONSE_OK) {
          original_file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fdialog));
          g_print("%s\n", original_file);
          gtk_widget_destroy(fdialog);
          current_index = 0;
          current_file = original_file;
          show_image(current_file);
        }
/* TODO Bugfix: Cancel -> Window schleißen 
        if (gtk_dialog_run(GTK_DIALOG(fdialog)) == GTK_RESPONSE_CANCEL) {
          gtk_widget_destroy(GTK_WIDGET(fdialog));
        }
        */
           
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Brightness") == 0)  
    {
        if (IsDirty == false){
          save ("");
        } else {
          save ("temp");
        }
        if (current_index < 0){
            printf("No image loaded!\n");
        } else {
            

            GtkWidget *plus_btn, *minus_btn, *undo_btn;
            GtkWidget *frame_b;
            int p = 10;
            int m = -10;

            plus_btn = gtk_button_new_with_label("+10");
            minus_btn = gtk_button_new_with_label("-10");
            //undo_btn = gtk_button_new_with_label("UNDO");
            gtk_layout_put(GTK_LAYOUT(layout), minus_btn, 100, 680);
            gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 200, 680);
            //gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 300, 680);
            g_signal_connect (G_OBJECT(minus_btn), "clicked", 
                            G_CALLBACK(set_brightness), GINT_TO_POINTER(m));
            g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                            G_CALLBACK(set_brightness), GINT_TO_POINTER(p));
            /*g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                            G_CALLBACK(set_brightness), GINT_TO_POINTER(0));*/
                            
            frame_b = gtk_frame_new("Brightness");
            gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
            gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, 620);

            gtk_widget_show(layout);
            gtk_widget_show_all(window);
        }
    } 
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Saturation") == 0)  
    {   
        if (IsDirty == false){
          save ("");
        } else {
          save ("temp");
        }
        if (current_index < 0){
            printf("No image loaded!\n");
        } else {  
           

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
                              G_CALLBACK(undo), NULL);
                              
            frame_b = gtk_frame_new("Saturation");
            gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
            gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, 620);
            gtk_widget_show(layout);
            gtk_widget_show_all(window);
        }
    }/*
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Contrast") == 0)  
    {   
        if (manipulated == false){
          copy_bmp(file_name, "../img/old.bmp");        // backup of the original
          copy_bmp(file_name, "../img/new.bmp");
          manipulated = true;
        } else {
          copy_bmp("../img/new.bmp","../img/old.bmp");
        }     
        
        GtkWidget *plus_btn, *minus_btn, *undo_btn;
        GtkWidget *frame_b;
        plus_btn = gtk_button_new_with_label("+10");
        minus_btn = gtk_button_new_with_label("-10");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), minus_btn, 100, 680);
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 200, 680);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 300, 680);
        g_signal_connect (G_OBJECT(minus_btn), "clicked", 
                          G_CALLBACK(set_contrast), GINT_TO_POINTER(-5));
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_contrast), GINT_TO_POINTER(5));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(set_contrast), GINT_TO_POINTER(0));
                          
        frame_b = gtk_frame_new("Contrast");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, 620);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Grayscale") == 0)  
    {
        if (manipulated == false){
          copy_bmp(file_name, "../img/old.bmp");        // backup of the original
          copy_bmp(file_name, "../img/new.bmp");
          manipulated = true;
        } else {
          copy_bmp("../img/new.bmp","../img/old.bmp");
        }  
        if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item))){
          grayscale("../img/old.bmp","../img/new.bmp");
          show_image("../img/new.bmp");
        } else {
          show_image("../img/old.bmp");
        }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "exclusive Grayscale") == 0)  
    {   
        if (manipulated == false){
          copy_bmp(file_name, "../img/old.bmp");        // backup of the original
          copy_bmp(file_name, "../img/new.bmp");
          manipulated = true;
        } else {
          copy_bmp("../img/new.bmp","../img/old.bmp");
        }     
        g_print("You pressed exclusive Grayscale\n");
        
        GtkWidget *plus_btn, *minus_btn, *undo_btn;
        GtkWidget *frame_b;
        plus_btn = gtk_button_new_with_label("+10");
        minus_btn = gtk_button_new_with_label("-10");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), minus_btn, 100, 680);
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 200, 680);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 300, 680);
        g_signal_connect (G_OBJECT(minus_btn), "clicked", 
                          G_CALLBACK(set_exclusive_grayscale), GINT_TO_POINTER(-10));
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_exclusive_grayscale), GINT_TO_POINTER(10));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(set_exclusive_grayscale), GINT_TO_POINTER(0));
                          
        frame_b = gtk_frame_new("exclusive Grayscale");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, 620);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
    }*/
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Exit") == 0)  
    {
        gtk_main_quit(); //quit the application
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "About") == 0)
    {
        g_print("You pressed About\n");
    } 
}

GtkWidget * create_filechooser_dialog (char *init_path, GtkFileChooserAction action)
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

static void show_image (char *file_path)
{
  GtkWidget *image;
  
  // show image
  image = gtk_image_new_from_file (file_path);
  gtk_layout_put(GTK_LAYOUT(layout), image, 20, 80);

  gtk_widget_show(layout);
  gtk_widget_show_all(window);

}

/************************************^**********************************************************************************************************************************
	UNDO / REDO / SAVE
**********************************************************************************************************************************************************************/
char * index_path (int index_i)
{
    static char path[256] = "";
    char *index_string;

    asprintf(&index_string, "%d", index_i);
    memccpy(memccpy(memccpy(path, "../img/", '\0', 256) -1, index_string, '\0', 256) -1, ".bmp", '\0', 256);

    return (char*)path;
}

void save (char *temp)
{
  if (temp == "temp"){

    printf ("\n\n\n\nSAVING CURRENT IMAGE %d\n\n\n\n\n\n", current_index);
    copy_bmp(current_file, index_path(current_index));
  } else {

    copy_bmp(current_file, index_path(current_index));
    current_index++;
  }  
}

void undo ()
{ 
  
}

void redo ()
{

}

/************************************^**********************************************************************************************************************************
	Callback to Manipulation functions
**********************************************************************************************************************************************************************/

void set_brightness (GtkWidget* widget, gpointer data)
{
  IsDirty = true;
  int value = GPOINTER_TO_INT(data);
  brightness(current_file, current_file, value); // 
  
  show_image(current_file);
}

void set_saturation (GtkWidget* widget, gpointer data)
{
  IsDirty = true;
  int value = GPOINTER_TO_INT(data);
  saturation(current_file, current_file, value);
  show_image(current_file);
} /*
void set_contrast (GtkWidget* widget, gpointer data)
{
  char *output_path = "../img/new.bmp";
  int i = GPOINTER_TO_INT(data);
  current_float_value = ((current_float_value) + (i/100.0f));
  if (GPOINTER_TO_INT(data) == 0){                                              // UNDO
    current_float_value = 1.0;
    copy_bmp("../img/old.bmp","../img/new.bmp");
    show_image("../img/old.bmp");
  } else {
    
    contrast("../img/new.bmp", output_path, current_float_value);
    show_image(output_path);
  }
}
void set_exclusive_grayscale (GtkWidget* widget, gpointer data)
{
  char *output_path = "../img/new.bmp";
  int i = GPOINTER_TO_INT(data);
  current_int_value = (current_int_value + i);
  g_print("\n\n\n%d\n\n\n", current_int_value);
  if (GPOINTER_TO_INT(data) == 0){                         // UNDO-action
    current_int_value = 0;
    copy_bmp("../img/old.bmp","../img/new.bmp");
    show_image("../img/old.bmp");
  } else {
    
    exclusive_grayscale("../img/new.bmp", output_path, 0);
    show_image(output_path);
  }
}
void set_grayscale (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == 0){
      copy_bmp(file_name, "../img/old.bmp");                                    // backup of the original
      copy_bmp(file_name, "../img/new.bmp");
      manipulated = 1;
  } else {
      copy_bmp("../img/new.bmp","../img/old.bmp");
  }  
  if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item)) == TRUE){
      grayscale("../img/old.bmp","../img/new.bmp");
      show_image("../img/new.bmp");
  } else {
      g_print("\n\n\n\n Halllo \n\n\n\n\n\n");
      show_image("../img/old.bmp");
  }
}
void set_floyd_steinberg (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == 0){
      copy_bmp(file_name, "../img/old.bmp");                                    // backup of the original
      copy_bmp(file_name, "../img/new.bmp");
      manipulated = 1;
  } else {
      //manipulated = ;
      //copy_bmp("../img/new.bmp","../img/old.bmp");
  }  
  if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item)) == TRUE){
      floyd_steinberg("../img/old.bmp","../img/new.bmp");
      show_image("../img/new.bmp");
  } else {
      g_print("\n\n\n\n Halllo \n\n\n\n\n\n");
      show_image("../img/old.bmp");
  }
}
void set_color_seperation (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == 0){
      copy_bmp(file_name, "../img/old.bmp");                                    // backup of the original
      copy_bmp(file_name, "../img/new.bmp");
      manipulated = 1;
  } else {
      //copy_bmp("../img/new.bmp","../img/old.bmp");
  }  
  if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item)) == TRUE){
      color_seperation("../img/old.bmp","../img/new.bmp");
      show_image("../img/new.bmp");
  } else {
      g_print("\n\n\n\n Test \n\n\n\n\n\n");
      show_image("../img/old.bmp");
  }
}
void set_invert_colors (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == 0){
      copy_bmp(file_name, "../img/old.bmp");                                    // backup of the original
      copy_bmp(file_name, "../img/new.bmp");
      manipulated = 1;
  } else {
      //manipulated = ;
      //copy_bmp("../img/new.bmp","../img/old.bmp");
  }  
  if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item)) == TRUE){
      invert_colors("../img/old.bmp","../img/new.bmp");
      show_image("../img/new.bmp");
  } else {
      g_print("\n\n\n\n Test \n\n\n\n\n\n");
      show_image("../img/old.bmp");
  }
}
void set_sepia (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == 0){
      copy_bmp(file_name, "../img/old.bmp");                                    // backup of the original
      copy_bmp(file_name, "../img/new.bmp");
      manipulated = 1;
  } else {
      //manipulated = ;
      //copy_bmp("../img/new.bmp","../img/old.bmp");
  }  
  if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item)) == TRUE){
      sepia("../img/old.bmp","../img/new.bmp");
      show_image("../img/new.bmp");
  } else {
      g_print("\n\n\n\n Test \n\n\n\n\n\n");
      show_image("../img/old.bmp");
  }
}
void set_mirror_vert (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == 0){
      copy_bmp(file_name, "../img/old.bmp");                                    // backup of the original
      copy_bmp(file_name, "../img/new.bmp");
      manipulated = 1;
  } else {
      //manipulated = ;
      //copy_bmp("../img/new.bmp","../img/old.bmp");
  }  
  if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item)) == TRUE){
      mirror_vert("../img/old.bmp","../img/new.bmp");
      show_image("../img/new.bmp");
  } else {
      g_print("\n\n\n\n Test \n\n\n\n\n\n");
      show_image("../img/old.bmp");
  }
}
void set_mirror_hor (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == 0){
      copy_bmp(file_name, "../img/old.bmp");                                    // backup of the original
      copy_bmp(file_name, "../img/new.bmp");
      manipulated = 1;
  } else {
      //manipulated = ;
      //copy_bmp("../img/new.bmp","../img/old.bmp");
  }  
  if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item)) == TRUE){
      mirror_hor("../img/old.bmp","../img/new.bmp");
      show_image("../img/new.bmp");
  } else {
      g_print("\n\n\n\n Test \n\n\n\n\n\n");
      show_image("../img/old.bmp");
  }
}
*/
/**********************************************************************************************************************************************************************
	main()
**********************************************************************************************************************************************************************/

int main (int    argc, char **argv)
{
  GtkWidget *menu_bar, *menu_item, *file_menu, *help_menu, *vbox, *save_button, *undo_button, *redo_button,
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
  /*
  menu_item = gtk_menu_item_new_with_label("Contrast");
  gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("exclusive Grayscale");
  gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

// CheckMenuItems
  menu_item = gtk_check_menu_item_new_with_label("Grayscale");
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu_item), FALSE);
  gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), menu_item);
  g_signal_connect(menu_item, "toggle", G_CALLBACK(set_grayscale), NULL);

  menu_item = gtk_check_menu_item_new_with_mnemonic("Floyd Steinberg");
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu_item), FALSE);
  gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(set_floyd_steinberg), NULL);

  menu_item = gtk_check_menu_item_new_with_mnemonic("Color Seperation");
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu_item), FALSE);
  gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(set_color_seperation), NULL);

  menu_item = gtk_check_menu_item_new_with_mnemonic("Invert Colors");
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu_item), FALSE);
  gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(set_invert_colors), NULL);
  menu_item = gtk_check_menu_item_new_with_mnemonic("Sepia");
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu_item), FALSE);
  gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(set_sepia), NULL);
  menu_item = gtk_check_menu_item_new_with_mnemonic("Mirror (vertical)");
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu_item), FALSE);
  gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(set_mirror_vert), NULL);
  menu_item = gtk_check_menu_item_new_with_mnemonic("Mirror (horizontal)");
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu_item), FALSE);
  gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(set_mirror_hor), NULL);
*/


  vbox = gtk_box_new(0,0);
  gtk_box_pack_start(GTK_BOX(vbox), menu_bar,1,0,0);
  
  undo_button = gtk_button_new_with_label("UNDO");
  redo_button = gtk_button_new_with_label("REDO");
  save_button = gtk_button_new_with_label("SAVE");
  
  gtk_box_pack_start(GTK_BOX(vbox), undo_button,0,0,0);
  gtk_box_pack_start(GTK_BOX(vbox), redo_button,10,0,0);
  gtk_box_pack_start(GTK_BOX(vbox), save_button,20,0,0);
  gtk_layout_put(GTK_LAYOUT(layout), vbox, 0, 0);
  
  g_signal_connect(G_OBJECT(undo_button), "clicked", G_CALLBACK(undo), NULL);
  g_signal_connect(G_OBJECT(redo_button), "clicked", G_CALLBACK(redo), NULL);
  g_signal_connect(G_OBJECT(save_button), "clicked", G_CALLBACK(save), NULL);


  gtk_widget_show_all(window);

  gtk_main();

  return 0;
} 
