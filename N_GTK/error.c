#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include<gtk/gtk.h>
#include "callback.h"
#include "document.h"
#include "error.h"
#include "barreoutils.h"
#include "menu.h"
#include "raccourcis.h"

static void print_message (GtkMessageType, const gchar *, va_list);

void print_info (char *format, ...)
{
  va_list va;

  va_start (va, format);
  print_message (GTK_MESSAGE_INFO, format, va);
}

void print_warning (char *format, ...)
{
  va_list va;

  va_start (va, format);
  print_message (GTK_MESSAGE_WARNING, format, va);
}

void print_error (char *format, ...)
{
  va_list va;

  va_start (va, format);
  print_message (GTK_MESSAGE_ERROR, format, va);
  exit (EXIT_FAILURE);
}

static void print_message (GtkMessageType type, const gchar *format, va_list va)
{
  gchar *message = NULL;
  GtkWidget *p_dialog = NULL;

  message = g_strdup_vprintf (format, va);
  p_dialog = gtk_message_dialog_new (docs.p_main_window, GTK_DIALOG_MODAL, type, GTK_BUTTONS_OK, message);
  g_free (message), message = NULL;
  gtk_dialog_run (GTK_DIALOG (p_dialog));
  gtk_widget_destroy (p_dialog);
}
