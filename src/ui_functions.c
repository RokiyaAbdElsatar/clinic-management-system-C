#include "../include/ui_header.h"
// #include "../include/strHeader.h"

#include <gtk/gtk.h>

extern GtkWidget *admin_window;
extern GtkWidget *clinet_window;
extern GtkWidget *main_window;
void on_back_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(admin_window);
    gtk_widget_hide(clinet_window);
    gtk_widget_show_all(main_window);
}
