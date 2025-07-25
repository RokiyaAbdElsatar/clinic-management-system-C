#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "../include/ui_header.h"
#include "../include/strHeader.h"

extern GtkWidget *admin_window;
extern GtkWidget *main_window;

GtkWidget *loginBTN;
GtkWidget *password_Entry;

void show_admin_mode(GtkWidget *parent_window)
{
        gtk_widget_hide(main_window);
        GtkWidget *background;
        GtkWidget *fixed;
        GtkWidget *label;
        GtkWidget *backBTN;
        GtkWidget *password_Label;

        admin_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(admin_window), "Admin Mode");
        gtk_window_set_default_size(GTK_WINDOW(admin_window), 800, 700);
        gtk_window_set_position(GTK_WINDOW(admin_window), GTK_WIN_POS_CENTER_ALWAYS);

        fixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(admin_window), fixed);

        // Load background image

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

        // Create labels and buttons

        label = gtk_label_new("Welcome to Admin");
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
                                        "}",
                                        -1, NULL);
        GtkStyleContext *contextStroke = gtk_widget_get_style_context(label);
        gtk_style_context_add_provider(contextStroke,
                                       GTK_STYLE_PROVIDER(providerStroke),
                                       GTK_STYLE_PROVIDER_PRIORITY_USER);
        gtk_fixed_put(GTK_FIXED(fixed), label, 200, 50);

        // Password entry field and label and button

        password_Label = gtk_label_new("Enter the password :");
        gtk_widget_set_name(password_Label, "password-label");
        GtkCssProvider *providerID = gtk_css_provider_new();
        gtk_css_provider_load_from_data(providerID,
                                        "#password-label {\n"
                                        "  font-size: 20px;\n"
                                        "  font-style: italic;\n"
                                        "  color: #0078a9;\n"
                                        "  font-weight: bold;\n"
                                        "  text-shadow: -1px -1px 0 white,\n"
                                        "               1px -1px 0 white,\n"
                                        "              -1px 1px 0 white,\n"
                                        "               1px 1px 0 white;\n"
                                        "}",
                                        -1, NULL);
        GtkStyleContext *contextpassword = gtk_widget_get_style_context(password_Label);
        gtk_style_context_add_provider(contextpassword,
                                       GTK_STYLE_PROVIDER(providerID),
                                       GTK_STYLE_PROVIDER_PRIORITY_USER);
        gtk_fixed_put(GTK_FIXED(fixed), password_Label, 200, 300);

        // Password entry field
        password_Entry = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(password_Entry), "Enter Admin Password");
        gtk_entry_set_visibility(GTK_ENTRY(password_Entry), FALSE);   // Hide the password
        gtk_entry_set_invisible_char(GTK_ENTRY(password_Entry), '*'); // Set the character
        gtk_fixed_put(GTK_FIXED(fixed), password_Entry, 350, 350);
        gtk_widget_set_size_request(password_Entry, 200, 30);

        loginBTN = gtk_button_new_with_label("Login");
        gtk_fixed_put(GTK_FIXED(fixed), loginBTN, 490, 400);
        g_signal_connect(loginBTN, "clicked", G_CALLBACK(on_login_clicked), NULL);
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

        // Back button to return to main window

        backBTN = gtk_button_new_with_label("Back");
        gtk_fixed_put(GTK_FIXED(fixed), backBTN, 100, 620);
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

        gtk_widget_show_all(admin_window);
        // gtk_widget_hide(parent_window);
}
