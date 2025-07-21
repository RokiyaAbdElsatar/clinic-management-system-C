#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h> 
#include "../include/ui_header.h"

GtkWidget *admin_window;
GtkWidget *clinet_window;
GtkWidget *main_window;
int main(int argc, char *argv[]) {

    GtkWidget *label;
    GtkWidget *label2;
    GtkWidget *fixed;
    GtkWidget *adminModeBTN;
    GtkWidget *clintModeBTN;
    GtkWidget *background;

    gtk_init(&argc, &argv);
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "Clinic Management System");
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 700);
    gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(main_window), fixed);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("./images/bg.png", 800, 700, FALSE, NULL);
    background = gtk_image_new_from_pixbuf(pixbuf);
    g_object_unref(pixbuf); 
    gtk_fixed_put(GTK_FIXED(fixed), background, 0, 0);

    
        // Create Glass Box effect
        GtkWidget *glass_box = gtk_frame_new(NULL);
        gtk_widget_set_name(glass_box, "glass_box");
      gtk_fixed_put(GTK_FIXED(fixed), glass_box, 60, 36);
        gtk_widget_set_size_request(glass_box, 670, 570);

        // Glass effect style

        GtkCssProvider *glass_provider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(glass_provider,
                                        "#glass_box {"
                                        "  background-color: rgba(1, 200, 234, 0.1);" 
                                        "  border-radius: 20px;"
                                        "  border: 1px solid rgba(255, 255, 255, 0.3);"
                                        "  box-shadow: 0 8px 32px rgba(0, 0, 0, 0.25);"
                                        "  -gtk-icon-shadow: none;"    
                                        "}",
                                        -1, NULL);
        GtkStyleContext *glass_context = gtk_widget_get_style_context(glass_box);
        gtk_style_context_add_provider(glass_context, GTK_STYLE_PROVIDER(glass_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);


    label =gtk_label_new("Welcome to clinic system");
    gtk_widget_set_name(label, "welcome-label");
    GtkCssProvider *providerStroke = gtk_css_provider_new();
    gtk_css_provider_load_from_data(providerStroke,
    "#welcome-label {\n"
    "  font-size: 40px;\n"
    "  font-style: italic;\n"
    "  font-weight: bold;\n"
    "  color: #0078a9;\n"
    "  text-shadow: -1px -1px 0 white,\n"
    "               1px -1px 0 white,\n"
    "              -1px 1px 0 white,\n"
    "               1px 1px 0 white;\n"
    "}", -1, NULL);
    GtkStyleContext *contextStroke = gtk_widget_get_style_context(label);
    gtk_style_context_add_provider(contextStroke,
    GTK_STYLE_PROVIDER(providerStroke),
    GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_fixed_put(GTK_FIXED(fixed), label, 175, 50);

    label2 = gtk_label_new("Choose the Mode");
    gtk_widget_set_name(label2, "mode-label");
    GtkCssProvider *providerlabel2 = gtk_css_provider_new();
    gtk_css_provider_load_from_data(providerlabel2,
    "#mode-label {\n"
    "  font-size: 35px;\n"
    "  font-style: italic;\n"
    "  color: #0078a9;\n"
        "  font-weight: bold;\n"
    "  text-shadow: -1px -1px 0 white,\n"
    "               1px -1px 0 white,\n"
    "              -1px 1px 0 white,\n"
    "               1px 1px 0 white;\n"
    "}", -1, NULL);
    GtkStyleContext *contextlabel2 = gtk_widget_get_style_context(label2);
    gtk_style_context_add_provider(contextlabel2, GTK_STYLE_PROVIDER(providerlabel2), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_fixed_put(GTK_FIXED(fixed), label2, 280, 175);

    adminModeBTN = gtk_button_new_with_label("Admin");
    g_signal_connect(adminModeBTN, "clicked", G_CALLBACK(show_admin_mode), main_window);

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
    gtk_fixed_put(GTK_FIXED(fixed), adminModeBTN, 500, 400);

    clintModeBTN = gtk_button_new_with_label("Clinet");
    g_signal_connect(clintModeBTN, "clicked", G_CALLBACK(show_clinet_mode), main_window);
    GtkStyleContext *context2 = gtk_widget_get_style_context(clintModeBTN);
    gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_fixed_put(GTK_FIXED(fixed), clintModeBTN, 150, 400);

    gtk_widget_show_all(main_window);
    gtk_main();
}
