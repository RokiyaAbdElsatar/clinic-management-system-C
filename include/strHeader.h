#ifndef STRHEADER_H
#define STRHEADER_H


#define SLOT_COUNT 5

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


typedef struct Reservation {
    int patient_id;
    char slot[30];
    struct Reservation *next;
} Reservation;

extern Reservation *res_head;

extern const char *default_slots[SLOT_COUNT];


typedef struct ReservationWidgets{
    GtkWidget *id_entry;
    GtkWidget *slot_combo;
    GtkWidget *window;
} ReservationWidgets;


void addPatient(int id, int age, const char* name, const char* gender);
Patient* findByID(int id);

bool is_patient_id_exists(int id);

void editPatient(int id, const char* newName, int newAge, const char* newGender);
void displayPatients();
void on_login_clicked(GtkWidget *widget, gpointer data);


bool is_slot_reserved(const char *slot);

void add_reservation(int patient_id, const char *slot);

void reserve_slot_button_clicked(GtkWidget *widget, gpointer user_data);

bool cancel_reservation_by_id(int patient_id);

#endif 