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
//bool is_admin_logged_in = false;
Patient *head = NULL;



void on_login_clicked(GtkWidget *widget, gpointer data) {
    const gchar *Enteredpassword = gtk_entry_get_text(GTK_ENTRY(password_Entry));
    if (g_strcmp0(Enteredpassword, "1234") == 0) {
        attempts = 0;
        gtk_widget_hide(admin_window);
        show_admin_dashboard(NULL);

        // return true;
    } else {
        attempts--;
        if (attempts >= 1) {
            gchar *message = g_strdup_printf("Wrong password! Attempts left: %d", attempts);
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_ERROR,
                GTK_BUTTONS_OK,
                "%s", message);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            g_free(message);
        }
    }
}
    void addPatient() {
    Patient *newPatient = ((Patient *)calloc(1, sizeof(Patient)));
    newPatient->id = 1;  // Assign a unique ID
    newPatient->age = 30;
    g_strlcpy(newPatient->name, "John Doe", sizeof(newPatient->name));
    g_strlcpy(newPatient->disease, "Flu", sizeof(newPatient->disease));
    g_strlcpy(newPatient->doctor, "Dr. Smith", sizeof(newPatient->doctor));

    // Add the new patient to the linked list
    newPatient->next = head;
    head = newPatient;
}