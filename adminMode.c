#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h> 
#include "ui_header.h"

extern GtkWidget *admin_window;
extern GtkWidget *main_window;

void show_admin_mode(GtkWidget *parent_window) {
        gtk_widget_hide(main_window);
        GtkWidget *background;
        GtkWidget *fixed;
        GtkWidget *label;
        GtkWidget *backBTN;
        GtkWidget *password_Entry;
        GtkWidget *password_Label;
        GtkWidget *loginBTN;

        admin_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(admin_window), "Admin Mode");
        gtk_window_set_default_size(GTK_WINDOW(admin_window), 800, 700);

        fixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(admin_window), fixed);

        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("./images/bg.png", 800, 700, FALSE, NULL);
        background = gtk_image_new_from_pixbuf(pixbuf);
        g_object_unref(pixbuf); 
        gtk_fixed_put(GTK_FIXED(fixed), background, 0, 0);   

        label = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(label), "<span font='24' style='italic' color='white'><b>Welcome to Admin</b></span>");
        gtk_fixed_put(GTK_FIXED(fixed), label, 200, 50);

        password_Label = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(password_Label), "<span font='14' style='italic' color='white'><b>Enter Password</b></span>");
        gtk_fixed_put(GTK_FIXED(fixed), password_Label, 160, 310);

        password_Entry = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(password_Entry), "Enter Admin Password");
        gtk_entry_set_visibility(GTK_ENTRY(password_Entry), FALSE); // Hide the password
        gtk_entry_set_invisible_char(GTK_ENTRY(password_Entry), '*'); // Set the character
        gtk_fixed_put(GTK_FIXED(fixed), password_Entry, 350, 310);
        gtk_widget_set_size_request(password_Entry, 200, 30);

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
                                    "  border:1px solid #04A2BE;"
                                    "  padding: 10px 20px;"
                                    "  min-width: 80px;"
                                    "  min-height: 25px;"
                                    "}",
                                    -1, NULL);
                                    
    GtkStyleContext *context = gtk_widget_get_style_context(backBTN);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    


     



        loginBTN = gtk_button_new_with_label("Login");
        gtk_fixed_put(GTK_FIXED(fixed), loginBTN, 480, 380);
        g_signal_connect(loginBTN, "clicked", G_CALLBACK("on_login_clicked"), NULL);
        GtkCssProvider *provider2 = gtk_css_provider_new();
        gtk_css_provider_load_from_data(provider2,
                                     "button {"
                                    "  font-size:18px;"
                                    "  font-weight:bold;"
                                    "  font-style:italic;"
                                    "  background: #01c8ea;"
                                    "  color: white;"
                                    "  border-radius: 10px;"
                                    "  border:1px solid #e8e9eb;"
                                    "  padding: 10px 20px;"
                                    "  min-width: 70px;"
                                    "  min-height: 20px;"
                                    "}",
                                    -1, NULL);
        GtkStyleContext *context2 = gtk_widget_get_style_context(loginBTN);
        gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider2), GTK_STYLE_PROVIDER_PRIORITY_USER);





        gtk_widget_show_all(admin_window);
        // gtk_widget_hide(parent_window);
}
