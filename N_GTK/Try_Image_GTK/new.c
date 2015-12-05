# include <gtk/gtk.h>
# include <stdlib.h>
# include <stdio.h>

static GtkWidget* Picture =NULL;
static GtkWidget* image;
void destroy(void) {
  gtk_main_quit();
}

void choose(void) {
  
  Picture =  gtk_image_new_from_file("rees_a");
}




int main (int argc, char** argv) {
  //char *title = argv[1];
  
  GtkWidget* window;  
  // GtkWidget* image;
  
  //GtkWidget *Button;
  GtkWidget *MenuBar;
  GtkWidget *Menu;
  // GtkWidget *label;
  GtkWidget *MenuItem;
  // GtkWidget *VBox;
  GtkWidget *Image_box;
 
  
  gtk_init (&argc, &argv);
  //WINDOW
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  //post Window
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 200,200); 
 
  //image
  Image_box = gtk_vbox_new(FALSE, 5 );
  gtk_container_add(GTK_CONTAINER(window),Image_box);
  image = gtk_image_new_from_file(argv[1]);
  // gtk_box_pack_start(GTK_BOX(Image_box), image,FALSE,TRUE,0);
 
 
  MenuBar = gtk_menu_bar_new();
  Menu = gtk_menu_new();
  
    //////////////////////MENU/////////////////////////  
   
  MenuItem = gtk_menu_item_new_with_label("Choose");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  GTK_SIGNAL_FUNC(choose), NULL);
  
  MenuItem = gtk_menu_item_new_with_label("Analyse");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  // gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  GTK_SIGNAL_FUNC(open), NULL);//appel la detection
  
  
  MenuItem = gtk_menu_item_new_with_label("Leave"); 
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  GTK_SIGNAL_FUNC(destroy), NULL);
  
  ///////////////////////////////////////////////////////


  if(Picture != NULL)
    {image = Picture;}
  
   //ADD Menu
  MenuItem = gtk_menu_item_new_with_label("File");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem), Menu);

  //ADD file top window
  gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), MenuItem);
  
  // Menu au dessu image//
  gtk_box_pack_start(GTK_BOX(Image_box), MenuBar, FALSE, FALSE, 0);  
  gtk_box_pack_start(GTK_BOX(Image_box), image,FALSE,TRUE,0);
    
  gtk_signal_connect(GTK_OBJECT (window), "destroy", GTK_SIGNAL_FUNC (destroy), NULL);
 
  gtk_widget_show_all(window);
  gtk_main();
  //return EXIT_SUCCESS;
  return 0;
}