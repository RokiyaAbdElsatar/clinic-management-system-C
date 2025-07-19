#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h> 


void show_admin_mode(GtkWidget *parent_window) {
        GtkWidget *background;
        GtkWidget *admin_window;
        GtkWidget *fixed;
        GtkWidget *label;

        admin_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(admin_window), "Admin Mode");
        gtk_window_set_default_size(GTK_WINDOW(admin_window), 800, 700);

        fixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(admin_window), fixed);

        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("./images/bg.png", 800, 700, FALSE, NULL);
        background = gtk_image_new_from_pixbuf(pixbuf);
        g_object_unref(pixbuf); 
        gtk_fixed_put(GTK_FIXED(fixed), background, 0, 0);        label = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(label), "<span font='24' style='italic'><b>Welcome to Admin</b></span>");
        gtk_fixed_put(GTK_FIXED(fixed), label, 200, 50);

        gtk_widget_show_all(admin_window);
        // gtk_widget_hide(parent_window);
}
