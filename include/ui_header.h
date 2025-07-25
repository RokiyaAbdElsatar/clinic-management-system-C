#include <gtk/gtk.h>
extern GtkListStore *patient_store;
extern GtkTreeView *treeview;


typedef struct EditData{
    GtkWidget *id_entry;
    GtkWidget *dialog;
} EditData;

typedef struct EditFields {
    GtkWidget *name;
    GtkWidget *age;
    GtkWidget *gender;
    GtkWidget *dialog;
    int id;
} EditFields;

// from clintMode.c
extern GtkWidget *ID_text_Entry;
extern GtkWidget *patient_info_label;
extern GtkWidget *patient_reservations_label;

void show_admin_mode(GtkWidget *parent_window);
void show_clinet_mode(GtkWidget *parent_window);
void show_admin_dashboard(GtkWidget *parent_window);
// void open_admin_window();
void on_back_clicked(GtkWidget *widget, gpointer data);

void add_patient_window(GtkWidget *parent_window, gpointer data);

void on_save_patient_clicked(GtkWidget *widget, gpointer data);

void on_clear_fields_clicked(GtkWidget *widget, gpointer data);

void displayGUI(GtkWidget *parent_window);

void edit_patient_window(GtkWidget *widget, gpointer user_data);

void on_find_patient_clicked(GtkWidget *widget, gpointer data);

void on_save_edit_clicked(GtkWidget *widget, gpointer data);


void slot_patient_window(GtkWidget *widget, gpointer parent_window);

void on_search_clicked(GtkWidget *widget, gpointer data);