#include <gtk/gtk.h>


/*
GdkPixbuf *create_pixbuf(const gchar * filename) {
    
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   
   if (!pixbuf) {
       
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
} */


int main (int    argc, char **argv)
{
  GtkWidget *window;
  //GdkPixbuf *image;
  GtkWidget *layout;
  GtkWidget *image;
  GtkWidget *vbox;

  GtkWidget *menubar;
  GtkWidget *fileMenu;
  GtkWidget *fileMi;
  GtkWidget *quitMi;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "BMP-MP");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  

  layout = gtk_layout_new(NULL, NULL);                                         // layoutcontainer for image
  gtk_container_add(GTK_CONTAINER (window), layout);
  gtk_widget_show(layout);

  image = gtk_image_new_from_file("sails.bmp");
  gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

  //gtk_window_set_icon(GTK_WINDOW(window), image);


  vbox = gtk_vbox_new(FALSE, 0);                                                // Menubar
  gtk_container_add(GTK_CONTAINER(window), vbox);

  menubar = gtk_menu_bar_new();
  fileMenu = gtk_menu_new();

  fileMi = gtk_menu_item_new_with_label("File");
  quitMi = gtk_menu_item_new_with_label("Quit");

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

  g_signal_connect(G_OBJECT(quitMi), "activate",
        G_CALLBACK(gtk_main_quit), NULL);
  
  gtk_widget_show(window);

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
} 