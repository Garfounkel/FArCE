# include <gtk/gtk.h>
# include <stdlib.h>
# include <stdio.h>

static GtkWidget* Picture =NULL;
static GtkWidget* image;


typedef struct Screen Screen;
struct Screen
{
 GtkWidget* Window; 
 GtkWidget* image; 
};

  
void destroy(void) {
  gtk_main_quit();
}

void save(void) {
  gtk_main_quit();
}

void supp(void) {
  gtk_main_quit();
}

GtkWidget* choose(void) {

  Picture =  gtk_image_new_from_file("rees_a");  
  return Picture;
}


Screen* init_screen(GtkWidget* title)
{
  Screen *screen=malloc(sizeof(struct Screen));
  screen->image = title;
  screen->Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  return screen;
  
}

int main (int argc, char** argv) {   
  // GtkWidget* window;  
  // GtkWidget* image;
  //GtkWidget *Button;
  GtkWidget *MenuBar;
  GtkWidget *Menu;
  // GtkWidget *label;
  GtkWidget *MenuItem;
  // GtkWidget *VBox;
  GtkWidget *Image_box;
   
  gtk_init (&argc, &argv);
  
 
  
  ////////////// WINDOW/////////////////
  // window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
  Screen *scre = init_screen(gtk_image_new_from_file(argv[1]));
  
  ////////////post Window/////////////////
  gtk_window_set_position(GTK_WINDOW(scre->Window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(scre->Window), 320,200); 
 
  //image
  Image_box = gtk_vbox_new(FALSE, 5 );
  gtk_container_add(GTK_CONTAINER(scre->Window),Image_box);
  image = gtk_image_new_from_file(argv[1]);
  // gtk_box_pack_start(GTK_BOX(Image_box), image,FALSE,TRUE,0);

 
  MenuBar = gtk_menu_bar_new();
  Menu = gtk_menu_new();
  
    //////////////////////MENU/////////////////////////  
   
  MenuItem = gtk_menu_item_new_with_label("Choose");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  G_CALLBACK(choose), NULL);
  
 if(Picture != NULL)
    {image = Picture;}

    
  MenuItem = gtk_menu_item_new_with_label("Save");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  GTK_SIGNAL_FUNC(save), NULL);

    
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


  /* if(Picture != NULL)
     {image = Picture;}*/
  
   //ADD Menu
  MenuItem = gtk_menu_item_new_with_label("File");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem), Menu);

  //ADD file top window
  gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), MenuItem);
  
  // Menu au dessu image//
  gtk_box_pack_start(GTK_BOX(Image_box), MenuBar, FALSE, FALSE, 0);  
  gtk_box_pack_start(GTK_BOX(Image_box),scre->image,TRUE,FALSE,0);
    
  gtk_signal_connect(GTK_OBJECT (scre->Window), "destroy", GTK_SIGNAL_FUNC (destroy), NULL);
 
  gtk_widget_show_all(scre->Window);
  gtk_main();
  //return EXIT_SUCCESS;
  return 0;
}
