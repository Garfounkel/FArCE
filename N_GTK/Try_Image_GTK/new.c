# include <gtk/gtk.h>
# include <stdlib.h>
# include <stdio.h>



typedef struct Screen Screen;
struct Screen
{
 GtkWidget* Window; 
 GtkWidget* image;
  
};

  
void Destroy(void) {
   gtk_main_quit();
}


void supp(void) {
    gtk_main_quit();
}
///////swap image////////////
static void choose(GtkWidget *button,GtkImage  *image) {
 
  static gboolean state = TRUE;

   if( state )
      gtk_image_set_from_file( image,"renaud_e");
   else
      gtk_image_set_from_file( image,"daumal_l");

   state = ! state;

   
}

void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection)
{
    const gchar* chemin;
    GtkWidget *dialog;
    chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection) );
     
    dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection),
    GTK_DIALOG_MODAL,
    GTK_MESSAGE_INFO,
    GTK_BUTTONS_OK,
    "Vous avez choisi :\n%s", chemin);
     
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    gtk_widget_destroy(file_selection);
}

void Navigate(){
   GtkWidget *selection;
     
    selection = gtk_file_selection_new( g_locale_to_utf8( "Sélectionnez un fichier", -1, NULL, NULL, NULL) );
    gtk_widget_show(selection);
     
    //On interdit l'utilisation des autres fenêtres.
    gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
     
    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked",
		     G_CALLBACK(recuperer_chemin), selection );
     
    g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked",
		     G_CALLBACK(gtk_widget_destroy), selection);
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
  GtkWidget *StatusBar;
  GtkWidget *MenuItem;
  GtkWidget *Image_box;
   
  gtk_init (&argc, &argv);
   
  ////////////// WINDOW/////////////////
  
  // window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
  Screen *scre = init_screen(gtk_image_new_from_file(argv[1]));
  
  ////////////post Window/////////////////
  gtk_window_set_position(GTK_WINDOW(scre->Window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(scre->Window), 320,200); 

  //  button = gtk_button_new_with_mnemonic("_gggg");
   //  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Navigate),NULL);
  
  /////////////image/////////////
  Image_box = gtk_vbox_new(FALSE, 0 );
  gtk_container_add(GTK_CONTAINER(scre->Window),Image_box);
  //////Photo title
  StatusBar = gtk_statusbar_new();
  gtk_statusbar_push (GTK_STATUSBAR (StatusBar), 0,"NONO");
    
  MenuBar = gtk_menu_bar_new();
  Menu = gtk_menu_new();

    //////////////////////MENU/////////////////////////  
   
  MenuItem = gtk_menu_item_new_with_label("Choose");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate", G_CALLBACK(choose), GTK_IMAGE(scre->image));  
    
   MenuItem =gtk_menu_item_new_with_mnemonic (("_Add Pictures"));
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",G_CALLBACK(Navigate),NULL);

    
  MenuItem = gtk_menu_item_new_with_label("Supp");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  GTK_SIGNAL_FUNC(choose), NULL);
  
  
  MenuItem = gtk_menu_item_new_with_label("Analyse");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  // gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  GTK_SIGNAL_FUNC(open), NULL);//appel la detection
  
  
  MenuItem = gtk_menu_item_new_with_label("Leave"); 
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  GTK_SIGNAL_FUNC(Destroy), NULL);
  
  ///////////////////////////////////////////////////////
     
  
   //ADD Menu
  MenuItem = gtk_menu_item_new_with_label("File");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem), Menu);

  //ADD file top window
  gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), MenuItem);
  
  // Menu au dessus image//
  gtk_box_pack_start(GTK_BOX(Image_box), MenuBar, FALSE, FALSE, 0);  gtk_box_pack_start(GTK_BOX(Image_box),scre->image,TRUE,FALSE,0);
  gtk_box_pack_end(GTK_BOX(Image_box), StatusBar, FALSE, FALSE, 0);

  gtk_signal_connect(GTK_OBJECT (scre->Window), "destroy", GTK_SIGNAL_FUNC (Destroy), NULL);
 
  gtk_widget_show_all(scre->Window);
  gtk_main();
  
  //return EXIT_SUCCESS;
  return 0;
}
