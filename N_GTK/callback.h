#ifndef H_CALLBACK
#define H_CALLBACK

#include<gtk/gtk.h>
#include "document.h"
#include "error.h"
#include "barreoutils.h"
#include "menu.h"
#include "raccourcis.h"

void cb_new (GtkWidget *, gpointer);
void cb_open (GtkWidget *, gpointer);
void cb_save (GtkWidget *, gpointer);
void cb_saveas (GtkWidget *, gpointer);
void cb_close (GtkWidget *, gpointer);
void cb_quit (GtkWidget *, gpointer);
void cb_select (GtkTreeView *, GtkTreePath *, GtkTreeViewColumn *, gpointer);
void cb_modifie (GtkWidget *, gpointer);
void cb_page_change (GtkNotebook *, GtkNotebook *, guint, gpointer);
void dir_list (void);

#endif /* not H_CALLBACK */
