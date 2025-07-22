// #define Length 50
// #define maxPatient 5
// #define maxSlots 5

// typedef struct 
// {
//     char name[Length],gender;
//     int age , id ,reservedSlot ;

// }Patient;

// int addPatient(Patient newPatient);
// int findByID(int id);


typedef struct Patient {
    int id;
    int age;
    char name[50];
    char disease[50];
    char doctor[50];
   struct Patient *next;
} Patient;
extern Patient *head;


void addPatient();

Patient *findByID(int id);

void editPatient(int id); 

void displayPatients();
void on_login_clicked(GtkWidget *widget, gpointer data);