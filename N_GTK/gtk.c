#include <stdlib.h>
#include <glib.h>
#include<gtk/gtk.h>
#include "callback.h"
#include "document.h"
#include "error.h"
#include "barreoutils.h"
#include "menu.h"
#include "raccourcis.h"

docs_t docs = {NULL, NULL, NULL, NULL, NULL, NULL};

void cb_quit (GtkWidget *, gpointer);

int main (int argc, char **argv)
{
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;
  GtkWidget *p_hpaned = NULL;
  GtkWidget *p_text_view = NULL;

  /* Initialisation de GTK+ */
  gtk_init (&argc, &argv);

/* Creation de la zone de texte */
  p_text_view = gtk_text_view_new ();

  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_maximize (GTK_WINDOW (p_window));
  gtk_window_set_title (GTK_WINDOW (p_window), "Editeur de texte en GTK+");
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);
  docs.p_main_window = GTK_WINDOW (p_window);

  /* Creation du conteneur principal */
  p_main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

  /* Creation du menu */
  gtk_box_pack_start (GTK_BOX (p_main_box), GTK_WIDGET (menu_new (p_text_view)), FALSE, FALSE, 0);

  /* Creation de la barre d'outils */
  gtk_box_pack_start (GTK_BOX (p_main_box), GTK_WIDGET (toolbar_new (p_text_view)), FALSE, FALSE, 0);

  /* Creation du separateur horizontal */
  p_hpaned = gtk_paned_new (GTK_ORIENTATION_VERTICAL);
  gtk_box_pack_start (GTK_BOX (p_main_box), p_hpaned, TRUE, TRUE, 0);

  /* Creation de l'aborescence */
  {
    GtkWidget *p_tree_view = NULL;
    GtkWidget *p_scrolled_window = NULL;
    GtkListStore *p_list_store = NULL;
    GtkCellRenderer *p_renderer = NULL;
    GtkTreeViewColumn *p_column = NULL;

    p_list_store = gtk_list_store_new (2, GDK_TYPE_PIXBUF, G_TYPE_STRING);
    docs.p_list_store = p_list_store;
    docs.dir_name = g_strdup (g_get_home_dir ());
    dir_list ();

    p_scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (p_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_paned_add1 (GTK_PANED (p_hpaned), p_scrolled_window);

    p_tree_view = gtk_tree_view_new_with_model (GTK_TREE_MODEL (p_list_store));
    p_renderer = gtk_cell_renderer_pixbuf_new ();
    p_column = gtk_tree_view_column_new_with_attributes (NULL, p_renderer, "pixbuf", 0, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (p_tree_view), p_column);
    p_renderer = gtk_cell_renderer_text_new ();
    p_column = gtk_tree_view_column_new_with_attributes (NULL, p_renderer, "text", 1, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (p_tree_view), p_column);
    gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (p_tree_view), FALSE);
    g_signal_connect (G_OBJECT (p_tree_view), "row-activated", G_CALLBACK (cb_select), NULL);
    gtk_container_add (GTK_CONTAINER (p_scrolled_window), p_tree_view);
  }

  /* Creation de la page d'onglets */
  {
    GtkWidget *p_notebook = NULL;

    p_notebook = gtk_notebook_new ();
    gtk_paned_add2 (GTK_PANED (p_hpaned), p_notebook);
    g_signal_connect (G_OBJECT (p_notebook), "switch-page", G_CALLBACK (cb_page_change), NULL);
    docs.p_notebook = GTK_NOTEBOOK (p_notebook);
  }

  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);
  gtk_paned_set_position (GTK_PANED (p_hpaned), 200);

  /* Lancement de la boucle principale */
  gtk_main ();
  return EXIT_SUCCESS;
}

void cb_quit (GtkWidget *p_widget, gpointer user_data)
{
  gtk_main_quit();

  /* Parametres inutilises */
  (void)p_widget;
  (void)user_data;
}
