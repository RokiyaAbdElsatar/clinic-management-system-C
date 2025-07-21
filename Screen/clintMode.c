#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h> 
#include "../ui_header.h"
#include "../strHeader.h"

extern GtkWidget *clinet_window;
extern GtkWidget *main_window;


void show_clinet_mode(GtkWidget *parent_window) {
        gtk_widget_hide(main_window);
        GtkWidget *background;
        GtkWidget *fixed;
        GtkWidget *label;
        GtkWidget *IDlabel;
        GtkWidget *backBTN;

        clinet_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(clinet_window), "Clinet Mode");
        gtk_window_set_default_size(GTK_WINDOW(clinet_window), 800, 700);

        fixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(clinet_window), fixed);

        // Load background image

        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("./images/bg.png", 800, 700, FALSE, NULL);
        background = gtk_image_new_from_pixbuf(pixbuf);
        g_object_unref(pixbuf); 
        gtk_fixed_put(GTK_FIXED(fixed), background, 0, 0);  

           // Create Glass Box effect
        GtkWidget *glass_box = gtk_frame_new(NULL);
        gtk_widget_set_name(glass_box, "glass_box");
        gtk_fixed_put(GTK_FIXED(fixed), glass_box, 130, 35);
        gtk_widget_set_size_request(glass_box, 550, 500);
        
        
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
        

        // Create labels and buttons

        label = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(label), "<span font='24' style='italic' color='#292843'><b>Welcome to Clinet</b></span>");
        gtk_fixed_put(GTK_FIXED(fixed), label, 200, 50);

        IDlabel = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(IDlabel), "<span font='14' style='italic' color='#292843'><b>Enter the Patient ID</b></span>");
        gtk_fixed_put(GTK_FIXED(fixed), IDlabel, 200, 320);

        // Back button to return to main window

        backBTN = gtk_button_new_with_label("Back");
        gtk_fixed_put(GTK_FIXED(fixed), backBTN, 100, 600);
        g_signal_connect(backBTN, "clicked", G_CALLBACK(on_back_clicked), NULL);
        GtkCssProvider *provider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(provider,
                                    "button {"
                                    "  font-size:18px;"
                                    "  font-weight:bold;"
                                    "  font-style:italic;"
                                    "  background: transparent;"
                                    "  color: #04A2BE;"
                                    "  border-radius: 10px;"
                                    "  border:1px solid #e8e9eb;"
                                    "  padding: 10px 20px;"
                                    "  min-width: 80px;"
                                    "  min-height: 25px;"
                                    "}",
                                    -1, NULL);
                                    
    GtkStyleContext *context = gtk_widget_get_style_context(backBTN);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    


     



     

        gtk_widget_show_all(clinet_window);
        // gtk_widget_hide(parent_window);
}
