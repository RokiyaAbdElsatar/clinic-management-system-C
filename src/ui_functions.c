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
    if (data == NULL)
    {
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

void edit_patient_window(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *dialog, *content_area, *grid;
    GtkWidget *id_entry, *btn_next;

    GtkWidget *parent_window = gtk_widget_get_toplevel(GTK_WIDGET(widget));

    dialog = gtk_dialog_new_with_buttons("Edit Patient",
                                         NULL,
                                         GTK_DIALOG_MODAL,
                                         NULL, NULL);

    if (GTK_IS_WINDOW(parent_window))
    {
        gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(parent_window));
    }

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    id_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(id_entry), "Enter Patient ID");

    btn_next = gtk_button_new_with_label("Find & Edit");

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Patient ID:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_next, 0, 1, 2, 1);

    gtk_container_add(GTK_CONTAINER(content_area), grid);
    gtk_widget_show_all(dialog);

    EditData *edit_data = g_malloc(sizeof(EditData));
    edit_data->id_entry = id_entry;
    edit_data->dialog = dialog;

    g_signal_connect(btn_next, "clicked", G_CALLBACK(on_find_patient_clicked), edit_data);
}

void on_find_patient_clicked(GtkWidget *widget, gpointer data)
{
    EditData *edit_data = (EditData *)data;
    GtkWidget *dialog = edit_data->dialog;
    GtkWidget *id_entry = edit_data->id_entry;

    const gchar *id_str = gtk_entry_get_text(GTK_ENTRY(id_entry));
    int id = atoi(id_str);

    Patient *p = findByID(id);
    if (p == NULL)
    {
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                         GTK_DIALOG_MODAL,
                                                         GTK_MESSAGE_ERROR,
                                                         GTK_BUTTONS_OK,
                                                         "Incorrect ID: %d", id);

        gtk_window_set_position(GTK_WINDOW(error_dialog), GTK_WIN_POS_CENTER_ALWAYS);
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
        return;
    }

    gtk_widget_destroy(dialog);
    g_free(edit_data);

    // Show edit form
    GtkWidget *edit_dialog, *content_area, *grid;
    GtkWidget *name_entry, *age_entry, *gender_entry, *btn_save;

    GtkWidget *parent_window = gtk_widget_get_toplevel(GTK_WIDGET(widget));

    edit_dialog = gtk_dialog_new_with_buttons("Edit Patient Info",
                                              NULL,
                                              GTK_DIALOG_MODAL,
                                              NULL, NULL);

    if (GTK_IS_WINDOW(parent_window))
    {
        gtk_window_set_transient_for(GTK_WINDOW(edit_dialog), GTK_WINDOW(parent_window));
    }

    gtk_window_set_position(GTK_WINDOW(edit_dialog), GTK_WIN_POS_CENTER_ALWAYS);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(edit_dialog));

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    name_entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(name_entry), p->name);

    age_entry = gtk_entry_new();
    gchar age_buf[16];
    sprintf(age_buf, "%d", p->age);
    gtk_entry_set_text(GTK_ENTRY(age_entry), age_buf);

    gender_entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(gender_entry), p->gender);

    btn_save = gtk_button_new_with_label("Save Changes");

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Name:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Age:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), age_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Gender:"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gender_entry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_save, 0, 3, 2, 1);

    gtk_container_add(GTK_CONTAINER(content_area), grid);
    gtk_widget_show_all(edit_dialog);

    EditFields *fields = g_malloc(sizeof(EditFields));
    fields->name = name_entry;
    fields->age = age_entry;
    fields->gender = gender_entry;
    fields->dialog = edit_dialog;
    fields->id = id;

    g_signal_connect(btn_save, "clicked", G_CALLBACK(on_save_edit_clicked), fields);
}

void on_save_edit_clicked(GtkWidget *widget, gpointer data)
{
    EditFields *edit_fields = (EditFields *)data;

    const gchar *name = gtk_entry_get_text(GTK_ENTRY(edit_fields->name));
    const gchar *age_str = gtk_entry_get_text(GTK_ENTRY(edit_fields->age));
    const gchar *gender = gtk_entry_get_text(GTK_ENTRY(edit_fields->gender));

    int age = atoi(age_str);
    if (strlen(name) == 0 || strlen(gender) == 0 || age <= 0)
    {
        GtkWidget *err = gtk_message_dialog_new(GTK_WINDOW(edit_fields->dialog),
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_ERROR,
                                                GTK_BUTTONS_OK,
                                                "Invalid input");
        gtk_window_set_position(GTK_WINDOW(err), GTK_WIN_POS_CENTER_ALWAYS);
        gtk_dialog_run(GTK_DIALOG(err));
        gtk_widget_destroy(err);
        return;
    }

    editPatient(edit_fields->id, name, age, gender);

    gtk_widget_destroy(edit_fields->dialog);
    g_free(edit_fields);
}

