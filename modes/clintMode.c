#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "../include/ui_header.h"
#include "../include/strHeader.h"

extern GtkWidget *clinet_window;
extern GtkWidget *main_window;

GtkWidget *ID_text_Entry;
GtkWidget *SearchBTN;

GtkWidget *patient_info_label;
GtkWidget *patient_reservations_label;

void show_clinet_mode(GtkWidget *parent_window)
{
        gtk_widget_hide(main_window);
        GtkWidget *background;
        GtkWidget *fixed;
        GtkWidget *label;
        GtkWidget *IDlabel;
        GtkWidget *backBTN;

        clinet_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(clinet_window), "Clinet Mode");
        gtk_window_set_default_size(GTK_WINDOW(clinet_window), 800, 700);
        gtk_window_set_position(GTK_WINDOW(clinet_window), GTK_WIN_POS_CENTER_ALWAYS);
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

        label = gtk_label_new("Welcome to Clinet");
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

        IDlabel = gtk_label_new("Enter the Patient ID :");
        gtk_widget_set_name(IDlabel, "ID-label");
        GtkCssProvider *providerID = gtk_css_provider_new();
        gtk_css_provider_load_from_data(providerID,
                                        "#ID-label {\n"
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
        GtkStyleContext *contextID = gtk_widget_get_style_context(IDlabel);
        gtk_style_context_add_provider(contextID,
                                       GTK_STYLE_PROVIDER(providerID),
                                       GTK_STYLE_PROVIDER_PRIORITY_USER);
        gtk_fixed_put(GTK_FIXED(fixed), IDlabel, 200, 300);

        // Patient ID entry field and label and button
        ID_text_Entry = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(ID_text_Entry), "Enter ID");
        gtk_fixed_put(GTK_FIXED(fixed), ID_text_Entry, 350, 350);
        gtk_widget_set_size_request(ID_text_Entry, 200, 30);

        SearchBTN = gtk_button_new_with_label("Search");
        gtk_fixed_put(GTK_FIXED(fixed), SearchBTN, 490, 400);
        g_signal_connect(SearchBTN, "clicked", G_CALLBACK(on_search_clicked), NULL);
        GtkCssProvider *providerSearch = gtk_css_provider_new();
        gtk_css_provider_load_from_data(providerSearch,
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
        GtkStyleContext *contextSearch = gtk_widget_get_style_context(SearchBTN);
        gtk_style_context_add_provider(contextSearch, GTK_STYLE_PROVIDER(providerSearch), GTK_STYLE_PROVIDER_PRIORITY_USER);

        // Label to show patient info
        patient_info_label = gtk_label_new("");
        gtk_fixed_put(GTK_FIXED(fixed), patient_info_label, 200, 460);
        gtk_widget_set_size_request(patient_info_label, 400, 100);

        // Label to show reservation info
        patient_reservations_label = gtk_label_new("");
        gtk_fixed_put(GTK_FIXED(fixed), patient_reservations_label, 200, 530);
        gtk_widget_set_size_request(patient_reservations_label, 400, 100);

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
