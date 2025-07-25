#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "../include/ui_header.h"
#include "../include/strHeader.h"

extern GtkWidget *admin_window;
extern GtkWidget *main_window;

GtkWidget *admin_dashboard;
GtkListStore *patient_store = NULL;
GtkTreeView *treeview;

// extern void populate_treeview_from_list(GtkListStore *store);

void show_admin_dashboard(GtkWidget *parent_window)
{
    gtk_widget_hide(admin_window);
    GtkWidget *background;
    GtkWidget *fixed;
    GtkWidget *backBTN;

    GtkWidget *addBTN;
    GtkWidget *editBTN;
    GtkWidget *SlotBTN;
    GtkWidget *cancelBTN;

    admin_dashboard = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(admin_dashboard), "Admin Mode");
    gtk_window_set_default_size(GTK_WINDOW(admin_dashboard), 800, 700);
    gtk_window_set_position(GTK_WINDOW(admin_dashboard), GTK_WIN_POS_CENTER_ALWAYS);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(admin_dashboard), fixed);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("./images/bg.png", 800, 700, FALSE, NULL);
    background = gtk_image_new_from_pixbuf(pixbuf);
    g_object_unref(pixbuf);
    gtk_fixed_put(GTK_FIXED(fixed), background, 0, 0);

    GtkWidget *glass_box = gtk_frame_new(NULL);
    gtk_widget_set_name(glass_box, "glass_box");
    gtk_fixed_put(GTK_FIXED(fixed), glass_box, 60, 36);
    gtk_widget_set_size_request(glass_box, 670, 570);

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

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(glass_box), vbox);

    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 10);

    addBTN = gtk_button_new_with_label("Add Patient");

    GtkCssProvider *provideraddBTN = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provideraddBTN,
                                    "button {"
                                    "  font-size:18px;"
                                    "  font-weight:bold;"
                                    "  font-style:italic;"
                                    "  background: #01c8ea;"
                                    "  color: white;"
                                    "  border-radius: 10px;"
                                    "  border:1px solid #e8e9eb;"
                                    "  padding: 10px 20px;"
                                    "  min-width: 80px;"
                                    "  min-height: 30px;"
                                    "}",
                                    -1, NULL);

    GtkStyleContext *contextaddBTN = gtk_widget_get_style_context(addBTN);
    gtk_style_context_add_provider(contextaddBTN, GTK_STYLE_PROVIDER(provideraddBTN), GTK_STYLE_PROVIDER_PRIORITY_USER);

    editBTN = gtk_button_new_with_label("Edit Patient");
    GtkCssProvider *providereditBTN = gtk_css_provider_new();
    gtk_css_provider_load_from_data(providereditBTN,
                                    "button {"
                                    "  font-size:18px;"
                                    "  font-weight:bold;"
                                    "  font-style:italic;"
                                    "  background: #01c8ea;"
                                    "  color: white;"
                                    "  border-radius: 10px;"
                                    "  border:1px solid #e8e9eb;"
                                    "  padding: 10px 20px;"
                                    "  min-width: 80px;"
                                    "  min-height: 30px;"
                                    "}",
                                    -1, NULL);

    GtkStyleContext *contexteditBTN = gtk_widget_get_style_context(editBTN);
    gtk_style_context_add_provider(contexteditBTN, GTK_STYLE_PROVIDER(providereditBTN), GTK_STYLE_PROVIDER_PRIORITY_USER);

    SlotBTN = gtk_button_new_with_label("Reserve Slot");
    GtkCssProvider *providerslotBTN = gtk_css_provider_new();
    gtk_css_provider_load_from_data(providerslotBTN,
                                    "button {"
                                    "  font-size:18px;"
                                    "  font-weight:bold;"
                                    "  font-style:italic;"
                                    "  background: #01c8ea;"
                                    "  color: white;"
                                    "  border-radius: 10px;"
                                    "  border:1px solid #e8e9eb;"
                                    "  padding: 10px 20px;"
                                    "  min-width: 80px;"
                                    "  min-height: 30px;"
                                    "}",
                                    -1, NULL);

    GtkStyleContext *contextslotBTN = gtk_widget_get_style_context(SlotBTN);
    gtk_style_context_add_provider(contextslotBTN, GTK_STYLE_PROVIDER(providerslotBTN), GTK_STYLE_PROVIDER_PRIORITY_USER);

    cancelBTN = gtk_button_new_with_label("Cancel Reservation");
    GtkCssProvider *providercancelBTN = gtk_css_provider_new();
    gtk_css_provider_load_from_data(providercancelBTN,
                                    "button {"
                                    "  font-size:18px;"
                                    "  font-weight:bold;"
                                    "  font-style:italic;"
                                    "  background: #01c8ea;"
                                    "  color: white;"
                                    "  border-radius: 10px;"
                                    "  border:1px solid #e8e9eb;"
                                    "  padding: 10px 20px;"
                                    "  min-width: 80px;"
                                    "  min-height: 30px;"
                                    "}",
                                    -1, NULL);

    GtkStyleContext *contextcancelBTN = gtk_widget_get_style_context(cancelBTN);
    gtk_style_context_add_provider(contextcancelBTN, GTK_STYLE_PROVIDER(providercancelBTN), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_box_pack_start(GTK_BOX(button_box), addBTN, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(button_box), editBTN, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(button_box), SlotBTN, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(button_box), cancelBTN, TRUE, TRUE, 5);

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scrolled_window, 630, 400);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 10);

    treeview = GTK_TREE_VIEW(gtk_tree_view_new());
    GtkWidget *tree_view = GTK_WIDGET(treeview);

    GtkCssProvider *providerTable = gtk_css_provider_new();
    gtk_css_provider_load_from_data(providerTable,
                                    "treeview, scrolledwindow { background-color: transparent; }",
                                    -1, NULL);

    GtkStyleContext *context;
    context = gtk_widget_get_style_context(tree_view);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(providerTable), GTK_STYLE_PROVIDER_PRIORITY_USER);

    context = gtk_widget_get_style_context(scrolled_window);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(providerTable), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);

    patient_store = gtk_list_store_new(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(patient_store));
    treeview = GTK_TREE_VIEW(tree_view);

    // populate_treeview_from_list(patient_store);

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GdkRGBA transparent_bg;
    gdk_rgba_parse(&transparent_bg, "rgba(255, 255, 255, 0.0)");
    g_object_set(renderer, "cell-background-rgba", &transparent_bg, NULL);

    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "ID", renderer, "text", 0, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "Name", renderer, "text", 1, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "Age", renderer, "text", 2, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "Gender", renderer, "text", 3, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "Slot", renderer, "text", 4, NULL);

    // Connect buttons to their respective functions
    
    g_signal_connect(addBTN, "clicked", G_CALLBACK(displayGUI), admin_dashboard);
    g_signal_connect(editBTN, "clicked", G_CALLBACK(edit_patient_window), admin_dashboard);
   // g_signal_connect(SlotBTN, "clicked", G_CALLBACK(slot_patient_window), admin_dashboard);

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

    GtkStyleContext *contextbackBTN = gtk_widget_get_style_context(backBTN);
    gtk_style_context_add_provider(contextbackBTN, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_show_all(admin_dashboard);
}