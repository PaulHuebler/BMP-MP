#include <gtk/gtk.h>
#include <stdio.h>

GtkWidget * create_filechooser_dialog(char *init_path, GtkFileChooserAction action);

static void menu_response(GtkWidget* menu_item, gpointer data)
{
    GtkWidget *fdialog;
    char *fname = "";

    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Open") == 0)   
    {
        g_print("You pressed Open\n");
        fdialog = create_filechooser_dialog(fname, GTK_FILE_CHOOSER_ACTION_OPEN);
        if (gtk_dialog_run(GTK_DIALOG(fdialog)) == GTK_RESPONSE_OK) {
          fname = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fdialog));
          printf(fname); }
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

GtkWidget *
create_filechooser_dialog(char *init_path, GtkFileChooserAction action)
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

    case GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER:
    case GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER:
      break;
  }

  return fdialog;
}


int main (int    argc, char **argv)
{
  GtkWidget *window;
  GtkWidget *layout;
  GtkWidget *image;
  GtkWidget *menu_bar, *menu_item, *file_menu, *help_menu, *vbox, *button;
  char *file_name = "";

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

  vbox = gtk_box_new(0,0);
  //button = gtk_button_new_with_label("This is a Button");
  gtk_box_pack_start(GTK_BOX(vbox), menu_bar,1,0,0);
  //gtk_box_pack_start(GTK_BOX(vbox), button,0,0,0);
 
  gtk_layout_put(GTK_LAYOUT(layout), vbox, 0, 0);
  
// show image
  image = gtk_image_new_from_file (file_name);
  gtk_layout_put(GTK_LAYOUT(layout), image, 20, 80);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
} 
