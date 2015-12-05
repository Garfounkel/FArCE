# include <gtk/gtk.h>
# include <stdlib.h>
# include <stdio.h>

//# include "test.h"


typedef struct Screen Screen;
struct Screen
{
 GtkWidget* Window; 
 GtkWidget* image;
  
};

  
void destroy(void) {
   gtk_main_quit();
}

void Navigate(void) {

  GtkWidget *filew;
   /* Création d'un widget de sélection de fichier. */
 
    filew = gtk_file_selection_new ("File selection");
     
    gtk_signal_connect (GTK_OBJECT (filew), "destroy",
                        (GtkSignalFunc) destroy, &filew);
 
    /* Connexion de ok_button à la fonction file_ok_sel() */
 
    gtk_signal_connect (GTK_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
                        "clicked", (GtkSignalFunc) choose, filew );
    
    /* Connexion de cancel_button pour détruire le widget */
 
    gtk_signal_connect_object (GTK_OBJECT (GTK_FILE_SELECTION (filew)->cancel_button),
                               "clicked", (GtkSignalFunc) gtk_widget_destroy,
                               GTK_OBJECT (filew));
    
    /* Configuration du nom de fichier, comme s'il s'agissait d'un dialogue de
     * sauvegarde et que nous donnions un nom de fichier par défaut. */
 
   /*gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew), 
      "penguin.png");*/
}

void supp(void) {
    gtk_main_quit();
}

static void choose(GtkWidget *button,GtkImage  *image) {
 
  static gboolean state = TRUE;

   if( state )
      gtk_image_set_from_file( image,"renaud_e");
   else
      gtk_image_set_from_file( image,"daumal_l");

   state = ! state;
}


Screen* init_screen(GtkWidget* title)
{
  Screen *screen=malloc(sizeof(struct Screen));
  screen->image = title;
  screen->Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  return screen;
  
}

int main (int argc, char** argv) {   
 
  GtkWidget *MenuBar;
  GtkWidget *Menu;
  
  GtkWidget *MenuItem;
 
  GtkWidget *Image_box;
   
  gtk_init (&argc, &argv);
  
 
  
  ////////////// WINDOW/////////////////
  // window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
  Screen *scre = init_screen(gtk_image_new_from_file(argv[1]));
  
  ////////////post Window/////////////////
  gtk_window_set_position(GTK_WINDOW(scre->Window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(scre->Window), 320,200); 
 
  //image
  Image_box = gtk_vbox_new(FALSE, 0 );
  gtk_container_add(GTK_CONTAINER(scre->Window),Image_box);
 

 
  MenuBar = gtk_menu_bar_new();
  Menu = gtk_menu_new();
  
    //////////////////////MENU/////////////////////////  
   
  MenuItem = gtk_menu_item_new_with_label("Choose");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate", G_CALLBACK(choose), GTK_IMAGE(scre->image));  


    
  MenuItem = gtk_menu_item_new_with_label("Navigate");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  /*GTK_SIGNAL_FUNC(Navigate)*/(GtkSignalFunc)Navigate, NULL);

    
  MenuItem = gtk_menu_item_new_with_label("Supp");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  GTK_SIGNAL_FUNC(choose), NULL);
  
  
  MenuItem = gtk_menu_item_new_with_label("Analyse");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  // gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  GTK_SIGNAL_FUNC(open), NULL);//appel la detection
  
  
  MenuItem = gtk_menu_item_new_with_label("Leave"); 
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  GTK_SIGNAL_FUNC(destroy), NULL);
  
  ///////////////////////////////////////////////////////
  
  
   //ADD Menu
  MenuItem = gtk_menu_item_new_with_label("File");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem), Menu);

  //ADD file top window
  gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), MenuItem);
  
  // Menu au dessu image//
  // gtk_box_pack_start(GTK_BOX(Image_box), MenuBar, FALSE, FALSE, 0);  
  gtk_box_pack_start(GTK_BOX(Image_box),scre->image,TRUE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(Image_box), MenuBar, FALSE, FALSE, 0);  

  gtk_signal_connect(GTK_OBJECT (scre->Window), "destroy", GTK_SIGNAL_FUNC (destroy), NULL);
 
  gtk_widget_show_all(scre->Window);
  gtk_main();
  
  //return EXIT_SUCCESS;
  return 0;
}