void slot_patient_window(GtkWidget *widget, gpointer parent_window)
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Reserve a Slot");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 250);
    gtk_window_set_transient_for(GTK_WINDOW(window), GTK_WINDOW(parent_window));
    gtk_window_set_modal(GTK_WINDOW(window), TRUE);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *id_label = gtk_label_new("Enter Patient ID:");
    GtkWidget *id_entry = gtk_entry_new();

    gtk_box_pack_start(GTK_BOX(vbox), id_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), id_entry, FALSE, FALSE, 0);

    GtkWidget *slot_label = gtk_label_new("Select Slot:");
    GtkWidget *slot_combo = gtk_combo_box_text_new();

    for (int i = 0; i < SLOT_COUNT; i++)
    {
        if (!is_slot_reserved(default_slots[i]))
        {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(slot_combo), default_slots[i]);
        }
    }

    gtk_box_pack_start(GTK_BOX(vbox), slot_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), slot_combo, FALSE, FALSE, 0);

    GtkWidget *reserve_btn = gtk_button_new_with_label("Reserve");
    gtk_box_pack_start(GTK_BOX(vbox), reserve_btn, FALSE, FALSE, 0);

    ReservationWidgets *widgets = malloc(sizeof(ReservationWidgets));
    widgets->id_entry = id_entry;
    widgets->slot_combo = slot_combo;
    widgets->window = window;

    g_signal_connect(reserve_btn, "clicked", G_CALLBACK(reserve_slot_button_clicked), widgets);

    gtk_widget_show_all(window);
}
void reserve_slot_button_clicked(GtkWidget *widget, gpointer user_data)
{
    ReservationWidgets *widgets = (ReservationWidgets *)user_data;
    GtkWidget *id_entry = widgets->id_entry;
    GtkWidget *combo = widgets->slot_combo;
    GtkWidget *window = widgets->window;

    const gchar *id_text = gtk_entry_get_text(GTK_ENTRY(id_entry));
    const gchar *slot_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));

    if (id_text == NULL || slot_text == NULL || strlen(id_text) == 0)
    {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
                                                   "Please enter a valid ID and select a slot.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    int id = atoi(id_text);
    if (!is_patient_id_exists(id))
    {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
                                                   "Patient ID not found.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    add_reservation(id, slot_text);

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,
                                               "Slot reserved successfully!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    gtk_widget_destroy(window);
    free(widgets);
}

void on_show_patient_clicked(GtkWidget *btn, gpointer user_data)
{
    GtkStack *stack = GTK_STACK(user_data);
    gtk_stack_set_visible_child_name(stack, "patient");
}

void on_show_reservation_clicked(GtkWidget *btn, gpointer user_data)
{
    GtkStack *stack = GTK_STACK(user_data);
    gtk_stack_set_visible_child_name(stack, "reservation");
}

void on_search_clicked(GtkWidget *widget, gpointer data)
{
    const gchar *id_text = gtk_entry_get_text(GTK_ENTRY(ID_text_Entry));
    int id = atoi(id_text);

    Patient *found = findByID(id);
    if (found == NULL)
    {
        GtkWidget *dialog = gtk_dialog_new_with_buttons(
            "Patient Not Found",
            GTK_WINDOW(main_window),
            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
            "_Close", GTK_RESPONSE_CLOSE,
            NULL);
        gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);

        GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
        GtkWidget *label = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(label), "<span foreground='red'>No patient found with this ID.</span>");
        gtk_container_add(GTK_CONTAINER(content_area), label);

        gtk_widget_show_all(dialog);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Prepare patient info
    char patient_info[512];
    sprintf(patient_info,
            "<span foreground='#0078a9' font='18'><b>Patient Info:-</b></span>\n"
            "<span foreground='black' font='14'><b>Name: %s\nAge: %d\nGender: %s</b></span>",
            found->name, found->age, found->gender);

    // Prepare reservations info
    char reservations_info[512] = "<span foreground='#0078a9' font='18'><b>Reservations:</b></span>\n";
    bool has_reservations = false;

    Reservation *current = res_head;
    while (current != NULL)
    {
        if (current->patient_id == id)
        {
            strcat(reservations_info, "<span foreground='black' font='14'>");
            strcat(reservations_info, current->slot);
            strcat(reservations_info, "</span>\n");
            has_reservations = true;
        }
        current = current->next;
    }

    if (!has_reservations)
    {
        strcpy(reservations_info, "No reservations for this patient.");
    }

    // Create dialog window
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
        "Patient Details",
        GTK_WINDOW(main_window),
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        "_Close", GTK_RESPONSE_CLOSE,
        NULL);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create stack to switch views
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 300);

    GtkWidget *patient_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(patient_label), patient_info);
    gtk_label_set_justify(GTK_LABEL(patient_label), GTK_JUSTIFY_LEFT);
    gtk_label_set_xalign(GTK_LABEL(patient_label), 0.0);
    gtk_widget_set_margin_start(patient_label, 15);

    GtkWidget *reservation_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(reservation_label), reservations_info);
    gtk_label_set_justify(GTK_LABEL(reservation_label), GTK_JUSTIFY_LEFT);
    gtk_label_set_xalign(GTK_LABEL(reservation_label), 0.0);
    gtk_widget_set_margin_start(reservation_label, 15);

    gtk_stack_add_named(GTK_STACK(stack), patient_label, "patient");
    gtk_stack_add_named(GTK_STACK(stack), reservation_label, "reservation");

    // Create buttons to switch between views
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *show_patient_btn = gtk_button_new_with_label("Show Patient Info");
    GtkWidget *show_reservation_btn;

    if (has_reservations)
        show_reservation_btn = gtk_button_new_with_label("Show Reservation Info");
    else
        show_reservation_btn = gtk_button_new_with_label("No reservations for this patient.");

    // Connect button signals
    // Connect button signals
    g_signal_connect(show_patient_btn, "clicked", G_CALLBACK(on_show_patient_clicked), stack);
    g_signal_connect(show_reservation_btn, "clicked", G_CALLBACK(on_show_reservation_clicked), stack);

    gtk_box_pack_start(GTK_BOX(button_box), show_patient_btn, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(button_box), show_reservation_btn, TRUE, TRUE, 5);

    gtk_box_pack_start(GTK_BOX(content_area), button_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(content_area), stack, TRUE, TRUE, 10);

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
