# include <gtk/gtk.h>
# include <stdlib.h>
# include <stdio.h>
<<<<<<< HEAD
# include <err.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

void DataBase(char *path);
=======
# include <string.h>
# include <err.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "../../src/ViolaJones/pixel_operations.h"
# include "../../src/ViolaJones/haar.h"
# include "../../src/ViolaJones/Ulong_tab.h"
# include "../../src/ViolaJones/integral_image.h"
# include "../../src/ViolaJones/adaboost.h"
# include "../../src/Preprocessing/Image_OPs.h"
# include "../../src/SDL_operations/SDL_OPs.h"
# include "../../src/yolo.h"
# include <assert.h>
# include <sys/stat.h>
# include <unistd.h>
# include "../../src/ViolaJones/cascade.h"

>>>>>>> d73975cb80a15958a14cd83638d71863195ad781

typedef struct Screen Screen;
struct Screen
{
  GtkWidget* Window;
  GtkWidget* image;
  char *title,*name,*chemin;

};
static Screen *scre;

void Destroy(void) {

  gtk_main_quit();
}

void  Analyse(char* name)
{

  yolo(&name);
}
void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection)
{
  const gchar* chemin;
  GtkWidget *dialog;
  if(bouton){
  chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection) );

  dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection),
				  GTK_DIALOG_MODAL,
				  GTK_MESSAGE_INFO,
				  GTK_BUTTONS_OK,
				  "Vous avez choisi :\n%s", chemin);
  scre->chemin=(char*)chemin;
  scre->name = g_path_get_basename(chemin);
  gtk_image_set_from_file(GTK_IMAGE(scre->image),chemin);

<<<<<<< HEAD
  char* path = (char*)chemin;
  DataBase(path);
  
=======
>>>>>>> d73975cb80a15958a14cd83638d71863195ad781
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  gtk_widget_destroy(file_selection);

  }
}

void Navigate(){
  GtkWidget *selection;

  selection = gtk_file_selection_new( g_locale_to_utf8( "Sélectionnez un fichier", -1, NULL, NULL, NULL) );
  gtk_widget_show(selection);


  gtk_window_set_modal(GTK_WINDOW(selection), TRUE);

  g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked",
		   G_CALLBACK(recuperer_chemin), selection);

  g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked",
			   G_CALLBACK(gtk_widget_destroy), selection);
}


Screen* init_screen(GtkWidget* image)
{
  Screen *screen=malloc(sizeof(struct Screen));
  screen->image = image;
  screen->Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  screen->title ="Farce Project";
  screen->name=NULL;
  return screen;
 }


void DataBase(char *path)
{
  const char* src_path;
  const char* dst_path;
  int src_fd, dst_fd, err;
  unsigned char buffer[4096];

  src_path = path;
  dst_path = "database/";

  src_fd = open(src_path, O_RDONLY);
  dst_fd = open(dst_path, O_WRONLY);
  
 while (1) {
    err = read(src_fd, buffer, 4096);
    if (err == -1) {
      printf("Error reading file.\n");
      exit(1);
    }

    if (err == 0) break;

    err = write(dst_fd, buffer, err);
    if (err == -1) {
      printf("Error writing to file.\n");
      exit(1);
    }
    exit(1);
    }
  
 //  execve(src_path], newargv, newenviron);
  
 //free(buffer);
  close(src_fd);
  close(dst_fd);

}


int main (int argc, char** argv) {

  GtkWidget *MenuBar;
  GtkWidget *Menu;
  GtkWidget *StatusBar;
  GtkWidget *MenuItem;
  GtkWidget *Image_box;

  gtk_init (&argc, &argv);

  ////////////// WINDOW/////////////////
  scre = init_screen(gtk_image_new_from_file(argv[1]));

  ////////////post Window/////////////////
  gtk_window_set_position(GTK_WINDOW(scre->Window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(scre->Window), 320,200);


  /////////////image/////////////
  Image_box = gtk_vbox_new(FALSE, 0 );
  gtk_container_add(GTK_CONTAINER(scre->Window),Image_box);

  /////////////////////////

  MenuBar = gtk_menu_bar_new();
  Menu = gtk_menu_new();

  //////////////////////MENU/////////////////////////


  MenuItem =gtk_menu_item_new_with_mnemonic(("_Add Pictures"));
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",GTK_SIGNAL_FUNC(Navigate),NULL);

  MenuItem = gtk_menu_item_new_with_label("Analyse");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  GTK_SIGNAL_FUNC(Analyse),scre->chemin);

  MenuItem = gtk_menu_item_new_with_label("Leave");
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu), MenuItem);
  gtk_signal_connect(GTK_OBJECT (MenuItem), "activate",  GTK_SIGNAL_FUNC(Destroy), NULL);

  //////////////////////End MENU/////////////////////////////////

   //////Photo title/////////
  StatusBar = gtk_statusbar_new();
  gtk_statusbar_push (GTK_STATUSBAR (StatusBar), 0, scre->title);
  //////////////////////////////////////////////////////////////

  //ADD Menu
  MenuItem = gtk_menu_item_new_with_label("File");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem), Menu);



  //ADD file top window
  gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar), MenuItem);

  // Menu au dessus image//
  gtk_box_pack_start(GTK_BOX(Image_box), MenuBar, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(Image_box),scre->image,TRUE,FALSE,0);
  gtk_box_pack_end(GTK_BOX(Image_box), StatusBar, FALSE, FALSE, 0);

  gtk_signal_connect(GTK_OBJECT (scre->Window), "destroy", GTK_SIGNAL_FUNC (Destroy), NULL);

  gtk_widget_show_all(scre->Window);
  gtk_main();

  //return EXIT_SUCCESS;
  return 0;
}
