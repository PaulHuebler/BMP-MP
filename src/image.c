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

          if ((get_width(current_file))+50 >= width) {
            width = (get_width(current_file))+50;
          }

          height = get_height(current_file);

          gtk_window_resize(GTK_WINDOW(window), width, (get_height(current_file))+300);

        }  else {
          if (gtk_dialog_run(GTK_DIALOG(fdialog)) == GTK_RESPONSE_CANCEL) {
            gtk_widget_destroy(fdialog);
          }
        } 
    }/*
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Save as") == 0)
    {
      fdialog = create_filechooser_dialog(current_file, GTK_FILE_CHOOSER_ACTION_SAVE);

      if (gtk_dialog_run(GTK_DIALOG(fdialog)) == GTK_RESPONSE_OK){
        current_file = 
      } else {
        if (gtk_dialog_run(GTK_DIALOG(fdialog)) == GTK_RESPONSE_CANCEL) {
            gtk_widget_destroy(fdialog);
          }
      }
    }*/
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Brightness") == 0)  
    {
      manipulated = false;
        if (current_index < 0){
            printf("No image loaded!\n");
        } else { 
            gtk_widget_destroy(plus_btn);          
            gtk_widget_destroy(minus_btn);            
            gtk_widget_destroy(undo_btn); 
            gtk_widget_destroy(old_color_entry);
            gtk_widget_destroy(new_color_entry);  

            int p = 10;
            int m = -10;
            plus_btn = gtk_button_new_with_label("+10");
            minus_btn = gtk_button_new_with_label("-10");
            undo_btn = gtk_button_new_with_label("UNDO");
            gtk_layout_put(GTK_LAYOUT(layout), minus_btn, 100, height+150);
            gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 200, height+150);
            gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 300, height+150);
            g_signal_connect (G_OBJECT(minus_btn), "clicked", 
                            G_CALLBACK(set_brightness), GINT_TO_POINTER(m));
            g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                            G_CALLBACK(set_brightness), GINT_TO_POINTER(p));
            g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                            G_CALLBACK(undo), NULL);

            gtk_widget_destroy(frame_b);

            frame_b = gtk_frame_new("Brightness");
            gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
            gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);

            gtk_widget_show(layout);
            gtk_widget_show_all(window);
        }
    } 
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Saturation") == 0)  
    {   
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else { 
            gtk_widget_destroy(plus_btn);          
            gtk_widget_destroy(minus_btn);            
            gtk_widget_destroy(undo_btn);  
            gtk_widget_destroy(old_color_entry);
            gtk_widget_destroy(new_color_entry);          
  
            int p = 10;
            int m = -10;
            plus_btn = gtk_button_new_with_label("+10");
            minus_btn = gtk_button_new_with_label("-10");
            undo_btn = gtk_button_new_with_label("UNDO");
            gtk_layout_put(GTK_LAYOUT(layout), minus_btn, 100, height+150);
            gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 200, height+150);
            gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 300, height+150);
            g_signal_connect (G_OBJECT(minus_btn), "clicked", 
                              G_CALLBACK(set_saturation), GINT_TO_POINTER(m));
            g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                              G_CALLBACK(set_saturation), GINT_TO_POINTER(p));
            g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                              G_CALLBACK(undo), NULL);

            gtk_widget_destroy(frame_b);

            frame_b = gtk_frame_new("Saturation");
            gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
            gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);

            gtk_widget_show(layout);
            gtk_widget_show_all(window);
        }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Contrast") == 0)  
    { 
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else {    
        gtk_widget_destroy(plus_btn);          
        gtk_widget_destroy(minus_btn);            
        gtk_widget_destroy(undo_btn); 
        gtk_widget_destroy(old_color_entry);
        gtk_widget_destroy(new_color_entry);

        plus_btn = gtk_button_new_with_label("+10");
        minus_btn = gtk_button_new_with_label("-10");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), minus_btn, 100, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 200, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 300, height+150);
        g_signal_connect (G_OBJECT(minus_btn), "clicked", 
                          G_CALLBACK(set_contrast), GINT_TO_POINTER(-10));
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_contrast), GINT_TO_POINTER(10));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(undo), NULL);

        gtk_widget_destroy(frame_b);

        frame_b = gtk_frame_new("Contrast");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
      }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "exclusive Grayscale") == 0)  
    { 
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else {    
        gtk_widget_destroy(plus_btn);          
        gtk_widget_destroy(minus_btn);            
        gtk_widget_destroy(undo_btn);
        gtk_widget_destroy(old_color_entry);
        gtk_widget_destroy(new_color_entry);

         // old_color_entry used as Tolerance
        old_color_entry = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(old_color_entry), "Tolerance");
        gtk_layout_put(GTK_LAYOUT(layout), old_color_entry, 200, height+150);


        plus_btn = gtk_button_new_with_label("APPLY");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 100, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 100, height+200);
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_exclusive_grayscale), NULL);
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(undo), NULL);

        gtk_widget_destroy(frame_b);

        frame_b = gtk_frame_new("exclusive Grayscale");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
      }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Grayscale") == 0)  
    {
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else {    
        gtk_widget_destroy(plus_btn);          
        gtk_widget_destroy(minus_btn);            
        gtk_widget_destroy(undo_btn); 
        gtk_widget_destroy(old_color_entry);
        gtk_widget_destroy(new_color_entry);


        plus_btn = gtk_button_new_with_label("APPLY");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 100, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 200, height+150);
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_grayscale), NULL);
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(undo), NULL);

        gtk_widget_destroy(frame_b);

        frame_b = gtk_frame_new("Grayscale");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
      }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Floyd Steinberg") == 0)  
    {     
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else {    
        gtk_widget_destroy(plus_btn);          
        gtk_widget_destroy(minus_btn);            
        gtk_widget_destroy(undo_btn); 
        gtk_widget_destroy(old_color_entry);
        gtk_widget_destroy(new_color_entry);

        plus_btn = gtk_button_new_with_label("APPLY");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 100, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 200, height+150);
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_floyd_steinberg), GINT_TO_POINTER(1));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(undo), NULL);

        gtk_widget_destroy(frame_b);

        frame_b = gtk_frame_new("Floyd Steinberg");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
      }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Color Seperation") == 0)  
    {
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else {    
        gtk_widget_destroy(plus_btn);          
        gtk_widget_destroy(minus_btn);            
        gtk_widget_destroy(undo_btn); 
        gtk_widget_destroy(old_color_entry);
        gtk_widget_destroy(new_color_entry);

        plus_btn = gtk_button_new_with_label("APPLY");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 100, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 200, height+150);
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_color_seperation), GINT_TO_POINTER(1));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(undo), NULL);

        gtk_widget_destroy(frame_b);

        frame_b = gtk_frame_new("Color Seperation");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
      }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Invert Colors") == 0)  
    {
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else {    
        gtk_widget_destroy(plus_btn);          
        gtk_widget_destroy(minus_btn);            
        gtk_widget_destroy(undo_btn); 
        gtk_widget_destroy(old_color_entry);
        gtk_widget_destroy(new_color_entry);

        plus_btn = gtk_button_new_with_label("APPLY");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 100, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 200, height+150);
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_invert_colors), GINT_TO_POINTER(1));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(undo), NULL);

        gtk_widget_destroy(frame_b);

        frame_b = gtk_frame_new("Invert Colors");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
      }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Sepia") == 0)  
    {
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else {    
        gtk_widget_destroy(plus_btn);          
        gtk_widget_destroy(minus_btn);            
        gtk_widget_destroy(undo_btn); 
        gtk_widget_destroy(old_color_entry);
        gtk_widget_destroy(new_color_entry);

        plus_btn = gtk_button_new_with_label("APPLY");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 100, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 200, height+150);
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_sepia), GINT_TO_POINTER(1));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(undo), NULL);

        gtk_widget_destroy(frame_b);

        frame_b = gtk_frame_new("Sepia");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
      }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Mirror") == 0)  
    {
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else {    
        gtk_widget_destroy(plus_btn);          
        gtk_widget_destroy(minus_btn);            
        gtk_widget_destroy(undo_btn); 
        gtk_widget_destroy(old_color_entry);
        gtk_widget_destroy(new_color_entry);

        plus_btn = gtk_button_new_with_label("APPLY vertical");
        minus_btn = gtk_button_new_with_label("APPLY horizontal");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 100, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), minus_btn, 100, height+200);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 300, height+150);
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_mirror), GINT_TO_POINTER(1));
        g_signal_connect (G_OBJECT(minus_btn), "clicked", 
                          G_CALLBACK(set_mirror), GINT_TO_POINTER(0));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(undo), NULL);

        gtk_widget_destroy(frame_b);

        frame_b = gtk_frame_new("Mirror Image");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
      }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Gaussian Blur 2D") == 0)  
    {
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else {    
        gtk_widget_destroy(plus_btn);          
        gtk_widget_destroy(minus_btn);            
        gtk_widget_destroy(undo_btn);
        gtk_widget_destroy(old_color_entry);
        gtk_widget_destroy(new_color_entry); 

        plus_btn = gtk_button_new_with_label("APPLY");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 100, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 200, height+150);
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_gaussian_blur2D), GINT_TO_POINTER(1));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(undo), NULL);

        gtk_widget_destroy(frame_b);

        frame_b = gtk_frame_new("Gaussian Blur 2D");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
      }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Temperature") == 0)  
    { 
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else {    
        gtk_widget_destroy(plus_btn);          
        gtk_widget_destroy(minus_btn);            
        gtk_widget_destroy(undo_btn); 
        gtk_widget_destroy(old_color_entry);
        gtk_widget_destroy(new_color_entry);

        plus_btn = gtk_button_new_with_label("+10");
        minus_btn = gtk_button_new_with_label("-10");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), minus_btn, 100, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 200, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 300, height+150);
        g_signal_connect (G_OBJECT(minus_btn), "clicked", 
                          G_CALLBACK(set_temperature), GINT_TO_POINTER(-10));
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_temperature), GINT_TO_POINTER(10));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(undo), NULL);

        gtk_widget_destroy(frame_b);

        frame_b = gtk_frame_new("Temperature");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
      }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Color Swap") == 0)  
    { 
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else {    
        gtk_widget_destroy(plus_btn);          
        gtk_widget_destroy(minus_btn);            
        gtk_widget_destroy(undo_btn);
        gtk_widget_destroy(old_color_entry);
        gtk_widget_destroy(new_color_entry);
        
        old_color_entry = gtk_entry_new();
        new_color_entry = gtk_entry_new();
        plus_btn = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(old_color_entry), "old color");
        gtk_entry_set_placeholder_text(GTK_ENTRY(new_color_entry), "new color");
        gtk_entry_set_placeholder_text(GTK_ENTRY(plus_btn), "Tolerance");
        gtk_layout_put(GTK_LAYOUT(layout), old_color_entry, 400, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), new_color_entry, 600, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 200, height+150);


        minus_btn = gtk_button_new_with_label("Apply");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), minus_btn, 100, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 100, height+200);
        g_signal_connect (G_OBJECT(minus_btn), "clicked", 
                          G_CALLBACK(set_color_swap), NULL);
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(undo), NULL);

        gtk_widget_destroy(frame_b);

        frame_b = gtk_frame_new("Color Swap\t\t\t\t\t\t\t\t\t\told color:\t\t\t\t\tnew color:\t\t\t\t");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
      }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Sobel Edge Detection") == 0)  
    {
      manipulated = false;
      if (current_index < 0){
          printf("No image loaded!\n");
      } else {    
        gtk_widget_destroy(plus_btn);          
        gtk_widget_destroy(minus_btn);            
        gtk_widget_destroy(undo_btn); 
        gtk_widget_destroy(old_color_entry);
        gtk_widget_destroy(new_color_entry);

        plus_btn = gtk_button_new_with_label("APPLY");
        undo_btn = gtk_button_new_with_label("UNDO");
        gtk_layout_put(GTK_LAYOUT(layout), plus_btn, 100, height+150);
        gtk_layout_put(GTK_LAYOUT(layout), undo_btn, 200, height+150);
        g_signal_connect (G_OBJECT(plus_btn), "clicked", 
                          G_CALLBACK(set_sobel_edge_detection), GINT_TO_POINTER(1));
        g_signal_connect (G_OBJECT(undo_btn), "clicked", 
                          G_CALLBACK(undo), NULL);

        gtk_widget_destroy(frame_b);

        frame_b = gtk_frame_new("Sobel Edge Detection");
        gtk_frame_set_shadow_type(GTK_FRAME(frame_b), GTK_SHADOW_OUT);
        gtk_layout_put(GTK_LAYOUT(layout), frame_b, 80, height+110);
        gtk_widget_show(layout);
        gtk_widget_show_all(window);
      }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Exit") == 0)  
    {
        gtk_main_quit(); //quit the application
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "About") == 0)
    {
        g_print("You pressed About\nGoing to open: https://github.com/PaulHuebler/BMP-MP\n");
	      gtk_show_uri_on_window(NULL, "https://github.com/PaulHuebler/BMP-MP", GDK_CURRENT_TIME, 0);
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

    break;
  }

  return fdialog;
}

