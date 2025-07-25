#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "../include/strHeader.h"
#include "../include/ui_header.h"
#include <stdbool.h>

extern GtkWidget *loginBTN;
extern GtkWidget *password_Entry;

extern GtkWidget *admin_window;
extern GtkWidget *main_window;
extern GtkWidget *admin_dashboard;

int attempts = 3;
// bool is_admin_logged_in = false;
Patient *head = NULL;

void on_login_clicked(GtkWidget *widget, gpointer data)
{
    const gchar *Enteredpassword = gtk_entry_get_text(GTK_ENTRY(password_Entry));
    if (g_strcmp0(Enteredpassword, "1234") == 0)
    {
        attempts = 0;
        gtk_widget_hide(admin_window);
        show_admin_dashboard(NULL);

        // return true;
    }
    else
    {
        attempts--;
        if (attempts >= 1)
        {
            gchar *message = g_strdup_printf("Wrong password! Attempts left: %d", attempts);
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                       GTK_DIALOG_MODAL,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "%s", message);
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            g_free(message);
        }
        else
        {
            exit(EXIT_SUCCESS);
        }
    }
}

Patient *create_patient(int id, int age, const char *name, const char *gender)
{
    Patient *new_patient = (Patient *)malloc(sizeof(Patient));
    if (new_patient == NULL)
    {
        return NULL;
    }

    new_patient->id = id;
    new_patient->age = age;
    strcpy(new_patient->name, name);
    strcpy(new_patient->gender, gender);
    new_patient->next = NULL;

    return new_patient;
}

Patient *findByID(int id)
{
    Patient *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            return current; // Patient found
        }
        current = current->next;
    }
    return NULL; // Patient not found
}
void addPatient(int id, int age, const char *name, const char *gender)
{
    Patient *newPatient = ((Patient *)calloc(1, sizeof(Patient)));
    if (findByID(id) != NULL)
    {
        g_print("Patient with ID %d already exists.\n", id);
        // free(newPatient);
        return;
    }

    newPatient->id = id;
    newPatient->age = age;
    strcpy(newPatient->name, name);
    strcpy(newPatient->gender, gender);
    // Add the new patient to the linked list
    newPatient->next = head;
    head = newPatient;
}

void editPatient(int id, const char *newName, int newAge, const char *newGender)
{
    Patient *patient = findByID(id);
    if (patient != NULL)
    {
        if (newName)
            strcpy(patient->name, newName);
        if (newAge > 0)
            patient->age = newAge;
        if (newGender)
            strcpy(patient->gender, newGender);
        g_print("Patient with ID %d updated successfully.\n", id);
    }
    else
    {
        g_print("Patient with ID %d not found. Cannot edit.\n", id);
    }
}
