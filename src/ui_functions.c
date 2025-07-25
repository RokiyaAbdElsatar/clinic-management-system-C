#include "../include/ui_header.h"
#include "../include/strHeader.h"
#include <gtk/gtk.h>

extern GtkWidget *admin_window;
extern GtkWidget *clinet_window;
extern GtkWidget *main_window;
extern GtkWidget *admin_dashboard;
extern GtkListStore *patient_store;
extern GtkTreeView *treeview;

void on_back_clicked(GtkWidget *widget, gpointer data)
{
    gtk_widget_hide(admin_window);
    gtk_widget_hide(clinet_window);
    gtk_widget_hide(admin_dashboard);
    gtk_widget_show_all(main_window);
}

void add_patient_window(GtkWidget *parent_window, gpointer data)
{
    GtkWidget *dialog, *content_area, *grid;
    GtkWidget *id_entry, *name_entry, *age_entry, *gender_entry;
    GtkWidget *btn_save, *btn_cancel;

    dialog = gtk_dialog_new_with_buttons("Add New Patient",
                                         GTK_WINDOW(data), 
                                         GTK_DIALOG_MODAL,
                                         NULL, NULL);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(name_entry), "Enter Name");

    age_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(age_entry), "Enter Age");

    gender_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(gender_entry), "Enter Gender");

    id_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(id_entry), "Enter ID");

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Name:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Age:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), age_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Gender:"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gender_entry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("ID:"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 3, 1, 1);

    btn_save = gtk_button_new_with_label("Save");
    btn_cancel = gtk_button_new_with_label("Cancel");

    gtk_grid_attach(GTK_GRID(grid), btn_save, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_cancel, 1, 4, 1, 1);

    gtk_container_add(GTK_CONTAINER(content_area), grid);
    gtk_widget_show_all(dialog);

    AddPatientData *patient_data = g_malloc(sizeof(AddPatientData));
    patient_data->entry_name = name_entry;
    patient_data->entry_age = age_entry;
    patient_data->entry_gender = gender_entry;
    patient_data->entry_id = id_entry;
    patient_data->dialog = dialog;
    patient_data->store = patient_store;
    patient_data->treeview = treeview;

    g_signal_connect(btn_save, "clicked", G_CALLBACK(on_save_patient_clicked), patient_data);
    g_signal_connect_swapped(btn_cancel, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);
}

void on_save_patient_clicked(GtkWidget *widget, gpointer data)
{
    if (data == NULL) {
        g_print("Error: patientData is NULL\n");
        return;
    }

    AddPatientData *patientData = (AddPatientData *)data;

    if (!GTK_IS_ENTRY(patientData->entry_name) ||
        !GTK_IS_ENTRY(patientData->entry_age) ||
        !GTK_IS_ENTRY(patientData->entry_gender) ||
        !GTK_IS_ENTRY(patientData->entry_id))
    {
        g_print("Error: One of the GtkEntry widgets is invalid.\n");
        return;
    }

    const gchar *name = gtk_entry_get_text(GTK_ENTRY(patientData->entry_name));
    const gchar *age_str = gtk_entry_get_text(GTK_ENTRY(patientData->entry_age));
    const gchar *gender = gtk_entry_get_text(GTK_ENTRY(patientData->entry_gender));
    const gchar *id_str = gtk_entry_get_text(GTK_ENTRY(patientData->entry_id));

    int age = atoi(age_str);
    int id = atoi(id_str);

    if (strlen(name) == 0 || age <= 0 || strlen(gender) == 0 || id <= 0)
    {
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(patientData->dialog),
                                                         GTK_DIALOG_MODAL,
                                                         GTK_MESSAGE_ERROR,
                                                         GTK_BUTTONS_OK,
                                                         "Please fill all fields correctly.");
        gtk_window_set_position(GTK_WINDOW(error_dialog), GTK_WIN_POS_CENTER_ALWAYS);
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
        return;
    }

    addPatient(id, age, name, gender);

    // Print the list of patients to the console
    g_print("=== List of Patients ===\n");
    Patient *current = head;
    while (current != NULL)
    {
        g_print("Patient ID: %d, Name: %s, Age: %d, Gender: %s\n",
                current->id, current->name, current->age, current->gender);
        current = current->next;
    }

    gtk_widget_destroy(patientData->dialog);
    g_free(patientData); 
}

void displayGUI(GtkWidget *parent_window)
{
    add_patient_window(parent_window, NULL);  
}