void show_image (char *file_path)
{
  printf("\n\n\nShowImage:\n%s\n%d\n\n\n\n\n",current_file, current_index);

  gtk_widget_destroy(image);

  // show image
  image = gtk_image_new_from_file (file_path);

  gtk_layout_put(GTK_LAYOUT(layout), image, 20, 80);

  gtk_widget_show(layout);
  gtk_widget_show_all(window);
}

/************************************^**********************************************************************************************************************************
	UNDO / SAVE
**********************************************************************************************************************************************************************/

void save () 
{
  copy_bmp(current_file, "../img/new.bmp");
  copy_bmp(current_file, "../img/old.bmp");
  current_file = "../img/old.bmp";
}

void undo ()
{ 
  copy_bmp("../img/old.bmp", "../img/new.bmp");
  current_file = "../img/old.bmp";
  show_image("../img/old.bmp");
  current_float_value = 1.0;
  current_int_value = 0;
}

/************************************^**********************************************************************************************************************************
	Callback to Manipulation functions
**********************************************************************************************************************************************************************/

void set_brightness (GtkWidget* widget, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  int value = GPOINTER_TO_INT(data);
  brightness(current_file, "../img/new.bmp", value);
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
void set_saturation (GtkWidget* widget, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  int value = GPOINTER_TO_INT(data);
  saturation(current_file, "../img/new.bmp", value);
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
} 
void set_contrast (GtkWidget* widget, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  int value = GPOINTER_TO_INT(data);
  //current_float_value = ((current_float_value) + (value/100.0f));
  contrast(current_file, "../img/new.bmp", value);
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
void set_exclusive_grayscale (GtkWidget* widget, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  const gchar *tolerance = gtk_entry_get_text (GTK_ENTRY(old_color_entry));
  int value = atoi(tolerance);  
  exclusive_grayscale(current_file, "../img/new.bmp", value);
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
void set_grayscale (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  grayscale(current_file, "../img/new.bmp");
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
void set_floyd_steinberg (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  floyd_steinberg(current_file, "../img/new.bmp");
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
void set_color_seperation (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  color_seperation(current_file, "../img/new.bmp");
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
void set_invert_colors (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  invert_colors(current_file, "../img/new.bmp");
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
void set_sepia (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  sepia(current_file, "../img/new.bmp");
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
void set_mirror (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  int value = GPOINTER_TO_INT(data);
  if (value == 1){
    mirror_vert(current_file, "../img/new.bmp");
  } else {
    mirror_hor(current_file, "../img/new.bmp");
  }
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
void set_gaussian_blur2D (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  gaussian_blur2D(current_file, "../img/new.bmp");
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
void set_temperature (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  int value = GPOINTER_TO_INT(data);
  //current_float_value = ((current_float_value) + (value/100.0f));
  temperature(current_file, "../img/new.bmp", value);
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
void set_color_swap (GtkWidget* widget, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  const gchar *num_old = gtk_entry_get_text (GTK_ENTRY(old_color_entry));
  old_color = atoi(num_old);
  const gchar *num_new = gtk_entry_get_text (GTK_ENTRY(new_color_entry));
  new_color = atoi(num_new);
  const gchar *tolerance = gtk_entry_get_text (GTK_ENTRY(plus_btn));
  int value = atoi(tolerance);
  colorswap(current_file, "../img/new.bmp", old_color, new_color, value);
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
void set_sobel_edge_detection (GtkWidget* menu_item, gpointer data)
{
  if (manipulated == false){
    save();
    manipulated = true;
  }
  sobel_edge_detection(current_file, "../img/new.bmp");
  current_file = "../img/new.bmp";
  show_image("../img/new.bmp");
}
/**********************************************************************************************************************************************************************
	main()
**********************************************************************************************************************************************************************/

int main (int    argc, char **argv)
{
  GtkWidget *menu_bar, *menu_item, *file_menu, *help_menu, *save_button, *undo_button, *redo_button,
            *corrections_menu, *effects_menu, *transform_menu, *image;

  gtk_init(&argc, &argv);

// Create Window:
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "BMP-MP");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  
// layoutcontainer 
  layout = gtk_layout_new(NULL, NULL);                                         
  gtk_container_add(GTK_CONTAINER (window), layout);
  gtk_widget_show(layout);

// Menubar: 
  menu_bar = gtk_menu_bar_new();

  file_menu = gtk_menu_new();
  corrections_menu = gtk_menu_new();
  effects_menu = gtk_menu_new();
  transform_menu = gtk_menu_new();
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
  /*
  menu_item = gtk_menu_item_new_with_label("Save as");
  gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);
  */
  menu_item = gtk_menu_item_new_with_label("Exit");
  gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);
 
  menu_item = gtk_menu_item_new_with_label("About");
  gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Corrections");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), corrections_menu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

  menu_item = gtk_menu_item_new_with_label("Effects");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), effects_menu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

  menu_item = gtk_menu_item_new_with_label("Transformations");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), transform_menu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

  menu_item = gtk_menu_item_new_with_label("Brightness");
  gtk_menu_shell_append(GTK_MENU_SHELL(corrections_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Saturation");
  gtk_menu_shell_append(GTK_MENU_SHELL(corrections_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);
  
  menu_item = gtk_menu_item_new_with_label("Contrast");
  gtk_menu_shell_append(GTK_MENU_SHELL(corrections_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("exclusive Grayscale");
  gtk_menu_shell_append(GTK_MENU_SHELL(effects_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Grayscale");
  gtk_menu_shell_append(GTK_MENU_SHELL(effects_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Floyd Steinberg");
  gtk_menu_shell_append(GTK_MENU_SHELL(effects_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Color Seperation");
  gtk_menu_shell_append(GTK_MENU_SHELL(effects_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Invert Colors");
  gtk_menu_shell_append(GTK_MENU_SHELL(effects_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Sepia");
  gtk_menu_shell_append(GTK_MENU_SHELL(effects_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Mirror");
  gtk_menu_shell_append(GTK_MENU_SHELL(transform_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Gaussian Blur 2D");
  gtk_menu_shell_append(GTK_MENU_SHELL(effects_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Temperature");
  gtk_menu_shell_append(GTK_MENU_SHELL(corrections_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Color Swap");
  gtk_menu_shell_append(GTK_MENU_SHELL(corrections_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

  menu_item = gtk_menu_item_new_with_label("Sobel Edge Detection");
  gtk_menu_shell_append(GTK_MENU_SHELL(effects_menu), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);


  vbox = gtk_box_new(0,0);
  gtk_box_pack_start(GTK_BOX(vbox), menu_bar,1,0,0);
  
  save_button = gtk_button_new_with_label("SAVE");
  
  gtk_box_pack_start(GTK_BOX(vbox), save_button,10,0,0);
  gtk_layout_put(GTK_LAYOUT(layout), vbox, 0, 0);
  
  g_signal_connect(G_OBJECT(save_button), "clicked", G_CALLBACK(save), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
} 
