#ifndef STRHEADER_H
#define STRHEADER_H

typedef struct Patient {
    int id;
    int age;
    char name[50];
    char gender[50];
   struct Patient *next;
} Patient;
extern Patient *head;


typedef struct AddPatientData{
    GtkWidget *entry_name;
    GtkWidget *entry_age;
    GtkWidget *entry_gender;
    GtkWidget *entry_id;
    GtkWidget *dialog;
    GtkListStore *store;
    GtkTreeView *treeview;
} AddPatientData;


void addPatient(int id, int age, const char* name, const char* gender);
Patient* findByID(int id);
void editPatient(int id, const char* newName, int newAge, const char* newGender);
void displayPatients();
void on_login_clicked(GtkWidget *widget, gpointer data);

#endif 