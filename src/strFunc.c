#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h> 
#include "strHeader.h"

extern GtkWidget *loginBTN;
extern GtkWidget *password_Entry;
int attempts = 3;

void on_login_clicked(GtkWidget *widget, gpointer data) {
    const  gchar *Enteredpassword = gtk_entry_get_text(GTK_ENTRY(password_Entry));
    if (g_strcmp0(Enteredpassword, "1234") == 0) {
        attempts = 0;
       GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"Login successful!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    
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

// Patient patients[maxPatient];
// int patientCount = 0;
// int slotReserved[maxSlots] = {0};

// int findByID(int id){
//     for (int i = 0; i < patientCount; i++)
//     {
//         if (patients[i].id == id)
//         {
//             return i;
//         }
//     }
//     return -1;
// }

// int addPatient(Patient newPatient){
//     if (findByID(newPatient.id)!=-1)
//     {
//         return 0;
//     }
//     if (patientCount >= maxPatient) // check memory full
//     {
//         return -1;
//     }
//     newPatient.reservedSlot = -1;
//     patients[patientCount++] = newPatient;
//     return 1;
// }