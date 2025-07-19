#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h> 
#include "ui_header.h"

int main(int argc, char *argv[]) {

    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *label2;
    GtkWidget *fixed;
    GtkWidget *adminModeBTN;
    GtkWidget *clintModeBTN;
    GtkWidget *background;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Clinic Management System");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 700);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("./images/bg.png", 800, 700, FALSE, NULL);
    background = gtk_image_new_from_pixbuf(pixbuf);
    g_object_unref(pixbuf); 
    gtk_fixed_put(GTK_FIXED(fixed), background, 0, 0);

    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<span font='24' style='italic'><b>Welcome to clinic system</b></span>");
    gtk_fixed_put(GTK_FIXED(fixed), label, 170, 50);

    label2 = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label2), "<span font='18' style='italic'><b>Choose the Mode</b></span>");
    gtk_fixed_put(GTK_FIXED(fixed), label2, 280, 175);

    adminModeBTN = gtk_button_new_with_label("Admin");
    g_signal_connect(adminModeBTN, "clicked", G_CALLBACK(show_admin_mode), window);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "button {"
                                    "  font-size:18px;"
                                    "  font-weight:bold;"
                                    "  font-style:italic;"
                                    "  background: #01c8ea;"
                                    "  color: white;"
                                    "  border-radius: 10px;"
                                    "  border:1px solid #e8e9eb;"
                                    "  padding: 10px 20px;"
                                    "  min-width: 100px;"
                                    "  min-height: 35px;"
                                    "}",
                                    -1, NULL);

    GtkStyleContext *context = gtk_widget_get_style_context(adminModeBTN);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_fixed_put(GTK_FIXED(fixed), adminModeBTN, 550, 400);

    clintModeBTN = gtk_button_new_with_label("Clinet");
    GtkStyleContext *context2 = gtk_widget_get_style_context(clintModeBTN);
    gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_fixed_put(GTK_FIXED(fixed), clintModeBTN, 100, 400);

    gtk_widget_show_all(window);
    gtk_main();
}
