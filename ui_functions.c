#include "ui_header.h"

void open_admin_window() {
    GtkWidget *admin_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(admin_window), "Admin Mode");
    gtk_window_set_default_size(GTK_WINDOW(admin_window), 400, 300);
    gtk_widget_show_all(admin_window);
}